/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Game
*/

#include "Game.hpp"
#include "Initializer.hpp"

#include "PrinterSystem.hpp"
#include "ShipMvRSystem.hpp"
#include "ShipMvDSystem.hpp"
#include "ShipMvLSystem.hpp"
#include "ShipMvUSystem.hpp"
#include "ShootSystem.hpp"
#include "BgSystem.hpp"
#include "CleanSystem.hpp"
#include "TextureComponent.hpp"

#include "PositionComponent.hpp"
#include "TextureComponent.hpp"

#include <stdexcept>

#include "Initializer.hpp"
#include "PositionComponent.hpp"
#include "PrinterSystem.hpp"
#include "TextureComponent.hpp"
#include "MvmtComponent.hpp"

#include "DataNet.hpp"
#include "TypeMapCreator.hpp"

using namespace Client;

static void useLeft(void *g) {
    Game *game = (Game*) g;
    game->subCallSystem<ECS::ShipMvLSystem>(std::vector<std::any>());
}

static void useRight(void *g) {
    Game *game = (Game*) g;
    game->subCallSystem<ECS::ShipMvRSystem>(std::vector<std::any>());
}

static void useDown(void *g) {
    Game *game = (Game*) g;
    game->subCallSystem<ECS::ShipMvDSystem>(std::vector<std::any>());
}

static void useUp(void *g) {
    Game *game = (Game*) g;
    game->subCallSystem<ECS::ShipMvUSystem>(std::vector<std::any>());
}

static void useClick(void *g) {
    Game *game = (Game*) g;
    game->_init = true;
}

static void useSpace(void *g) {
    Game *game = (Game*) g;
    Uint64 current_shoot = game->getTicks();
    if (current_shoot - game->last_shoot > 500) {
        game->last_shoot = current_shoot;
        game->subCallSystem<ECS::ShootSystem>(std::vector<std::any>());
    }
}

static void useHover(void *g) {
    Game *game = (Game*) g;
    if (game->_init)
        return;
    auto & texs = game->_registry.get_components<ECS::TextureComponent>();
    if (texs.size() < 2)
        return;
    if (!texs[1])
        return;
    auto & vt = texs[1].value();
    vt.setPath("./assets/play_hover.png");
}

static void useDehover(void *g) {
    Game *game = (Game*) g;
    if (game->_init)
        return;
    auto & texs = game->_registry.get_components<ECS::TextureComponent>();
    if (texs.size() < 2)
        return;
    if (!texs[1])
        return;
    auto & vt = texs[1].value();
    vt.setPath("./assets/play.png");
}

Game::Game(unsigned short port, std::string address, int const sound) :
    _alive(true),
    _networkClient(_io_service, address, port, _alive),
    _user_id(0),
    last_shoot(0),
    _sound(sound),
    _graphics(sound),
    _init(false)
{
    ECS::Initializer initer(_registry);
    initer.init_components();
    initer.init_system();
    initer.init_menu();
    ECS::TypeMapCreator creatorty;
    DataNet::registerMapTypes(creatorty.getTypeIndexMap());
    PrinterSystem *sys = new PrinterSystem(_registry, _graphics.getLoader(), _graphics);
    _registry.register_system<PrinterSystem>(sys, std::type_index(typeid(PrinterSystem)));
    _graphics.registerBind(_graphics.keyLeft, &useLeft);
    _graphics.registerBind(_graphics.keyRight, &useRight);
    _graphics.registerBind(_graphics.keyDown, &useDown);
    _graphics.registerBind(_graphics.keyUp, &useUp);
    _graphics.registerBind(_graphics.keySpace, &useSpace);
    _graphics.registerBind(_graphics.keyClick, &useClick);
    _graphics.registerBind(_graphics.keyHover, &useHover);
    _graphics.registerBind(_graphics.keyDehover, &useDehover);
}

void Game::start() {
    std::thread NetworkThread(&Game::startNetworkClient, this);
    NetworkThread.detach();
    ECSLoop();
    _io_service.stop();
}

void Game::startNetworkClient() {
    _networkClient.run();
    _io_service.run();
}

void Game::ECSLoop() {
    _graphics.playSound("./assets/background.mp3", -1);
    Uint64 time = _graphics.getTicks();
    Uint64 last_shoot = _graphics.getTicks();
    bool connect = false;
    bool first_received = false;
    while(_alive) {
        // Network logic
        if (_init) {
            _networkClient.checkSendLoop();
            if (_networkClient.getQueueSizeToRead() > 0) {
                if (!first_received) {
                    _registry = ECS::Registry();
                    ECS::Initializer initer(_registry);
                    initer.init_components();
                    initer.init_system();
                    PrinterSystem *sys = new PrinterSystem(_registry, _graphics.getLoader(), _graphics);
                    _registry.register_system<PrinterSystem>(sys, std::type_index(typeid(PrinterSystem)));
                    _graphics.playSound("./assets/game_start.mp3", 1);
                    first_received = true;
                }
                std::optional<DataNet> odata = _networkClient.popDatanetToRead();
                if (odata) {
                    DataNet data = odata.value();
                    if (data._index == std::type_index(typeid(ECS::MvmtComponent))) {
                        _user_id = data._value;
                    } else if (data._index == std::type_index(typeid(ECS::TextureComponent))) {
                        ECS::TextureComponent tc = std::any_cast<ECS::TextureComponent>(data._any);
                        if (tc.getPath().compare("./assets/r-typesheet30a.gif") == 0)
                            _graphics.playSound("./assets/player_shoot.mp3", 0);
                        else if (tc.getPath().compare("./assets/r-typesheet16.gif") == 0)
                            _graphics.playSound("./assets/enemy_shoot.mp3", 0);
                    } else if (data._index == std::type_index(typeid(ECS::IgnoreComponent))) {
                        auto const &textures = _registry.get_components<ECS::TextureComponent>();
                        if (textures.size() > data._value) {
                            if (textures[data._value]) {
                                std::string path = textures[data._value].value().getPath();
                                if (path.compare("./assets/r-typesheet7.gif") == 0 || path.compare("./assets/r-typesheet30.gif") == 0)
                                    _graphics.playSound("./assets/enemy_death.mp3", 0);
                                else if (path.compare("./assets/r-typesheet3.gif") == 0)
                                    _graphics.playSound("./assets/bonus.mp3", 0);
                                else if (path.compare("./assets/r-typesheet46.gif") == 0 || path.compare("./assets/r-typesheet47.gif") == 0 ||
                                path.compare("./assets/r-typesheet48.gif") == 0 || path.compare("./assets/r-typesheet49.gif") == 0)
                                    _graphics.playSound("./assets/player_death.mp3", 0);
                            }
                        }
                    }
                    ECS::Entity entity(data._value);
                    _registry.add_component(entity, data._index, data._any);
                }
            }
            if (!first_received) {
                DataNet coda(1, std::type_index(typeid(int)), 1);
                _networkClient.pushDatanetToSend(coda);
            }
        }
        if (_graphics.call(this)) {
            _alive = false;
            exit(0);
            return;
        }
        _registry.call_system<ECS::CleanSystem>(std::vector<std::any>());
        // Render
        Uint64 current = _graphics.getTicks();
        if (current - time > 10) {
            time = current;
            _registry.call_system<ECS::BgSystem>(std::vector<std::any>());
            _graphics.renderClear();
            _registry.call_system<PrinterSystem>(std::vector<std::any>());
        }
    }
}

Uint64 Game::getTicks() {
    return _graphics.getTicks();
}

Graphics::GraphSystem &Game::getGraphics() {
    return _graphics;
}

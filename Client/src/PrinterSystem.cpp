/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PrinterSystem
*/

#include <any>

#include "PrinterSystem.hpp"

#include "PositionComponent.hpp"
#include "TextureComponent.hpp"
#include "RectComponent.hpp"
#include "IgnoreComponent.hpp"

#include <random>

using namespace Client;

/**
 * PrinterSystem constructor
 * 
 * @param registry the ECS registry
 * @param loader the SDL Texture loader
 */
PrinterSystem::PrinterSystem(ECS::Registry & registry, Graphics::Loader & loader, Graphics::GraphSystem &graphics) :
    _registry(registry),
    _loader(loader),
    _graphics(graphics)
{}

std::vector<ECS::Info> PrinterSystem::subCallSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &ignores = _registry.get_components<ECS::IgnoreComponent>();
    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &textures = _registry.get_components<ECS::TextureComponent>();

    for (int i = 0; i < 4 && i < positions.size() && i < textures.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto const &ign = ignores[i];
        if (ign)
            continue;
        auto const &pos = positions[i];
        auto const &tex = textures[i];
        
        if (pos && tex) {
            auto const &rect = _registry.get_components<ECS::RectComponent>()[i];
            auto const &vpos = pos.value();
            SDL_Rect drect = {vpos.getX(), vpos.getY(), vpos.getW(), vpos.getH()};
            if (rect) {
                auto const &vrect = rect.value();
                SDL_Rect srect = {vrect.getX(), vrect.getY(), vrect.getW(), vrect.getH()};
                if (tex.value().getPath().compare("./assets/r-typesheet30a.gif") == 0)
                    srect.x = srect.w * (std::rand() % 3);
                _graphics.render(tex.value().getPath(), &srect, &drect);
            } else {
                _graphics.render(tex.value().getPath(), NULL, &drect);
            }
        }
    }

    return list;
}

std::vector<ECS::Info> PrinterSystem::callSystem(std::vector<std::any> & params) {
    std::vector<ECS::Info> list;

    auto const &positions = _registry.get_components<ECS::PositionComponent>();
    auto const &textures = _registry.get_components<ECS::TextureComponent>();

    for (int i = 4; i < positions.size(); i++) {
        if (params.size() > 0) {
            int &e = std::any_cast<int&>(params.at(0));
            if (e != i)
                continue;
        }
        auto const &pos = positions[i];
        auto const &tex = textures[i];
        
        if (pos && tex) {
            auto const &rect = _registry.get_components<ECS::RectComponent>()[i];
            auto const &vpos = pos.value();
            SDL_Rect drect = {vpos.getX(), vpos.getY(), vpos.getW(), vpos.getH()};
            if (rect) {
                auto const &vrect = rect.value();
                SDL_Rect srect = {vrect.getX(), vrect.getY(), vrect.getW(), vrect.getH()};
                if (tex.value().getPath().compare("./assets/r-typesheet30a.gif") == 0)
                    srect.x = srect.w * (std::rand() % 3);
                _graphics.render(tex.value().getPath(), &srect, &drect);
            } else {
                _graphics.render(tex.value().getPath(), NULL, &drect);
            }
        }
    }
    std::vector<ECS::Info> spe = subCallSystem(params);
    for (int i = 0; i < spe.size(); i++)
        list.push_back(spe[i]);
    SDL_RenderPresent(_loader.getRenderer());

    return list;
}

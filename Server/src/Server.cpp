/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** Server
*/

#include "ECS/includes/Initializer.hpp"
#include "ECS/includes/Registry.hpp"
#include "ECS/includes/TypeMapCreator.hpp"

#include "Network/includes/UDPServer.hpp"
#include "Network/includes/DataNet.hpp"
#include "DataNet.hpp"
#include "Server.hpp"
#include "SpawnEnemySystem.hpp"
#include "SpawnEnemyColSystem.hpp"
#include "SpawnBonusSystem.hpp"
#include "SpawnObstacleSystem.hpp"
#include "SpawnDesObstSystem.hpp"
#include "MoveObstacleSystem.hpp"
#include "CollideSystem.hpp"
#include "BossMvSystem.hpp"

#include <time.h>
#include <chrono>

#include "FireSystem.hpp"
#include "CleanSystem.hpp"
#include "DestroySystem.hpp"
#include "EnemyShootSystem.hpp"


/**
 * Initialize server
 * 
 * @param port the port to bind the server
 * @param address the address to affect the server
 * @param registry the ECS registry of the server
 */
Server::Server(std::string address, unsigned short port, ECS::Registry &registry) :
    _registry(registry),
    _networkServer(_io_service, address, port, registry)
{}

/**
 * Start the thread of the server
 */
void Server::run() {
    std::thread NetworkThread(&Server::startNetworkServer, this);
    NetworkThread.detach();
    std::thread ECSThread(&Server::ECSLoop, this);
    ECSThread.detach();
    ECSLogic();
    while(true)
        std::this_thread::sleep_for(std::chrono::seconds(1));
    _io_service.stop();
}

/**
 * Start the network part
 */
void Server::startNetworkServer() {
    _networkServer.run();
    _io_service.run();
}


static uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

void Server::gameLogic(uint64_t &startGameLogicTiming)
{
    uint64_t shoot_current = timeSinceEpochMillisec();
    if (shoot_current - startGameLogicTiming >= CONTINUOUS_TIMING) {
        std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::FireSystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents2 = _registry.call_system<ECS::DestroySystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents3 = _registry.call_system<ECS::ObtainSystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents4 = _registry.call_system<ECS::RemoveObtainableSystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents5 = _registry.call_system<ECS::MoveObstacleSystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents6 = _registry.call_system<ECS::CollideSystem>(std::vector<std::any>());
        std::vector<ECS::Info> changedComponents7 = _registry.call_system<ECS::BossMvSystem>(std::vector<std::any>());
        for (int i = 0; i < changedComponents2.size(); i++)
            changedComponents.push_back(changedComponents2[i]);
        for (int i = 0; i < changedComponents3.size(); i++)
            changedComponents.push_back(changedComponents3[i]);
        for (int i = 0; i < changedComponents4.size(); i++)
            changedComponents.push_back(changedComponents4[i]);
        for (int i = 0; i < changedComponents5.size(); i++)
            changedComponents.push_back(changedComponents5[i]);
        for (int i = 0; i < changedComponents6.size(); i++)
            changedComponents.push_back(changedComponents6[i]);
        for (int i = 0; i < changedComponents7.size(); i++)
            changedComponents.push_back(changedComponents7[i]);
        std::size_t sizeChangedComponents = changedComponents.size();
        for (std::size_t i = 0; i < sizeChangedComponents; i++) {
            ECS::Info &inf = changedComponents[i];
            DataNet data(inf._value, inf._index, inf._any);
            _networkServer.pushDatanetToSend(data);
        }
        startGameLogicTiming = timeSinceEpochMillisec();
    }
}

void Server::levelOne() {
    time_t levelStart = time(0);
    time_t startTimingSpawn = time(0);
    time_t startBonusTimingSpawn = time(0);
    uint64_t startGameLogicTiming = timeSinceEpochMillisec();

    while (time(0) - levelStart <= LEVEL_TIMING) {
        if(time(0) - startTimingSpawn > SPAWN_TIMING) {
            startTimingSpawn = startTimingSpawn + SPAWN_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnEnemySystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents2 = _registry.call_system<ECS::EnemyShootSystem>(std::vector<std::any>());
            for (int i = 0; i < changedComponents2.size(); i++)
                changedComponents.push_back(changedComponents2[i]);
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        if(time(0) - startBonusTimingSpawn > BONUS_SPAWN_TIMING) {
            startBonusTimingSpawn = startBonusTimingSpawn + BONUS_SPAWN_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnBonusSystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents2 = _registry.call_system<ECS::SpawnObstacleSystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents3 = _registry.call_system<ECS::SpawnDesObstSystem>(std::vector<std::any>());
            for (int i = 0; i < changedComponents2.size(); i++)
                changedComponents.push_back(changedComponents2[i]);
            for (int i = 0; i < changedComponents3.size(); i++)
                changedComponents.push_back(changedComponents3[i]);
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        gameLogic(startGameLogicTiming);
    }
    startGameLogicTiming = timeSinceEpochMillisec();
    levelStart = time(0);
    startTimingSpawn= time(0);
    std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnBossSystem>(std::vector<std::any>());
    std::size_t sizeChangedComponents = changedComponents.size();
    for (std::size_t i = 0; i < sizeChangedComponents; i++) {
        ECS::Info &inf = changedComponents[i];
        DataNet data(inf._value, inf._index, inf._any);
        _networkServer.pushDatanetToSend(data);
    }
    while (time(0) - levelStart <= LEVEL_TIMING) {
        if(time(0) - startTimingSpawn > BOSS_SHOOT_TIMING) {
            startTimingSpawn = startTimingSpawn + BOSS_SHOOT_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::EnemyShootSystem>(std::vector<std::any>());
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        gameLogic(startGameLogicTiming);
    }
}

void Server::levelTwo() {
time_t levelStart = time(0);
    time_t startTimingSpawn = time(0);
    time_t startBonusTimingSpawn = time(0);
    uint64_t startGameLogicTiming = timeSinceEpochMillisec();

    while (time(0) - levelStart <= LEVEL_TIMING) {
        if(time(0) - startTimingSpawn > SPAWN_TIMING) {
            startTimingSpawn = startTimingSpawn + SPAWN_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnEnemyColSystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents2 = _registry.call_system<ECS::EnemyShootSystem>(std::vector<std::any>());
            for (int i = 0; i < changedComponents2.size(); i++)
                changedComponents.push_back(changedComponents2[i]);
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        if(time(0) - startBonusTimingSpawn > BONUS_SPAWN_TIMING) {
            startBonusTimingSpawn = startBonusTimingSpawn + BONUS_SPAWN_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnBonusSystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents2 = _registry.call_system<ECS::SpawnObstacleSystem>(std::vector<std::any>());
            std::vector<ECS::Info> changedComponents3 = _registry.call_system<ECS::SpawnDesObstSystem>(std::vector<std::any>());
            for (int i = 0; i < changedComponents2.size(); i++)
                changedComponents.push_back(changedComponents2[i]);
            for (int i = 0; i < changedComponents3.size(); i++)
                changedComponents.push_back(changedComponents3[i]);
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        gameLogic(startGameLogicTiming);
    }
    startGameLogicTiming = timeSinceEpochMillisec();
    levelStart = time(0);
    startTimingSpawn= time(0);
    std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::SpawnBossSystem>(std::vector<std::any>());
    std::size_t sizeChangedComponents = changedComponents.size();
    for (std::size_t i = 0; i < sizeChangedComponents; i++) {
        ECS::Info &inf = changedComponents[i];
        DataNet data(inf._value, inf._index, inf._any);
        _networkServer.pushDatanetToSend(data);
    }
    while (time(0) - levelStart <= LEVEL_TIMING) {
        if(time(0) - startTimingSpawn > BOSS_SHOOT_TIMING) {
            startTimingSpawn = startTimingSpawn + BOSS_SHOOT_TIMING;
            std::vector<ECS::Info> changedComponents = _registry.call_system<ECS::EnemyShootSystem>(std::vector<std::any>());
            std::size_t sizeChangedComponents = changedComponents.size();
            for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                ECS::Info &inf = changedComponents[i];
                DataNet data(inf._value, inf._index, inf._any);
                _networkServer.pushDatanetToSend(data);
            }
        }
        gameLogic(startGameLogicTiming);
    }
}


void Server::ECSLogic() {
    std::cout << "waiting for a player to connect" << std::endl;
    while (!_registry.getNumberUsers()) {}
    while(true) {
        levelOne();
        levelTwo();
    }
}

/**
 * Launch the ECS Loop
 */
void Server::ECSLoop() {
    ECS::TypeMapCreator creatorty;
    DataNet::registerMapTypes(creatorty.getTypeIndexMap());
    while(true) {
        _networkServer.checkSendLoop();
        if (_networkServer.getQueueSizeToRead() != 0) {
            std::optional<DataNet> odata = _networkServer.popDatanetToRead();
            if (odata) {
                DataNet data = odata.value();
                if (data._index != std::type_index(typeid(int))) {
                    std::vector<std::any> params;
                    params.push_back(data._value);
                    std::vector<ECS::Info> changedComponents = _registry.call_system(data._index, params);
                    std::size_t sizeChangedComponents = changedComponents.size();
                    for (std::size_t i = 0; i < sizeChangedComponents; i++) {
                        ECS::Info &inf = changedComponents[i];
                        DataNet data(inf._value, inf._index, inf._any);
                        _networkServer.pushDatanetToSend(data);
                    }
                }
            }
        }
    }
}

/**
 * Stop the server
 */
void Server::stop() {}

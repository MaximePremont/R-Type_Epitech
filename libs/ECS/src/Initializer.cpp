/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Initializer
*/

#include "Initializer.hpp"

#include "PositionComponent.hpp"
#include "TextureComponent.hpp"
#include "RectComponent.hpp"
#include "MvmtComponent.hpp"
#include "EnMvmtComponent.hpp"
#include "ShootComponent.hpp"
#include "IgnoreComponent.hpp"
#include "DestroyableComponent.hpp"
#include "ObtainableComponent.hpp"
#include "FireComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"
#include "TripleShotComp.hpp"
#include "ObstacleComponent.hpp"
#include "LazerComponent.hpp"

#include "ShipMvRSystem.hpp"
#include "ShipMvDSystem.hpp"
#include "ShipMvLSystem.hpp"
#include "ShipMvUSystem.hpp"
#include "MvmtComponent.hpp"
#include "ShootComponent.hpp"
#include "EnemyShootSystem.hpp"
#include "IgnoreComponent.hpp"
#include "ShootSystem.hpp"
#include "FireSystem.hpp"
#include "BgSystem.hpp"
#include "SpawnEnemySystem.hpp"
#include "SpawnEnemyColSystem.hpp"
#include "CleanSystem.hpp"
#include "DestroySystem.hpp"
#include "ObtainSystem.hpp"
#include "SpawnBonusSystem.hpp"
#include "RemoveObtainableSystem.hpp"
#include "SpawnObstacleSystem.hpp"
#include "SpawnDesObstSystem.hpp"
#include "SpawnBossSystem.hpp"
#include "MoveObstacleSystem.hpp"
#include "CollideSystem.hpp"
#include "BossMvSystem.hpp"

using namespace ECS;

Initializer::Initializer(Registry & registry) :
    _registry(registry)
{}

void Initializer::init_components() {
    _registry.register_component<PositionComponent>();
    _registry.register_component<TextureComponent>();
    _registry.register_component<RectComponent>();
    _registry.register_component<MvmtComponent>();
    _registry.register_component<EnMvmtComponent>();
    _registry.register_component<ShootComponent>();
    _registry.register_component<FireComponent>();
    _registry.register_component<IgnoreComponent>();
    _registry.register_component<DestroyableComponent>();
    _registry.register_component<ObtainableComponent>();
    _registry.register_component<LifeComponent>();
    _registry.register_component<ComputerComponent>();
    _registry.register_component<TripleShotComp>();
    _registry.register_component<ObstacleComponent>();
    _registry.register_component<LazerComponent>();
}

void Initializer::init_system() {
    _registry.register_system<ShipMvRSystem>(new ShipMvRSystem(_registry), std::type_index(typeid(ShipMvRSystem)));
    _registry.register_system<ShipMvUSystem>(new ShipMvUSystem(_registry), std::type_index(typeid(ShipMvUSystem)));
    _registry.register_system<ShipMvLSystem>(new ShipMvLSystem(_registry), std::type_index(typeid(ShipMvLSystem)));
    _registry.register_system<ShipMvDSystem>(new ShipMvDSystem(_registry), std::type_index(typeid(ShipMvDSystem)));
    _registry.register_system<ShootSystem>(new ShootSystem(_registry), std::type_index(typeid(ShootSystem)));
    _registry.register_system<EnemyShootSystem>(new EnemyShootSystem(_registry), std::type_index(typeid(EnemyShootSystem)));
    _registry.register_system<FireSystem>(new FireSystem(_registry), std::type_index(typeid(FireSystem)));
    _registry.register_system<BgSystem>(new BgSystem(_registry), std::type_index(typeid(BgSystem)));
    _registry.register_system<SpawnEnemySystem>(new SpawnEnemySystem(_registry), std::type_index(typeid(SpawnEnemySystem)));
    _registry.register_system<SpawnEnemyColSystem>(new SpawnEnemyColSystem(_registry), std::type_index(typeid(SpawnEnemyColSystem)));
    _registry.register_system<CleanSystem>(new CleanSystem(_registry), std::type_index(typeid(CleanSystem)));
    _registry.register_system<DestroySystem>(new DestroySystem(_registry), std::type_index(typeid(DestroySystem)));
    _registry.register_system<ObtainSystem>(new ObtainSystem(_registry), std::type_index(typeid(ObtainSystem)));
    _registry.register_system<SpawnBonusSystem>(new SpawnBonusSystem(_registry), std::type_index(typeid(SpawnBonusSystem)));
    _registry.register_system<RemoveObtainableSystem>(new RemoveObtainableSystem(_registry), std::type_index(typeid(RemoveObtainableSystem)));
    _registry.register_system<SpawnObstacleSystem>(new SpawnObstacleSystem(_registry), std::type_index(typeid(SpawnObstacleSystem)));
    _registry.register_system<SpawnDesObstSystem>(new SpawnDesObstSystem(_registry), std::type_index(typeid(SpawnDesObstSystem)));
    _registry.register_system<SpawnBossSystem>(new SpawnBossSystem(_registry), std::type_index(typeid(SpawnBossSystem)));
    _registry.register_system<MoveObstacleSystem>(new MoveObstacleSystem(_registry), std::type_index(typeid(MoveObstacleSystem)));
    _registry.register_system<CollideSystem>(new CollideSystem(_registry), std::type_index(typeid(CollideSystem)));
    _registry.register_system<BossMvSystem>(new BossMvSystem(_registry), std::type_index(typeid(BossMvSystem)));
}

void Initializer::register_users() {
    short idd = 46;
    for (short i = 0; i < 4; i++) {
        ECS::Entity e = _registry.spawn_entity();
        _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(0, 90 * i, 83, 60));
        std::string path("./assets/r-typesheet"+std::string(std::to_string(idd))+".gif");
        _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent(path));
        _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(0, 0, 33, 36));
        _registry.add_component<ECS::MvmtComponent>(e, ECS::MvmtComponent());
        _registry.add_component<ECS::ShootComponent>(e, ECS::ShootComponent());
        _registry.add_component<ECS::LifeComponent>(e, ECS::LifeComponent(PLAYER_LIVES));
        idd++;
    }
}

void Initializer::init_setup() {
    register_users();

    // Backgrounds
    ECS::Entity e = _registry.spawn_entity();
    _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(0, 0, 5449, WINDOW_HEIGHT));
    _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/r-typesheet45.gif"));
    _registry.add_component<ECS::RectComponent>(e, ECS::RectComponent(0, 0, 5449, WINDOW_HEIGHT));
    ECS::Entity e2 = _registry.spawn_entity();
    _registry.add_component<ECS::PositionComponent>(e2, ECS::PositionComponent(5449, 0, 5449, WINDOW_HEIGHT));
    _registry.add_component<ECS::TextureComponent>(e2, ECS::TextureComponent("./assets/r-typesheet45.gif"));
    _registry.add_component<ECS::RectComponent>(e2, ECS::RectComponent(0, 0, 5449, WINDOW_HEIGHT));
}

void Initializer::init_menu() {
    ECS::Entity e = _registry.spawn_entity();
    _registry.add_component<ECS::PositionComponent>(e, ECS::PositionComponent(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    _registry.add_component<ECS::TextureComponent>(e, ECS::TextureComponent("./assets/menu.png"));

    ECS::Entity b = _registry.spawn_entity();
    _registry.add_component<ECS::PositionComponent>(b, ECS::PositionComponent(WINDOW_WIDTH / 2 - 83, WINDOW_HEIGHT / 2 - 10, 166, 165));
    _registry.add_component<ECS::TextureComponent>(b, ECS::TextureComponent("./assets/play.png"));
    _registry.add_component<ECS::RectComponent>(b, ECS::RectComponent(0, 0, 331, 329));
}

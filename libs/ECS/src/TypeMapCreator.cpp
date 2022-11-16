/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TypeMapCreator
*/

#include <utility>

#include "TypeMapCreator.hpp"

#include "PositionComponent.hpp"
#include "TextureComponent.hpp"
#include "RectComponent.hpp"
#include "MvmtComponent.hpp"
#include "EnMvmtComponent.hpp"
#include "ShootComponent.hpp"
#include "FireComponent.hpp"
#include "IgnoreComponent.hpp"
#include "ObtainableComponent.hpp"
#include "DestroyableComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"
#include "TripleShotComp.hpp"
#include "ObstacleComponent.hpp"
#include "LazerComponent.hpp"

#include "ShipMvRSystem.hpp"
#include "ShipMvDSystem.hpp"
#include "ShipMvLSystem.hpp"
#include "ShipMvUSystem.hpp"
#include "ShootSystem.hpp"
#include "EnemyShootSystem.hpp"
#include "FireSystem.hpp"
#include "SpawnEnemySystem.hpp"
#include "SpawnEnemyColSystem.hpp"
#include "IgnoreComponent.hpp"
#include "DestroySystem.hpp"
#include "ObtainSystem.hpp"
#include "SpawnBonusSystem.hpp"
#include "SpawnBossSystem.hpp"
#include "RemoveObtainableSystem.hpp"
#include "SpawnObstacleSystem.hpp"
#include "SpawnDesObstSystem.hpp"
#include "MoveObstacleSystem.hpp"
#include "CollideSystem.hpp"
#include "BossMvSystem.hpp"

using namespace ECS;

std::unordered_map<std::type_index, std::string> TypeMapCreator::_map;

TypeMapCreator::TypeMapCreator() {
    if (_map.size() > 0)
        return;
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(PositionComponent)), "PositionComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(TextureComponent)), "TextureComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(RectComponent)), "RectComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(MvmtComponent)), "MvmtComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(EnMvmtComponent)), "EnMvmtComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShootComponent)), "ShootComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(DestroyableComponent)), "DestroyableComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ObtainableComponent)), "ObtainableComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(LifeComponent)), "LifeComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ComputerComponent)), "ComputerComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(TripleShotComp)), "TripleShotComp"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ObstacleComponent)), "ObstacleComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(LazerComponent)), "LazerComponent"));

    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShipMvRSystem)), "ShipMvRSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShipMvDSystem)), "ShipMvDSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShipMvLSystem)), "ShipMvLSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShipMvUSystem)), "ShipMvUSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ShootSystem)), "ShootSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(EnemyShootSystem)), "EnemyShootSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(FireSystem)), "FireSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(FireComponent)), "FireComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnEnemySystem)), "SpawnEnemySystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnEnemyColSystem)), "SpawnEnemyColSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(IgnoreComponent)), "IgnoreComponent"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(DestroySystem)), "DestroySystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(ObtainSystem)), "ObtainSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnBonusSystem)), "SpawnBonusSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(RemoveObtainableSystem)), "RemoveObtainableSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnObstacleSystem)), "SpawnObstacleSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnDesObstSystem)), "SpawnDesObstSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(SpawnBossSystem)), "SpawnBossSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(MoveObstacleSystem)), "MoveObstacleSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(CollideSystem)), "CollideSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(BossMvSystem)), "BossMvSystem"));
    _map.insert(std::pair<std::type_index, std::string>(std::type_index(typeid(int)), "int"));
}


std::unordered_map<std::type_index, std::string> & TypeMapCreator::getTypeIndexMap() {
    return _map;
}

//
// Created by mikael-vallenet on 04/10/22.
//

#ifndef NETWORK_CASTMAP_HPP
#define NETWORK_CASTMAP_HPP

#include <unordered_map>
#include <typeindex>
#include <any>

#include "MvmtComponent.hpp"
#include "EnMvmtComponent.hpp"
#include "PositionComponent.hpp"
#include "RectComponent.hpp"
#include "TextureComponent.hpp"
#include "ShootComponent.hpp"
#include "IgnoreComponent.hpp"
#include "FireComponent.hpp"
#include "DestroyableComponent.hpp"
#include "ObtainableComponent.hpp"
#include "LifeComponent.hpp"
#include "ComputerComponent.hpp"
#include "TripleShotComp.hpp"
#include "ObstacleComponent.hpp"
#include "LazerComponent.hpp"

#include "ShipMvDSystem.hpp"
#include "ShipMvLSystem.hpp"
#include "ShipMvRSystem.hpp"
#include "ShipMvUSystem.hpp"
#include "ShootSystem.hpp"
#include "EnemyShootSystem.hpp"
#include "FireSystem.hpp"
#include "DestroySystem.hpp"
#include "SpawnEnemySystem.hpp"
#include "SpawnEnemyColSystem.hpp"
#include "ObtainSystem.hpp"
#include "SpawnBonusSystem.hpp"
#include "RemoveObtainableSystem.hpp"
#include "SpawnObstacleSystem.hpp"
#include "SpawnBossSystem.hpp"
#include "SpawnDesObstSystem.hpp"
#include "MoveObstacleSystem.hpp"
#include "CollideSystem.hpp"
#include "BossMvSystem.hpp"


#include "Registry.hpp"

template <class Archive>
class CastMap : public std::unordered_map<std::type_index, std::function<void (Archive &, std::any &)>>{ 
    public:
        CastMap(bool const serial) {
            if (serial) {

                std::function<void(Archive &, std::any &)> funcSpawnEnColSys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnEnemyColSystem)), funcSpawnEnColSys));
                std::function<void(Archive &, std::any &)> funcEnMv = [](Archive & ar, std::any & any) {
                    ECS::EnMvmtComponent lan = std::any_cast<ECS::EnMvmtComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::EnMvmtComponent)), funcEnMv));
                std::function<void(Archive &, std::any &)> funcBossMvSystem = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::BossMvSystem)), funcBossMvSystem));
                std::function<void(Archive &, std::any &)> funcLazerCompR = [](Archive & ar, std::any & any) {
                    ECS::LazerComponent lan = std::any_cast<ECS::LazerComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::LazerComponent)), funcLazerCompR));
                std::function<void(Archive &, std::any &)> funcSpawnBossSystem = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnBossSystem)), funcSpawnBossSystem));
                std::function<void(Archive &, std::any &)> funcCollideSystemR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::CollideSystem)), funcCollideSystemR));
                std::function<void(Archive &, std::any &)> funcSpawnObstR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnObstacleSystem)), funcSpawnObstR));
                std::function<void(Archive &, std::any &)> funcSpawnDesObstR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnDesObstSystem)), funcSpawnDesObstR));
                std::function<void(Archive &, std::any &)> funcMoveObstR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::MoveObstacleSystem)), funcMoveObstR));
                std::function<void(Archive &, std::any &)> funcObstacleCompR = [](Archive & ar, std::any & any) {
                    ECS::ObstacleComponent lan = std::any_cast<ECS::ObstacleComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObstacleComponent)), funcObstacleCompR));
                std::function<void(Archive &, std::any &)> funcRmObtSystem = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::RemoveObtainableSystem)), funcRmObtSystem));
                std::function<void(Archive &, std::any &)> funcTripleShotCompR = [](Archive & ar, std::any & any) {
                    ECS::TripleShotComp lan = std::any_cast<ECS::TripleShotComp>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::TripleShotComp)), funcTripleShotCompR));
                std::function<void(Archive &, std::any &)> funcObtainSystemR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObtainSystem)), funcObtainSystemR));
                std::function<void(Archive &, std::any &)> funcSpawnBonusSystemR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnBonusSystem)), funcSpawnBonusSystemR));
                std::function<void(Archive &, std::any &)> func_int = [](Archive & ar, std::any & any) {
                    int lan = std::any_cast<int>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(int)), func_int));
                std::function<void(Archive &, std::any &)> func_mvmtcomp = [](Archive & ar, std::any & any) {
                    ECS::MvmtComponent lan = std::any_cast<ECS::MvmtComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::MvmtComponent)), func_mvmtcomp));
                std::function<void(Archive &, std::any &)> func_poscomp = [](Archive & ar, std::any & any) {
                    ECS::PositionComponent lan = std::any_cast<ECS::PositionComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::PositionComponent)), func_poscomp));
                std::function<void(Archive &, std::any &)> func_rectcomp = [](Archive & ar, std::any & any) {
                    ECS::RectComponent lan = std::any_cast<ECS::RectComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::RectComponent)), func_rectcomp));
                std::function<void(Archive &, std::any &)> func_texcomp = [](Archive & ar, std::any & any) {
                    ECS::TextureComponent lan = std::any_cast<ECS::TextureComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::TextureComponent)), func_texcomp));
                std::function<void(Archive &, std::any &)> func_shocomp = [](Archive & ar, std::any & any) {
                    ECS::ShootComponent lan = std::any_cast<ECS::ShootComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShootComponent)), func_shocomp));
                std::function<void(Archive &, std::any &)> funcDestroyComp = [](Archive & ar, std::any & any) {
                    ECS::DestroyableComponent lan = std::any_cast<ECS::DestroyableComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::DestroyableComponent)), funcDestroyComp));
                std::function<void(Archive &, std::any &)> funcObtainComp = [](Archive & ar, std::any & any) {
                    ECS::ObtainableComponent lan = std::any_cast<ECS::ObtainableComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObtainableComponent)), funcObtainComp));
                std::function<void(Archive &, std::any &)> func_fircomp = [](Archive & ar, std::any & any) {
                    ECS::FireComponent lan = std::any_cast<ECS::FireComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::FireComponent)), func_fircomp));
                std::function<void(Archive &, std::any &)> func_igncomp = [](Archive & ar, std::any & any) {
                    ECS::IgnoreComponent lan = std::any_cast<ECS::IgnoreComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::IgnoreComponent)), func_igncomp));
                std::function<void(Archive &, std::any &)> funcLifeCompS = [](Archive & ar, std::any & any) {
                    ECS::LifeComponent lan = std::any_cast<ECS::LifeComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::LifeComponent)), funcLifeCompS));
                std::function<void(Archive &, std::any &)> funcComputerCompS = [](Archive & ar, std::any & any) {
                    ECS::ComputerComponent lan = std::any_cast<ECS::ComputerComponent>(any);
                    ar & (lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ComputerComponent)), funcComputerCompS));
                std::function<void(Archive &, std::any &)> funcDestroySys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::DestroySystem)), funcDestroySys));
                std::function<void(Archive &, std::any &)> func_dsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvDSystem)), func_dsys));
                std::function<void(Archive &, std::any &)> func_lsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvLSystem)), func_lsys));
                std::function<void(Archive &, std::any &)> func_rsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvRSystem)), func_rsys));
                std::function<void(Archive &, std::any &)> func_usys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvUSystem)), func_usys));
                std::function<void(Archive &, std::any &)> func_shosys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShootSystem)), func_shosys));
                std::function<void(Archive &, std::any &)> func_firsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::FireSystem)), func_firsys));
                std::function<void(Archive &, std::any &)> func_spsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnEnemySystem)), func_spsys));
                std::function<void(Archive &, std::any &)> funcEneShoot = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::EnemyShootSystem)), funcEneShoot));
            } else {

                std::function<void(Archive &, std::any &)> funcSpawnEnColSysR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnEnemyColSystem)), funcSpawnEnColSysR));
                std::function<void(Archive &, std::any &)> funcEnMvR = [](Archive & ar, std::any & any) {
                    ECS::EnMvmtComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::EnMvmtComponent)), funcEnMvR));
                std::function<void(Archive &, std::any &)> funcBossMvS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::BossMvSystem)), funcBossMvS));
                std::function<void(Archive &, std::any &)> funcLazerCompS = [](Archive & ar, std::any & any) {
                    ECS::LazerComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::LazerComponent)), funcLazerCompS));
                std::function<void(Archive &, std::any &)> funcSpawnBossR = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnBossSystem)), funcSpawnBossR));
                std::function<void(Archive &, std::any &)> funcCollideSystemS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::CollideSystem)), funcCollideSystemS));
                std::function<void(Archive &, std::any &)> funcSpawnObstS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnObstacleSystem)), funcSpawnObstS));
                std::function<void(Archive &, std::any &)> funcSpawnDesObstS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnDesObstSystem)), funcSpawnDesObstS));
                std::function<void(Archive &, std::any &)> funcMoveObstS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::MoveObstacleSystem)), funcMoveObstS));
                std::function<void(Archive &, std::any &)> funcObstCompS = [](Archive & ar, std::any & any) {
                    ECS::ObstacleComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObstacleComponent)), funcObstCompS));
                std::function<void(Archive &, std::any &)> funcRmObtSystemS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::RemoveObtainableSystem)), funcRmObtSystemS));
                std::function<void(Archive &, std::any &)> funcObtainSystemS = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObtainSystem)), funcObtainSystemS));
                std::function<void(Archive &, std::any &)> funcSpawnBonusSystem = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnBonusSystem)), funcSpawnBonusSystem));
                std::function<void(Archive &, std::any &)> funcTripleShotCompS = [](Archive & ar, std::any & any) {
                    ECS::TripleShotComp lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::TripleShotComp)), funcTripleShotCompS));
                std::function<void(Archive &, std::any &)> func_int = [](Archive & ar, std::any & any) {
                    int lan = 0;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(int)), func_int));
                std::function<void(Archive &, std::any &)> func_mvmtcomp = [](Archive & ar, std::any & any) {
                    ECS::MvmtComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::MvmtComponent)), func_mvmtcomp));
                std::function<void(Archive &, std::any &)> func_poscomp = [](Archive & ar, std::any & any) {
                    ECS::PositionComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::PositionComponent)), func_poscomp));
                std::function<void(Archive &, std::any &)> func_rectcomp = [](Archive & ar, std::any & any) {
                    ECS::RectComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::RectComponent)), func_rectcomp));
                std::function<void(Archive &, std::any &)> func_texcomp = [](Archive & ar, std::any & any) {
                    ECS::TextureComponent lan("");
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::TextureComponent)), func_texcomp));
                std::function<void(Archive &, std::any &)> func_shocomp = [](Archive & ar, std::any & any) {
                    ECS::ShootComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShootComponent)), func_shocomp));
                std::function<void(Archive &, std::any &)> func_fircomp = [](Archive & ar, std::any & any) {
                    ECS::FireComponent lan(5);
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::FireComponent)), func_fircomp));
                std::function<void(Archive &, std::any &)> funcObtainComp = [](Archive & ar, std::any & any) {
                    ECS::ObtainableComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ObtainableComponent)), funcObtainComp));
                std::function<void(Archive &, std::any &)> funcDestComp = [](Archive & ar, std::any & any) {
                    ECS::DestroyableComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::DestroyableComponent)), funcDestComp));
                std::function<void(Archive &, std::any &)> func_igncomp = [](Archive & ar, std::any & any) {
                    ECS::IgnoreComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::IgnoreComponent)), func_igncomp));
                std::function<void(Archive &, std::any &)> funcLifeCompR = [](Archive & ar, std::any & any) {
                    ECS::LifeComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::LifeComponent)), funcLifeCompR));
                std::function<void(Archive &, std::any &)> funcComputerCompR = [](Archive & ar, std::any & any) {
                    ECS::ComputerComponent lan;
                    ar & (lan);
                    any = std::any(lan);
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ComputerComponent)), funcComputerCompR));

                std::function<void(Archive &, std::any &)> func_dsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvDSystem)), func_dsys));
                std::function<void(Archive &, std::any &)> funcDestroySys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::DestroySystem)), funcDestroySys));
                std::function<void(Archive &, std::any &)> func_lsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvLSystem)), func_lsys));
                std::function<void(Archive &, std::any &)> func_rsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvRSystem)), func_rsys));
                std::function<void(Archive &, std::any &)> func_usys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShipMvUSystem)), func_rsys));
                std::function<void(Archive &, std::any &)> func_shosys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::ShootSystem)), func_shosys));
                std::function<void(Archive &, std::any &)> func_firsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::FireSystem)), func_firsys));
                std::function<void(Archive &, std::any &)> func_spsys = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::SpawnEnemySystem)), func_spsys));
                std::function<void(Archive &, std::any &)> funcEnemShoot = [](Archive & ar, std::any & any) {
                    (void) ar;
                    (void) any;
                };
                this->insert(std::pair<std::type_index, std::function<void(Archive &, std::any &)>>(std::type_index(typeid(ECS::EnemyShootSystem)), funcEnemShoot));
            }
        }
};

#endif //NETWORK_CASTMAP_HPP

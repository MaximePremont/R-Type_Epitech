##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

add_library(ecs STATIC
    src/Entity.cpp
    src/Initializer.cpp
    src/Registry.cpp
    src/TypeMapCreator.cpp
    src/Info.cpp
    src/components/PositionComponent.cpp
    src/components/TextureComponent.cpp
    src/components/RectComponent.cpp
    src/components/MvmtComponent.cpp
    src/components/EnMvmtComponent.cpp
    src/components/ShootComponent.cpp
    src/components/FireComponent.cpp
    src/components/IgnoreComponent.cpp
    src/components/DestroyableComponent.cpp
    src/components/ObstacleComponent.cpp
    src/components/DestroyableComponent.cpp
    src/components/ObtainableComponent.cpp
    src/components/LifeComponent.cpp
    src/components/ComputerComponent.cpp
    src/components/TripleShotComp.cpp
    src/components/CoordsComponent.cpp
    src/components/LazerComponent.cpp
    
    src/systems/BossMvSystem.cpp
    src/systems/FireSystem.cpp
    src/systems/DestroySystem.cpp
    src/systems/ShootSystem.cpp
    src/systems/EnemyShootSystem.cpp
    src/systems/BgSystem.cpp
    src/systems/SpawnEnemySystem.cpp
    src/systems/SpawnEnemyColSystem.cpp
    src/systems/SpawnBossSystem.cpp
    src/systems/CleanSystem.cpp
    src/systems/ShipMvRSystem.cpp
    src/systems/ShipMvUSystem.cpp
    src/systems/ShipMvLSystem.cpp
    src/systems/ShipMvDSystem.cpp
    src/systems/ObtainSystem.cpp
    src/systems/SpawnBonusSystem.cpp
    src/systems/SpawnObstacleSystem.cpp
    src/systems/SpawnDesObstSystem.cpp
    src/systems/MoveObstacleSystem.cpp
    src/systems/RemoveObtainableSystem.cpp
    src/systems/CollideSystem.cpp
)
target_link_directories(ecs PUBLIC
    ../Boost
    "../Network"
)
target_link_libraries(ecs PUBLIC
    Boost::asio
    network
)
target_include_directories(ecs PUBLIC
    "./includes"
    "./includes/components"
    "./includes/systems"
    "../Network/includes"
    "../boost/libs/asio/include"
    "../boost/libs/serialization/include"
)

enable_testing()
add_executable(ecsTests
    tests/Entity_test.cpp
    tests/Registry_test.cpp
    tests/SparseArray_test.cpp
    tests/System_test.cpp
)
target_link_libraries(ecsTests
    GTest::gtest_main
    ecs
)
target_include_directories(ecsTests PUBLIC
    "./includes"
    "../googletest/googletest/include"
)

gtest_discover_tests(ecsTests)
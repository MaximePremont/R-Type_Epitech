/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** PrinterSystem
*/

#pragma once

#include "Loader.hpp"
#include "Registry.hpp"
#include "Graphics.hpp"

namespace Client {
    class PrinterSystem : public ECS::System {
        public:
            PrinterSystem(ECS::Registry & registry, Graphics::Loader &loader, Graphics::GraphSystem &graphics);
            std::vector<ECS::Info> callSystem(std::vector<std::any> & params) override;
        private:
            ECS::Registry & _registry;
            Graphics::Loader &_loader;
            std::vector<ECS::Info> subCallSystem(std::vector<std::any> & params);
            Graphics::GraphSystem &_graphics;
    };  
}

/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Graphics
*/

#pragma once

#include <SDL.h>
#include <memory>
#include <type_traits>
#include <unordered_map>
#include <chrono>

#include "Loader.hpp"

namespace Graphics {
    class GraphSystem {
        public:
            GraphSystem(int const sound);
            ~GraphSystem();
            SDL_Renderer *getRenderer();

            void registerBind(int32_t const key, void(*f)(void*));
            bool call(void *g);

            Uint64 getTicks();

            int32_t keyLeft;
            int32_t keyRight;
            int32_t keyUp;
            int32_t keyDown;
            int32_t keySpace;
            int32_t keyClick;

            int32_t keyHover;
            int32_t keyDehover;

            void renderClear();

            Loader &getLoader();

            void render(std::string const path, SDL_Rect *srect, SDL_Rect *drect);
            void playSound(std::string const path, int loop);
        private:
            int const _sound;
            Loader _loader;
            std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> _window;
            SDL_Renderer *_renderer;
            std::unordered_map<int32_t, void(*)(void*)> _callers;
            bool _hovering;
            bool _gooingUp;
            bool _gooingDown;
            bool _gooingLeft;
            bool _gooingRight;
            uint64_t _eventTime;
            bool _firstEventCall;
    };
}

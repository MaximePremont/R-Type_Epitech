/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Graphics
*/

#include "Graphics.hpp"

#include <SDL_image.h>
#include <stdexcept>
#include <SDL_mixer.h>

#include <iostream>

using namespace Graphics;

GraphSystem::GraphSystem(int const sound) :
    _sound(sound),
    _loader(nullptr, sound),
    _window(nullptr, SDL_DestroyWindow),
    keyLeft(SDLK_LEFT),
    keyRight(SDLK_RIGHT),
    keyUp(SDLK_UP),
    keyDown(SDLK_DOWN),
    keySpace(SDLK_SPACE),
    keyClick(16),
    keyHover(17),
    keyDehover(18),
    _hovering(false),
    _gooingUp(false),
    _gooingDown(false),
    _gooingLeft(false),
    _gooingRight(false),
    _eventTime(0),
    _firstEventCall(true)
{
    if (_sound > 0) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
            throw std::runtime_error(SDL_GetError());
    } else {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0)
            throw std::runtime_error(SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_PNG) < 0)
        throw std::runtime_error("Can't load IMG_SDL");
    _window.reset(SDL_CreateWindow("R-Type", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0));
    if (!_window.get())
        throw std::runtime_error("Failed to create SDL2 window");
    _renderer = SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
        throw std::runtime_error("Failed to get window renderer");
    if (sound > 0) {
        Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    }
    _loader.setRenderer(getRenderer());
    _loader.loadSources();
}

static uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

GraphSystem::~GraphSystem() {
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *GraphSystem::getRenderer() {
    return _renderer;
}

void GraphSystem::registerBind(int32_t const key, void(*f)(void*)) {
    _callers[key] = f;
}

bool GraphSystem::call(void *g) {
    if (_firstEventCall) {
        _firstEventCall = false;
        _eventTime = timeSinceEpochMillisec();
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return true;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _gooingLeft = true;
                break;
            case SDLK_RIGHT:
                _gooingRight = true;
                break;
            case SDLK_DOWN:
                _gooingDown = true;
                break;
            case SDLK_UP:
                _gooingUp = true;
                break;
            case SDLK_SPACE:
                _callers[SDLK_SPACE](g);
                break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _gooingLeft = false;
                break;
            case SDLK_RIGHT:
                _gooingRight = false;
                break;
            case SDLK_DOWN:
                _gooingDown = false;
                break;
            case SDLK_UP:
                _gooingUp = false;
                break;
            }
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.x >= 457 && event.button.x <= 623 &&  event.button.y >= 350 && event.button.y <= 515)
                _callers[16](g);
        } else if (event.type == SDL_MOUSEMOTION) {
            if (event.motion.x >= 457 && event.motion.x <= 623 && event.motion.y >= 350 && event.motion.y <= 515 ) {
                if (!_hovering) {
                    _hovering = true;
                    _callers[17](g);
                }
            } else {
                if (_hovering) {
                    _hovering = false;
                    _callers[18](g);
                }
            }
        }
    }
    if (timeSinceEpochMillisec() - _eventTime > 30) {

        if (_gooingDown) _callers[SDLK_DOWN](g);
        if (_gooingUp) _callers[SDLK_UP](g);
        if (_gooingRight) _callers[SDLK_RIGHT](g);
        if (_gooingLeft) _callers[SDLK_LEFT](g);
        _eventTime = _eventTime + 30;
    }
    return false;
}

Uint64 GraphSystem::getTicks() {
    return SDL_GetTicks64();
}

void GraphSystem::renderClear() {
    SDL_RenderClear(_renderer);
}

Loader &GraphSystem::getLoader() {
    return _loader;
}

void GraphSystem::render(std::string const path, SDL_Rect *srect, SDL_Rect *drect) {
    SDL_RenderCopy(_loader.getRenderer(), _loader.getTexture(path).lock().get(), srect, drect);
}

void GraphSystem::playSound(std::string const path, int loop) {
    if (_sound <= 0)
        return;
    Mix_PlayChannel(-1, _loader.getSound(path).lock().get(), loop);
}

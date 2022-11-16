/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Loader
*/

#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>

namespace Graphics {
    class Loader {
        public:
            /**
             * Constructor
             * 
             * @param renderer SDL2 Window renderer
            */
            Loader(SDL_Renderer *renderer, int const sound);
            /**
             * Destructor
            */
            ~Loader();
            /**
             * Use a texture
             * 
             * @param path Relative path to texture
             * @return Weak pointer to the loaded texture
            */
            std::weak_ptr<SDL_Texture> getTexture(std::string const path);
            
            std::weak_ptr<Mix_Chunk> getSound(std::string const path);
            /**
             * Get SDL2 Renderer
             * 
             * @return SDL2 Renderer
            */
            SDL_Renderer *getRenderer();
            /**
             * Set SDL2 renderer
             * 
             * @param Renderer SDL2
            */
            void setRenderer(SDL_Renderer *renderer);
            /**
             * Load all sources
            */
            void loadSources();
        private:
            const int _sound;
            SDL_Renderer *_renderer;
            std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> _textures;
            std::unordered_map<std::string, std::shared_ptr<SDL_Surface>> _surfaces;
            std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> _musics;

            /**
             * Load a texture
             * 
             * @param path Relative path to texture
            */
            void loadTexture(std::string const path);
            void loadMusic(std::string const path);
    };
}

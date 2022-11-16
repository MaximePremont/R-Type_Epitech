/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** Loader
*/

#include <SDL_image.h>
#include <stdexcept>
#include <string>

#include "Loader.hpp"

using namespace Graphics;

/**
 * Loader constructor
 * 
 * @param renderer the SDL renderer object
 */
Loader::Loader(SDL_Renderer *renderer, int const sound) :
    _sound(sound),
    _renderer(renderer)
{}

/**
 * Loader destructor, clear all textures
 */
Loader::~Loader() {
    _textures.clear();
}

/**
 * Load a texture from a file
 * 
 * @param path path to the file which contains the texture
 */
void Loader::loadTexture(std::string const path) {
    SDL_Surface *surface = IMG_Load(path.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!texture)
        throw std::runtime_error("Can't load texture");
    std::shared_ptr<SDL_Surface> shsur(surface, SDL_FreeSurface);
    _surfaces[path] = shsur;
    std::shared_ptr<SDL_Texture> shtex(texture, SDL_DestroyTexture);
    _textures[path] = shtex;
}

void Loader::loadMusic(std::string const path) {
    Mix_Chunk *music = Mix_LoadWAV(path.c_str());
    std::shared_ptr<Mix_Chunk> shmu(music, Mix_FreeChunk);
    _musics[path] = shmu;
}

/**
 * Get the texture from the map
 * 
 * @param path path to struct
 * @returns the SDL texture
 */
std::weak_ptr<SDL_Texture> Loader::getTexture(std::string const path) {
    return _textures[path];
}

std::weak_ptr<Mix_Chunk> Loader::getSound(std::string const path) {
    return _musics[path];
}

/**
 * Get the SDL renderer
 * 
 * @returns the SDL texture
 */
SDL_Renderer *Loader::getRenderer() {
    return _renderer;
}

/**
 * Set the SDL renderer
 * 
 * @param renderer the SDL renderer to set
 */
void Loader::setRenderer(SDL_Renderer *renderer) {
    _renderer = renderer;
}

/**
 * Load ressources from typesheet5.gif
 */
void Loader::loadSources() {
    loadTexture(std::string("./assets/r-typesheet46.gif"));
    loadTexture(std::string("./assets/r-typesheet47.gif"));
    loadTexture(std::string("./assets/r-typesheet48.gif"));
    loadTexture(std::string("./assets/r-typesheet49.gif"));
    loadTexture(std::string("./assets/r-typesheet45.gif"));
    loadTexture(std::string("./assets/r-typesheet41.gif"));
    loadTexture(std::string("./assets/r-typesheet30a.gif"));
    loadTexture(std::string("./assets/r-typesheet30.gif"));
    loadTexture(std::string("./assets/r-typesheet32.gif"));
    loadTexture(std::string("./assets/r-typesheet3.gif"));
    loadTexture(std::string("./assets/r-typesheet7.gif"));
    loadTexture(std::string("./assets/r-typesheet1.gif"));
    loadTexture(std::string("./assets/r-typesheet16.gif"));
    loadTexture(std::string("./assets/background.png"));
    loadTexture(std::string("./assets/play.png"));
    loadTexture(std::string("./assets/play_hover.png"));
    loadTexture(std::string("./assets/menu.png"));
    if (_sound <= 0)
        return;
    loadMusic(std::string("./assets/background.mp3"));
    loadMusic(std::string("./assets/player_shoot.mp3"));
    loadMusic(std::string("./assets/game_start.mp3"));
    loadMusic(std::string("./assets/enemy_shoot.mp3"));
    loadMusic(std::string("./assets/enemy_death.mp3"));
    loadMusic(std::string("./assets/bonus.mp3"));
    loadMusic(std::string("./assets/player_death.mp3"));
}

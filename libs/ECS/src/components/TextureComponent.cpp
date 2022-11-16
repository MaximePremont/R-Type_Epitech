/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** TextureComponent
*/

#include "TextureComponent.hpp"

using namespace ECS;

TextureComponent::TextureComponent(std::string const path) :
    _path(path)
{}

std::string TextureComponent::getPath() const {
    return _path;
}

void TextureComponent::setPath(std::string const path) {
    _path = path;
}

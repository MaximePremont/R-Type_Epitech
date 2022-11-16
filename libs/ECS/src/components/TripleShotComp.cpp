/*
** EPITECH PROJECT, 2022
** B-CPP-500-LYN-5-1-rtype-maxime.premont
** File description:
** TripleShotComp.cpp
*/

#include "TripleShotComp.hpp"

using namespace ECS;

TripleShotComp::TripleShotComp(time_t startTime):_startTime(startTime) {}

time_t TripleShotComp::getStartTime() const
{
    return _startTime;
}
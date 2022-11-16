/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** CoordsComponent
*/

#pragma once

namespace ECS {
    class CoordsComponent {
        public:
            CoordsComponent(int const x = 0, int const y = 0, int const w = 1, int const h = 1);
            CoordsComponent(CoordsComponent const &copy);

            void setX(int const x);
            void setY(int const y);
            void setW(int const w);
            void setH(int const h);
            int getX() const;
            int getY() const;
            int getW() const;
            int getH() const;
        protected:
            int _x;
            int _y;
            int _w;
            int _h;
    };
}

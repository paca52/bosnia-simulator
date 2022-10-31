#ifndef BOMBS_HPP
#define BOMBS_HPP

#include <unordered_map>
#include <iostream>
#include "raylib.h"

#define SPACE_Y 32
#define SPACE_X 32

typedef unsigned int u_int;
using std::unordered_map;

namespace BombNS {
    struct Node {
        int value{0};
    };

    class Bomb {
    public:
        Bomb(u_int rows, u_int columns, Texture2D *texture);

        // getteri
        double getX() const;
        double getY() const;

        void info() const;

        void draw() const;

        bool operator>=(const Bomb& bomb);

        ~Bomb();
    private:
        double x, y;
        Texture2D *texture;
        // < coord > = 1 ako postoji bomba sa tim coord
        // < coord > = 0 suprotno
        inline static unordered_map<int, Node> bombs_x;
        inline static unordered_map<int, Node> bombs_y;
    };
}

#endif // BOMBS_HPP

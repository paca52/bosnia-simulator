#include "bombs.hpp"

using namespace BombNS;

Bomb::Bomb(u_int rows, u_int columns, Texture2D *texture) :texture(texture) {
    u_int cntr = 0; // counter
    while(1) {
        if(cntr == rows * columns * rows * columns) { 
            fprintf(stderr, "ERROR: CAN'T GET COORDINATES FOR A BOMB\n");
            this->x = -1;
            this->y = -1;
            break;
        }

        double tmp_x = rand() % rows;
        double tmp_y = rand() % columns;

        if(bombs_x[tmp_x].value == 0 || bombs_y[tmp_y].value == 0) {
            this->x = tmp_x;
            bombs_x[tmp_x].value++;

            this->y = tmp_y;
            bombs_y[tmp_y].value++;
            break;
        }
        cntr++;
    }

}

// getteri
double Bomb::getX() const { return this->x; }
double Bomb::getY() const { return this->y; }

void Bomb::info() const {
    std::cout << "x(" << this->x << ")" << ", y(" << this->y << ")" << std::endl;
}

void Bomb::draw() const {
    DrawTexture(
        *this->texture,
        this->x * SPACE_X,
        this->y * SPACE_Y,
        RAYWHITE
    );
}

bool Bomb::operator>=(const Bomb& bomb) {
    if(this->x == bomb.x) return this->y > bomb.y;
    else return this->x > bomb.x;
}

Bomb::~Bomb() = default;

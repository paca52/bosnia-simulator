#include "field.hpp"

using namespace FieldNS;

Field::Field(u_int rows, u_int columns, Texture2D *texture, Texture2D *texture_open, Texture2D *flag) 
    :has_a_bomb(false), texture(texture), texture_open(texture_open), open(false), number_of_bombs_around(0), number_texture(nullptr), marked(false), flag(flag) {
    this->y = 0;
    this->x = 0;

    u_int tmp = brojPolja;
    while(tmp >= rows) {
        this->y++;
        tmp -= rows;
    }
    this->x = tmp;

    brojPolja++;
}

//getteri
double Field::getX() const { return this->x; }
double Field::getY() const { return this->y; }
bool Field::getHas_a_bomb() const { return this->has_a_bomb; }
Texture2D Field::getTexture() const { return *this->texture; }
bool Field::getOpen() const { return this->open; }
int Field::getNumberOfBombsAround() const { return this->number_of_bombs_around; }
const Texture2D* Field::getNumberTexture() const { return this->number_texture; }

// setteri
void Field::setBomb(bool has_a_bomb) { this->has_a_bomb = has_a_bomb; }
void Field::setOpen() { this->open = true; }
void Field::setNumberTexture(Texture2D *text) {
    if(this->number_of_bombs_around <= 0) return;
    this->number_texture = text;
}
void Field::setMark() { 
    if(this->open == false)
        this->marked = !this->marked; 
}
void Field::setMark(bool val) { 
    if(this->open == false)
        this->marked = val; 
}

void Field::setNumberOfBombsAround(int num) { this->number_of_bombs_around = num; }
void Field::incNumberOfBombsAround() { this->number_of_bombs_around += 1; }

void Field::info() const {
    std::cout 
        << "x(" << this->x << "), " 
        << "y(" << this->y << "), "
        << "texture(" << ( this->texture == nullptr ) << "), "
        << "number on the filed(" << this->number_of_bombs_around << "), "
        << "has_a_bomb(" << has_a_bomb << ")\n";
}

void Field::draw() const {
    if(this->open == false) {
        DrawTexture(
            *this->texture,
            this->x * SPACE_X,
            this->y * SPACE_Y,
            RAYWHITE
        );
    }
    else {
        DrawTexture(
            *this->texture_open,
            this->x * SPACE_X,
            this->y * SPACE_Y,
            RAYWHITE
        );
        if(this->number_texture != nullptr)
            DrawTexture(
                *this->number_texture,
                this->x * SPACE_X,
                this->y * SPACE_Y,
                RAYWHITE
            );
    }

    if(this->marked) {
        DrawTexture(
            *flag,
            this->x * SPACE_X,
            this->y * SPACE_Y,
            RAYWHITE
        );
    }
}

u_int Field::getBrojPolja() { return brojPolja; }

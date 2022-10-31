#ifndef GRID_HPP
#define GRID_HPP

typedef unsigned int u_int;

#include <vector>
#include <algorithm>
#include "bombs.hpp"
#include "field.hpp"
#include <string>
#include <cstring>

using namespace BombNS;
using namespace FieldNS;

class Grid {
public:
    Grid();

    void oznaci_brojem(double y, double x);
    bool validan_index(double y, double x) const;

    void display() const;
    void bomb_info() const;
    void field_info() const;

    void otvori_polja(double y, double x);
    void otvaraj(double y, double x);
    void mark(double y, double x);

    bool game_over(double y, double x);
    bool win();
    void end();

    ~Grid();
private:
    u_int rows, columns, num_of_bombs, num_of_fileds;
    std::vector<Bomb> bombs;
    Texture *bomb_texture, *field_texture, *field_texture_open;
    std::vector<std::vector<Field>> polja;
    Texture2D *number_textures;
    Texture2D *flag_texture;

    inline static u_int number_of_opened_fields;
};

#endif // GRID_HPP

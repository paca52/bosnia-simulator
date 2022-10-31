#ifndef FIELD_HPP
#define FIELD_HPP

typedef unsigned int u_int;

#include <iostream>
#include "raylib.h"
#include <string>

#define SPACE_Y 32
#define SPACE_X 32

namespace FieldNS {

    class Field {
    public:
        Field(u_int rows, u_int columns, Texture2D *texture, Texture2D *texture_open, Texture2D *flag);

        //getteri
        double getX() const;
        double getY() const;
        bool getHas_a_bomb() const;
        Texture2D getTexture() const;
        bool getOpen() const;
        int getNumberOfBombsAround() const;
        const Texture2D *getNumberTexture() const;

        // setteri
        void setBomb(bool has_a_bomb);
        void setOpen();
        void setNumberTexture(Texture2D *text);
        void setMark();
        void setMark(bool val);
        void setNumberOfBombsAround(int num);
        void incNumberOfBombsAround();

        void info() const;
        void draw() const;

        static u_int getBrojPolja();
    private:
        double x, y;
        bool has_a_bomb;
        Texture2D *texture, *texture_open;
        bool open;
        int number_of_bombs_around; // -1 => is a bomb
        Texture2D *number_texture;
        bool marked;
        Texture2D *flag;
        inline static u_int brojPolja = 0;
    };
};

#endif // FIELD_HPP

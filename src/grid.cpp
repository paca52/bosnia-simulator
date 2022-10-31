#include "grid.hpp"

Grid::Grid() :rows(10), columns(8), num_of_bombs(10), num_of_fileds(rows * columns) {
    // loading textures
    this->bomb_texture = new Texture2D;
    *this->bomb_texture = LoadTexture("textures/bomb.png");

    this->field_texture = new Texture2D;
    *this->field_texture = LoadTexture("textures/field.png");

    this->field_texture_open = new Texture2D;
    *this->field_texture_open = LoadTexture("textures/field_open.png");

    this->number_textures = new Texture2D[8];
    for(int i=0; i<8; i++) {
        this->number_textures[i] = LoadTexture(( "textures/" + std::to_string(i+1) + ".png" ).c_str());
    }

    this->flag_texture = new Texture2D;
    *flag_texture = LoadTexture("textures/flag.png");

    // make bombs
    for(u_int i=0; i<this->num_of_bombs; i++)
        bombs.push_back(
            Bomb(
                this->rows,
                this->columns,
                this->bomb_texture
            )
        );

    // making fields
    for(u_int i=0; i<columns; i++) {
        std::vector<Field> tmp;
        for(u_int j=0; j<rows; j++)
            tmp.push_back(Field(rows, columns, field_texture, field_texture_open, flag_texture));
        polja.push_back(tmp);
    }

    // marking all fields with bombs in them
    for(auto it = bombs.begin(); it != bombs.end(); it++) {
        polja[it->getY()][it->getX()].setBomb(true);
        oznaci_brojem(it->getY(), it->getX());
    }
}


void Grid::oznaci_brojem(double y, double x) {
    /* index = it->getY()  * rows + it->getX(); */
    polja[y][x].setNumberOfBombsAround(-2);
    
    for(int i=-1; i<2; i++)
        for (int j=-1; j<2; j++) {

            if(validan_index(y+i, x+j) == false) continue;

            polja[y+i][x+j].incNumberOfBombsAround();

            polja[y+i][x+j].setNumberTexture(
                &this->number_textures[polja[y+i][x+j].getNumberOfBombsAround() - 1]
            );

        }
}



bool Grid::validan_index(double y, double x) const {
    if(
        x >= 0 && x < rows &&
        y >= 0 && y < columns &&
        polja[y][x].getHas_a_bomb() == false
    ) return true;
    return false;
}


void Grid::display() const {
    for(u_int i=0; i<this->columns; i++)
        for(u_int j=0; j<this->rows; j++)
            polja[i][j].draw();

    for(u_int i=0; i<this->num_of_bombs; i++)
        if(polja[bombs[i].getY()][bombs[i].getX()].getOpen())
            bombs[i].draw();
}


void Grid::bomb_info() const {
    std::cout << "Bombs: \n";
    for(u_int i=0; i<this->num_of_bombs; i++) {
        std::cout << "\t[" << i << "]: "; bombs[i].info();
    }
}


void Grid::field_info() const {
    std::cout << "Polja:\n";
    for(u_int i=0; i<columns; i++) {
        for(u_int j=0; j<rows; j++) {
            std::cout << "\tPolje[" << i << ", " << j << "]: ";
            polja[i][j].info();
        }
        std::cout << "\n";
    }
    std::cout << "Broj Polja: " << Field::getBrojPolja() << "\n";
}


bool Grid::game_over(double y, double x) {
    x /= SPACE_X;
    y /= SPACE_Y;

    x = u_int(x);
    y = u_int(y);

    /* std::cout << "MOUSE PRESSED: " << x << ", " << y << "\n"; */

    /* polja[y][x].info(); */

    polja[y][x].setOpen();
    number_of_opened_fields++;
    if(polja[y][x].getHas_a_bomb())
        return true;

    return false;
}


bool Grid::win() {
    if(number_of_opened_fields == rows * columns - num_of_bombs)
        return true;
    return false;
}

void Grid::otvori_polja(double y, double x) {
    x /= SPACE_X;
    y /= SPACE_Y;

    x = u_int(x);
    y = u_int(y);

    if(polja[y][x].getNumberTexture() == nullptr) {
        this->otvaraj(y, x);
    }
}


void Grid::otvaraj(double y, double x) { 
    for(int i=-1; i<2; i++)
        for (int j=-1; j<2; j++) {
            if( 
                validan_index(y+i, x+j) &&
                polja[y+i][x+j].getNumberTexture() == nullptr &&
                polja[y+i][x+j].getNumberOfBombsAround() == 0 &&
                polja[y+i][x+j].getOpen() == false) 
            {
                polja[y+i][x+j].setOpen();
                number_of_opened_fields++;
                this->otvaraj(y+i, x+j);
            } 
            else if(validan_index(y+i, x+j) &&
                    polja[y+i][x+j].getNumberTexture() != nullptr &&
                    polja[y+i][x+j].getNumberOfBombsAround() > 0 &&
                    polja[y+i][x+j].getOpen() == false) 
            {
                polja[y+i][x+j].setOpen();
                number_of_opened_fields++;
            }
        }
}

void Grid::end() {
    for(u_int i=0; i<columns; i++)
        for(u_int j=0; j<rows; j++)
            polja[i][j].setOpen();
}

void Grid::mark(double y, double x) {
    x /= SPACE_X;
    y /= SPACE_Y;

    x = u_int(x);
    y = u_int(y);

    polja[y][x].setMark();
}

Grid::~Grid() {
    if(this->bomb_texture != nullptr)
        delete this->bomb_texture;

    if(this->field_texture != nullptr)
        delete this->field_texture;

    if(this->number_textures != nullptr)
        delete[] this->number_textures;

    if(this->flag_texture != nullptr)
        delete this->flag_texture;
}

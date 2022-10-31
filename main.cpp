#include "raylib.h"
#include "grid.hpp"
#include "bombs.hpp"
#include "field.hpp"
#include <float.h>

const int screenWidth = 320;
const int screenHeight = 256;

int main(void) {

    // window things
    InitWindow(screenWidth, screenHeight, "minolovac");
    SetTargetFPS(60);

    // vars
    Grid grid;

    /* grid.bomb_info(); */
    /* grid.field_info(); */

    bool GAME_OVER = false;
    bool WIN = false;

    // game loop
    while (!WindowShouldClose()) {

        // end
        if(GAME_OVER) {
            grid.end();
            
            BeginDrawing();
                
                ClearBackground(RAYWHITE);

                grid.display();

            EndDrawing();

            continue;
        } 
        else if(WIN) {
            BeginDrawing();

                ClearBackground(RAYWHITE);

                DrawText("YOU WIN", 50, 50, 20, GREEN);

            EndDrawing();

            continue;
        }

        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            double x = GetMouseX();
            double y = GetMouseY();
            if(grid.game_over(y, x)) {
                GAME_OVER = true;
                continue;
            } else {
                // ako je prazno polje treba da otvori sva susedna polja
                grid.otvori_polja(y, x);
            }
            
            if(grid.win())
                WIN = true;

        } else if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            double x = GetMouseX();
            double y = GetMouseY();
            grid.mark(y, x);
        }

        BeginDrawing();
            
            ClearBackground(RAYWHITE);
         
            grid.display();
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

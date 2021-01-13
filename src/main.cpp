#include "raylib.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "CellMatrix.h"

#define MAX_INPUT_SIZE 26

using namespace std;
enum STATES {
    GET_INPUT,
    EXECUTE,
};
inline int input_box(Rectangle rec, const char *message, std::string &buffer) {
    char keypress;
    int input = 0;
    
    DrawRectangleRec(rec, DARKGRAY);
    DrawText(buffer.c_str(), rec.x, rec.y+10,40,RAYWHITE);

            DrawText(message,
                     rec.x-210, rec.y-25,20, RAYWHITE);

            if (CheckCollisionPointRec(GetMousePosition(), rec)) {
                keypress = GetCharPressed();
                while(keypress > 0) {
                    if ((keypress >= 32) && (keypress <= 125)) {
                        buffer.push_back(keypress);
                    }

                    keypress = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE) && buffer.size() != 0) {
                    buffer.pop_back();
                }


            }
            // DrawRectangleRec(rec, LIGHTGRAY);

            // std::cout << buffer.c_str() << "\n";
}

// using namespace std::chrono_literals;
int main() {
    bool input_validation = false;

    const unsigned int matrix_size = 20;
    const unsigned int screenwidth = 1080;
    const unsigned int screenheight = 920;

    CellMatrix world(matrix_size);

    world.set(10,10,10,true);
    world.set(10,10,11,true);
    world.set(10,10,12,true);

    Rectangle birthbox = { screenwidth/2-90, 180, 90, 50 };
    Rectangle survivalbox = { screenwidth/2 - 90,420,90,50 };
    InitWindow(1080,920,"Cellular automaton");
    // MaximizeWindow();
    // ToggleFullscreen();
    Vector3 origin {0,0,0};
    Camera3D camera = { 0 };
    camera.position = (Vector3) {
        10.0f, 10.0f,  (float)matrix_size * 2.0+1
    };
    camera.target = origin;
    camera.up = (Vector3) {
        0.0f, 3.0f, 0.0f
    };
    camera.fovy = 45.0f;
    camera.type = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);

    int cubecount = 0;
    Vector3 pos;
    int x,y,z;
    STATES state = STATES::GET_INPUT;
    SetCameraMode(camera, CAMERA_ORBITAL);

    //2D VARIABLES' INSTANTIATION
    std::string birth_range_input, survival_range_input;
    unsigned int ticks = 0;
    float something = 1.0 / matrix_size;
    const int matrix_to_byte = (255/matrix_size);

    int keypress; // var to store character inputs
    while(!WindowShouldClose()) {

        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(BLACK);

        switch(state) {

        case STATES::GET_INPUT: {

            input_box(birthbox, "Lmao wong?", birth_range_input);
            break;
        }
        
        case STATES::EXECUTE: {
            BeginMode3D(camera);
            //Iterate through every cell
            for (x=0; x<matrix_size; x++) {
                for (y=0; y<matrix_size; y++) {
                    for (z=0; z<matrix_size; z++) {
                        if (world.get_cell(x,y,z)) {
                            world.count_neightbors(x,y,z);

                            pos.y = (float) y - ((float)matrix_size)/2.0;
                            pos.x = (float) x - ((float)matrix_size)/2.0;
                            pos.z = (float) z - ((float)matrix_size)/2.0;

                            // DrawRectanglePro((Rectangle){})

                            DrawCube(pos,1,1,1, (Color) {
                                matrix_to_byte *pos.z,matrix_to_byte*pos.y,matrix_to_byte*pos.x,255
                            });
                            DrawCubeWires(pos,1,1,1,BLACK);
                        }
                    }
                }
            }
            ticks++;
            if (ticks % 20 == 0) {
                world.evolve();
                ticks = 0;
            }
            EndMode3D();
            break;
        }
        }


        EndDrawing();
    }
    CloseWindow();
    return 0;
}


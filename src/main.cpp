#include "raylib.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "CellMatrix.h"

#define MAX_INPUT_SIZE_DIGITS 2

using namespace std;
enum STATES {
    GET_INPUT,
    EXECUTE,
};

inline int input_box(Rectangle rec, const char *message, std::string &buffer) {
    char keypress;
    int input = 0;

    DrawRectangleRec(rec, DARKGRAY);
    DrawText(buffer.c_str(), rec.x+10, rec.y+5,40,RAYWHITE);

    DrawText(message,
             rec.x-210, rec.y-25,20, RAYWHITE);

    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        keypress = GetCharPressed();
        while(keypress > 0) {
            if ((keypress >= 32) && (keypress <= 125 && (buffer.size() < MAX_INPUT_SIZE_DIGITS))) {
                buffer.push_back(keypress);
            }

            keypress = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && buffer.size() != 0) {
            buffer.pop_back();
        }


    }

}

// using namespace std::chrono_literals;
int main() {
    bool input_validation = false;
    const unsigned int matrix_size = 20;
    const unsigned int screenwidth = 1080;
    const unsigned int screenheight = 920;

    Rectangle start_button {screenwidth/2-90, 600, 90, 30}; 
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
    unsigned int ticks = 0;

    
    std::string birth_range_input, survival_range_input;
    birth_range_input = to_string(world.get_birth_edge());
    survival_range_input = to_string(world.get_survival_edge());

    float something = 1.0 / matrix_size;
    const int matrix_to_byte = (255/matrix_size);

    int keypress; // var to store character inputs
    while(!WindowShouldClose()) {

        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(BLACK);

        switch(state) {

        // This screen gathers input form user
        case STATES::GET_INPUT: {

            input_box(birthbox, "Enter max num of neightbors required to become alive", birth_range_input);
            input_box(survivalbox, "Enter max number a living cell can have", survival_range_input);

            if (CheckCollisionPointRec(GetMousePosition(), start_button)) {
                
                DrawRectangleRec(start_button, PINK);

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

                    world.set_survival_edge(stoi(survival_range_input));

                    world.set_birth_edge(stoi(birth_range_input));
                    
                    state = STATES::EXECUTE; 
                    // std::cout << world.get_birth_edge() << " " << world.get_survival_edge() << "\n";
                }
            } else {
                DrawRectangleRec(start_button, RED);
            }

            DrawText("START", start_button.x+10, start_button.y+5,20,RAYWHITE);
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


#include "raylib.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "CellMatrix.h"
using namespace std;
// using namespace std::chrono_literals;
int main() {
    bool input_validation = false;
    // int matrix_size;
    // do {
    //     std::cout << "Enter a matrix size: ";
    //     std::cin >> matrix_size;
        
    // } while(!input_validation);

    // matrix indexing is [y][x]
    const int matrix_size = 20;
 
    CellMatrix world(matrix_size);
    world.set(10,10,10,true);
    world.set(10,10,11,true);
    world.set(10,10,12,true);
   

    InitWindow(1080,920,"Cellular automaton");
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
    SetCameraMode(camera, CAMERA_ORBITAL);

    // Color transparent_red{255,0,0,200};
    unsigned int ticks = 0;
    float something = 1.0 / matrix_size;
    const int matrix_to_byte = (255/matrix_size);
    while(!WindowShouldClose()) {
        // std::cout << start_time << "\n";
        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        
        DrawCubeWires(origin, matrix_size+1, matrix_size+1, matrix_size+1, RAYWHITE);
        //Iterate through every cell
        for (x=0;x<matrix_size; x++) {
            for (y=0; y<matrix_size; y++) {
                for (z=0;z<matrix_size; z++) {
                    if (world.get_cell(x,y,z)) {
                        world.count_neightbors(x,y,z);

                        pos.y = (float) y - ((float)matrix_size)/2.0;
                        pos.x = (float) x - ((float)matrix_size)/2.0;
                        pos.z = (float) z - ((float)matrix_size)/2.0;

                        // DrawRectanglePro((Rectangle){})
                        
                        DrawCube(pos,1,1,1, (Color) {matrix_to_byte *pos.z,matrix_to_byte*pos.y,(255/matrix_size)*pos.x,255});
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

        EndDrawing();
    }
    CloseWindow();
    return 0;
}


#include "raylib.h"
#include <iostream>
#include <vector>
// #include <list>
#include <thread>
#include <chrono>
#include "CellMatrix.h"
using namespace std;
// using namespace std::chrono_literals;
int main() {
    bool input_validation = false;
    // do {
    //     std::cout << "Enter a matrix size"
    // } while(!input_validation);
    
    // matrix indexing is [y][x]
    const int matrix_size = 10;
 
    CellMatrix world(matrix_size);
    world.set(0,1,2,true);
    world.set(0,1,1,true);
    world.set(0,0,1,true);

    InitWindow(1080,920,"Cellular automaton");
    Vector3 origin {0,0,0};
    Camera3D camera = { 0 };
    camera.position = (Vector3) {
        10.0f, 10.0f,  (float)matrix_size * 2.0
    };  
    camera.target = origin;   
    camera.up = (Vector3) {
        0.0f, 1.0f, 0.0f
    };          
    camera.fovy = 45.0f;                                
    camera.type = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);

    int cubecount = 0;
    Vector3 pos;
    int x,y,z;
    // Color blorange {255,0,0,120};
    Color transparent_red{255,0,0,200};
    while(!WindowShouldClose()) {
        
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
                        
                        DrawCube(pos,1,1,1, transparent_red);
                        DrawCubeWires(pos,1,1,1,BLACK);
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        world.evolve();

        EndMode3D();

        // DrawFPS(10, 10);
        // DrawText("Cell matrix",10,20,10,GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}


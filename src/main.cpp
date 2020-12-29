#include "raylib.h"
#include <iostream>
#include <vector>
#include <list>
#include "CellMatrix.h"
using namespace std;

int main() {
    // matrix indexing is [y][x]
    int matrix_size = 10;
    // cin >> matrix_size;
    vector<vector<bool>> matrix (matrix_size, vector<bool>(matrix_size, false));
    list<pair<unsigned int, unsigned int>> to_be_rendered {
        make_pair(0,0),
        
    };
    // lmao
    // vector<vector<vector<bool > > >  matrix;


    CellMatrix test(10);
    test.set(0,0,1,true);
    test.set(0,1,1,true);
    test.set(1,0,1,true);

    matrix[0][1] = true;
    for (auto vec : matrix) {
        for (auto i : vec) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }

    InitWindow(1080,920,"Cellular automaton");

    Camera3D camera = { 0 };
    camera.position = (Vector3) {
        10.0f, 10.0f, 20.0f
    };  // Camera position
    camera.target = (Vector3) {
        0.0f, 0.0f, 0.0f
    };      // Camera looking at point
    camera.up = (Vector3) {
        0.0f, 1.0f, 0.0f
    };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;
    SetTargetFPS(60);
    Vector3 origin {0,0,0};
    int cubecount = 0;
    Vector3 pos;
    int x,y,z;
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);
        DrawCubeWires(origin, matrix_size+1, matrix_size+1, matrix_size+1, RAYWHITE);
        // DrawCube(Vector3{-matrix_size/2,-matrix_size/2,0},1,1,1,RED);

        // for (vector<)

        for (x=0;x<matrix_size; x++) {
            for (y=0; y<matrix_size; y++) {
                for (z=0;z<matrix_size; z++) {
                    if (test.get_substrate()[z][y][x]) {
                        test.count_neightbors(x,y,z);

                        pos.y = (float) y - ((float)matrix_size)/2.0;
                        pos.x = (float) x - ((float)matrix_size)/2.0;
                        pos.z = (float) z - ((float)matrix_size)/2.0;
                        
                        DrawCube(pos,1,1,1,RED);
                        DrawCubeWires(pos,1,1,1,BLACK);
                    }
                }
            }
        }

        // for (auto coord : to_be_rendered) {

        //     pos.y = (float) coord.second - ((float)matrix_size)/2.0;
        //     pos.x = (float) coord.first - ((float)matrix_size)/2.0;
        //     pos.z = 0;
        //     DrawCube(pos,1,1,1,RED);
        //     DrawCubeWires(pos,1,1,1,BLACK);
        // }
        EndMode3D();

        DrawFPS(10, 10);
        // DrawText("Cell matrix",10,20,10,GREEN);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}


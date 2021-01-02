#pragma once
#include <vector>
#include <iostream>

// using namespace std;
using uint = unsigned int;


class CellMatrix {
public:
    CellMatrix(uint size);
    void set(uint x, uint y, uint z, bool state);
    // void spin();
    bool get_cell(uint x, uint y, uint z);
    uint get_size();
    inline uint count_neightbors(uint x,uint y,uint z);
    void evolve();

private:
    uint size;
    std::vector<std::vector<std::vector<bool>>>* current_world;
    std::vector<std::vector<std::vector<bool>>>* next_world;
    std::vector<std::vector<std::vector<bool>>> alpha, beta;
    bool mat_turn;
};

CellMatrix::CellMatrix(uint size) : alpha(
        size,
        std::vector<std::vector<bool>> (
            size,
            std::vector<bool>(size, false)
        )
    ), beta(
        size,
        std::vector<std::vector<bool>> (
            size,
            std::vector<bool>(size, false)
        )
    ),
    mat_turn(false) {
    this->size = size;
    current_world = &alpha;
    next_world = &beta;
    // substrate
}

inline uint CellMatrix::count_neightbors(uint x,uint y,uint z) {
    uint neightbors = 0;
    for (int xi=-1; xi<2; xi++) {
        for (int yi=-1; yi<2; yi++) {
            for (int zi=-1; zi<2; zi++) {
                //bound checking
                if (xi+x >= 0 && xi+x < size && yi+y >= 0 && yi+y < size && zi+z >= 0 && zi+z < size) {
                    if (current_world->at(zi+z)[yi+y][xi+x]) {
                        // std::cout << "alive!" << "\n";
                        neightbors++;
                    }
                } else {
                    continue;
                }
            }
        }
    }

    // if (neightbors > 0)
        // std::cout << neightbors;
    return neightbors;
}

void CellMatrix::set(uint x, uint y, uint z, bool state) {
    if(x >= 0 && y >= 0 && z >= 0 && x < size && y < size && z < size) {
        // substrate[z][y][x] = state;
        current_world->at(z)[y][x] = state;
    }
}

bool CellMatrix::get_cell(uint x, uint y, uint z) {
    return current_world->at(z)[y][x];
}

inline uint CellMatrix::get_size() {
    return size;
}

void CellMatrix::evolve() {
    uint x,y,z;
    int neightbors;
    for (x=0;x<size;x++) {
        for (y=0; y<size; y++) {
            for (z=0; z<size; z++) {
                neightbors = count_neightbors(x,y,z);
                // RULE
                if (neightbors < 2 || neightbors >= 4) {
                    next_world->at(z)[y][x] = false;
                } else 
                    next_world->at(z)[y][x] = true;
                // if (neightbors > 2 &&)cout
                
            }
        }
    }
    auto temp = current_world;
    current_world = next_world;
    next_world = current_world;
}
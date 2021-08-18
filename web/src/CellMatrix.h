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
    
    void set_survival_edge(uint n);
    uint get_survival_edge();

    void set_birth_edge(uint n);
    uint get_birth_edge();

    inline uint count_neightbors(uint x,uint y,uint z);
    void evolve();

private:
    uint size;

    std::vector<std::vector<std::vector<bool>>> alpha, beta;
    // Default ranges for rule enforcement
    uint birth_edge = 2;
    uint survival_edge = 5;
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

}

inline uint CellMatrix::count_neightbors(uint x,uint y,uint z) {
    int neightbors = 0;
    for (int xi=-1; xi<2; xi++) {
        for (int yi=-1; yi<2; yi++) {
            for (int zi=-1; zi<2; zi++) {
                //bound checking
                if (xi+x >= 0 && xi+x < size && yi+y >= 0 && yi+y < size && zi+z >= 0 && zi+z < size) {
                    if (alpha[zi+z][yi+y][xi+x]) {
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
        alpha[z][y][x] = state;
    }
}

bool CellMatrix::get_cell(uint x, uint y, uint z) {
    return alpha[z][y][x];
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
                if (neightbors < birth_edge || neightbors > survival_edge) {
                    beta[z][y][x] = false;
                } else {
                    beta[z][y][x] = true;
                }
                
            }
        }
    }
    
    std::swap(alpha,beta);
}

void CellMatrix::set_survival_edge(uint n) {
    //Moore neighborhood of a cube allows for 26 neighbors tops
    if (n > 26) 
        n = 26;

    this->survival_edge = n;
}

void CellMatrix::set_birth_edge(uint n) {
    if (n>26)
        n=26;
    this->birth_edge = n;
}

uint CellMatrix::get_survival_edge() {
    return this->survival_edge;
}

uint CellMatrix::get_birth_edge() {
    return this->birth_edge;
}
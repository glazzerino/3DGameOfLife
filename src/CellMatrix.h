#pragma once
#include <vector>
// using namespace std;
using uint = unsigned int;


class CellMatrix {
public:
    CellMatrix(uint size);
    void set(uint x, uint y, uint z, bool state);
    void spin();
    const std::vector<std::vector<std::vector<bool>>>& get_substrate();
    uint get_size();
    inline uint count_neightbors(uint x,uint y,uint z);

private:
    uint size;
    std::vector<std::vector<std::vector<bool>>> substrate;
    std::vector<std::vector<std::vector<bool>>> alpha, beta;
    bool mat_turn;
};

CellMatrix::CellMatrix(uint size) : substrate(
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
    mat_turn(false)
{
    this->size = size;
    // substrate
}

inline uint CellMatrix::count_neightbors(uint x,uint y,uint z) {
    uint neightbors = 0;
    for (int xi=-1; xi<2; xi++) {
        for (int yi=-1; yi<2; yi++) {
            for (int zi=-1; zi<2; zi++) {
                //bound checking
                if (xi+x >= 0 && xi+x < size && yi+y >= 0 && yi+y < size && zi+z >= 0 && zi+z < size) {
                    if (this->substrate[zi+z][yi+y][xi+x]) {
                        // std::cout << "alive!" << "\n";
                        neightbors++;
                    }
                } else {
                    continue;
                }
            }
        }
    }

    if (neightbors > 0)
        std::cout << neightbors;
    return neightbors;
}

void CellMatrix::set(uint x, uint y, uint z, bool state) {
    if(x >= 0 && y >= 0 && z >= 0 && x < size && y < size && z < size) {
        this->substrate[z][y][x] = state;
    }
}

const std::vector<std::vector<std::vector<bool>>>& CellMatrix::get_substrate() {
    return this->substrate;
}

inline uint CellMatrix::get_size() {
    return size;
}
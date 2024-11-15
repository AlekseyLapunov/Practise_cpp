#include <iostream>
#include <vector>
#include <chrono>

#include "heavy_to_copy.hpp"
#include "util.hpp"

namespace config {

const size_t samples    = 100;
const size_t stringLen  = 1024;
const size_t secondsEta = 30;

}

int main() {
    // Copy section
    std::vector<HeavyToCopy> htc;
    htc.resize(config::samples);
    for (size_t i = 0; i < htc.size(); i++) {
        htc[i] = HeavyToCopy{ util::randomString(config::stringLen) };
    }

    auto start = std::chrono::high_resolution_clock::now();
    size_t opCountCopy = 0;

    std::cout << "Counting on Copy...\n";
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < config::secondsEta) {
        decltype(htc) dummy = htc;
        while (!dummy.empty()) {
            dummy.erase(dummy.begin());
            opCountCopy++;
        }
    }

    std::cout << "HTC (Copy) operations =\t" << opCountCopy << "\n"; // 76633500

    // Move section
    std::vector<HeavyToCopy_Move> htc_move;
    htc_move.resize(config::samples);
    for (size_t i = 0; i < htc_move.size(); i++) {
        htc_move[i] = HeavyToCopy_Move{ util::randomString(config::stringLen)};
    }

    start = std::chrono::high_resolution_clock::now();
    size_t opCountMove = 0;

    std::cout << "Counting on Move...\n";
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() < config::secondsEta) {
        decltype(htc_move) dummy = htc_move;
        while (!dummy.empty()) {
            dummy.erase(dummy.begin());
            opCountMove++;
        }
    }

    std::cout << "HTC (Move) operations =\t" << opCountMove << "\n"; // 234355450

    std::cout << "Ratio (Move : Copy)   =\t" << (float)((float)opCountMove/opCountCopy) << "\n";
}
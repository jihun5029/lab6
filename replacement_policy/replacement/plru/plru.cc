#include "plru.h"
#include <algorithm>
#include <cmath>

PLRU::PLRU(size_t associativity) : associativity(associativity) {
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

bool PLRU::find_block(std::list<uint64_t>& set, uint64_t block_addr) {
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

void PLRU::replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) {
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

void PLRU::update_tree_on_access(size_t index) {
    // Update the tree structure based on the accessed index
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

size_t PLRU::get_plru_index() {
    // Traverse the tree to find the PLRU index
    // You must complete this section of the code //   
    // Above //

    // Below //   
}

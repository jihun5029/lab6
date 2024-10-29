#include "fifo.h"

bool FIFO::find_block(std::list<uint64_t>& set, uint64_t block_addr) {

    for (auto& block : set) {
        if (block == block_addr) {
            return true;
        }
    }
    return false;
}

void FIFO::replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) {
    if (set.size() >= associativity) {
        set.pop_front();  // 가장 먼저 들어온 블록을 제거
    }
    set.push_back(block_addr);  // 새로운 블록 추가
}

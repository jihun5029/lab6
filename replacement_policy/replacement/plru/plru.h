#ifndef PLRU_H
#define PLRU_H

#include "../../replacement_policy.h"
#include <vector>
#include <list>

class PLRU : public ReplacementPolicy {
public:
    PLRU(size_t associativity);
    
    bool find_block(std::list<uint64_t>& set, uint64_t block_addr) override;
    void replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) override;

private:
    size_t associativity;
    std::vector<bool> plru_tree;  // Tree-based PLRU structure

    void update_tree_on_access(size_t index);
    size_t get_plru_index();
};

#endif  // PLRU_H

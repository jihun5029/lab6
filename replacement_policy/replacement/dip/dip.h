#ifndef DIP_H
#define DIP_H

#include "../../replacement_policy.h"
#include "lru.h"
#include "bip.h"
#include <list>

class DIP : public ReplacementPolicy {
public:
    DIP();

    bool find_block(std::list<uint64_t>& set, uint64_t block_addr) override;
    void replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) override;

private:
    // You must complete this section of the code //   
    // Above //

    // Below //   
};

#endif  // DIP_H

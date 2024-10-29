#ifndef BIP_H
#define BIP_H

#include "../../replacement_policy.h"
#include <list>
#include <random>

class BIP : public ReplacementPolicy {
public:
    BIP();

    bool find_block(std::list<uint64_t>& set, uint64_t block_addr) override;
    void replace_block(std::list<uint64_t>& set, uint64_t block_addr, size_t associativity) override;

private:
    // You must complete this section of the code //   
    // Above //

    // Below //   
};

#endif  // BIP_H

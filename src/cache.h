#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <iostream>
#include <memory>
#include <list>
#include "../replacement_policy/replacement_policy.h"

class CacheHierarchy {
public:
    CacheHierarchy(size_t l1_size, size_t l1_block_size, size_t l1_assoc, size_t l2_size, size_t l2_block_size, size_t l2_assoc, 
                   std::shared_ptr<ReplacementPolicy> rp1, std::shared_ptr<ReplacementPolicy> rp2, const std::string& cache_policy);

    bool l1_access(uint64_t mem_addr);
    bool l2_access(uint64_t mem_addr);
    void memory_access(uint64_t mem_addr);

private:
    class Cache {
    public:
        Cache(size_t size, size_t block_size, size_t associativity, std::shared_ptr<ReplacementPolicy> rp);

        bool access(uint64_t mem_addr);
        void add(uint64_t mem_addr);
        void remove(uint64_t mem_addr);

    private:
        size_t size;
        size_t block_size;
        size_t associativity;
        size_t num_sets;
        std::vector<std::list<uint64_t>> cache;
        std::shared_ptr<ReplacementPolicy> rp;
    };

    Cache l1_cache;
    Cache l2_cache;
    std::string cache_policy;

    int l1_hits;
    int l1_misses;
    int l2_hits;
    int l2_misses;

    void handle_inclusive_policy(uint64_t mem_addr);
    void handle_exclusive_policy(uint64_t mem_addr);
};

#endif  // CACHE_H

#include "cache.h"

// CacheHierarchy 생성자
CacheHierarchy::CacheHierarchy    
    // You must complete this section of the code //   
    // Above //

    // Below //  

// Cache 생성자
CacheHierarchy::Cache::Cache(size_t size, size_t block_size, size_t associativity, std::shared_ptr<ReplacementPolicy> rp)
    : size(size), block_size(block_size), associativity(associativity), num_sets(size / (block_size * associativity)), rp(rp) {
    cache.resize(num_sets);
}

void CacheHierarchy::memory_access(uint64_t mem_addr) {
    if (cache_policy == "inclusive") {
        handle_inclusive_policy(mem_addr);
    } else if (cache_policy == "exclusive") {
        handle_exclusive_policy(mem_addr);
    }
}


bool CacheHierarchy::l1_access(uint64_t mem_addr) {
    return l1_cache.access(mem_addr);
}


bool CacheHierarchy::l2_access(uint64_t mem_addr) {
    return l2_cache.access(mem_addr);
}


bool CacheHierarchy::Cache::access(uint64_t mem_addr) {
    uint64_t block_addr = mem_addr / block_size;
    uint64_t set_index = block_addr % num_sets;
    auto& set = cache[set_index];

    return rp->find_block(set, block_addr);
}

void CacheHierarchy::Cache::add(uint64_t mem_addr) {
    uint64_t block_addr = mem_addr / block_size;
    uint64_t set_index = block_addr % num_sets;
    auto& set = cache[set_index];

    rp->replace_block(set, block_addr, associativity);
}

    // (exclusive 정책에 필요)
void CacheHierarchy::Cache::remove(uint64_t mem_addr) {
    // You must complete this section of the code //   
    // Above //

    // Below //  
}


void CacheHierarchy::handle_inclusive_policy(uint64_t mem_addr) {
    // You must complete this section of the code //   
    // Above //

    // Below //  
}

void CacheHierarchy::handle_exclusive_policy(uint64_t mem_addr) {
    // You must complete this section of the code //   
    // Above //

    // Below //  
}
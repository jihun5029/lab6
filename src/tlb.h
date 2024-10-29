#ifndef TLB_H
#define TLB_H

#include <unordered_map>

class TLB {
public:
    TLB(unsigned long size);

    int translate(uint64_t virtual_page);
    void add_entry(uint64_t virtual_page, int physical_page);

private:
    size_t size;
    std::unordered_map<uint64_t, int> tlb;
};

#endif  // TLB_H

#include "tlb.h"

// Translate virtual address

TLB::TLB(unsigned long size) : size(size) {
    // 초기화 작업
}

int TLB::translate(uint64_t virtual_page) {
    if (tlb.find(virtual_page) != tlb.end()) {
        return tlb[virtual_page];
    }
    return -1;
}

// Add entry to TLB
void TLB::add_entry(uint64_t virtual_page, int physical_page) {
    if (tlb.size() >= size) {
        tlb.erase(tlb.begin());  // Remove the oldest entry if TLB is full
    }
    tlb[virtual_page] = physical_page;
}

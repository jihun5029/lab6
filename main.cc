#include "src/cache.h"
#include "src/tlb.h"
#include "trace_read/tracereader.h"
#include "replacement_policy/replacement_policy.h"
#include "replacement_policy/replacement/fifo/fifo.h"
#include "replacement_policy/replacement/lru/lru.h"
#include "replacement_policy/replacement/dip/dip.h"
#include "replacement_policy/replacement/bip/bip.h"
#include "replacement_policy/replacement/plru/plru.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <memory>
#include <fstream>

// nlohmann/json namespace alias
using json = nlohmann::json;


void save_results(const std::string& output_file, const Instruction& instr) {
    std::ofstream ofs(output_file, std::ios::app); // append 모드로 파일 열기
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output_file);
    }

    ofs << "IP: " << instr.ip << ", Opcode: " << instr.opcode
        << ", Src Reg: " << instr.src_reg << ", Dst Reg: " << instr.dst_reg
        << ", Mem Addr: " << instr.mem_addr << ", Mem Size: " << instr.mem_size
        << ", Is Branch: " << instr.is_branch << ", Branch Taken: " << instr.branch_taken
        << ", L1 Cache Hit: " << instr.cache_l1_hit << ", L1 Cache Miss: " << instr.cache_l1_miss
        << ", L2 Cache Hit: " << instr.cache_l2_hit << ", L2 Cache Miss: " << instr.cache_l2_miss << "\n";

    ofs.close();
}

void save_final_results(const std::string& output_file, int l1_hits, int l1_misses, int l2_hits, int l2_misses, int l2_accesses) {
    std::ofstream ofs(output_file, std::ios::app);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open output file: " + output_file);
    }

    ofs << "\nFinal Cache Statistics:\n";
    ofs << "L1 Cache Hit Rate: " << (static_cast<double>(l1_hits) / (l1_hits + l1_misses)) * 100 << "%\n";
    ofs << "L1 Cache Miss Rate: " << (static_cast<double>(l1_misses) / (l1_hits + l1_misses)) * 100 << "%\n";

    if (l2_accesses > 0) {
        ofs << "L2 Cache Hit Rate: " << (static_cast<double>(l2_hits) / l2_accesses) * 100 << "%\n";
        ofs << "L2 Cache Miss Rate: " << (static_cast<double>(l2_misses) / l2_accesses) * 100 << "%\n";
    } else {
        ofs << "L2 Cache was never accessed.\n";
    }

    ofs.close();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>\n";
        return 1;
    }

    std::string config_file = argv[1];
    
    // JSON 파일 읽기
    std::ifstream input_file(config_file);
    if (!input_file.is_open()) {
        std::cerr << "Failed to open config file: " << config_file << "\n";
        return 1;
    }

    json config;
    input_file >> config;

    // You must complete this section of the code //   
    // Above //

    // Below //  

    int l1_hits = 0, l1_misses = 0, l2_hits = 0, l2_misses = 0;
    int total_instructions = 0, l2_accesses = 0;

    while (reader.get_next_instruction(instr)) {

        int physical_page = tlb.translate(instr.mem_addr / block_size);
        if (physical_page == -1) {
            physical_page = instr.mem_addr / block_size;
            tlb.add_entry(instr.mem_addr / block_size, physical_page);
        }


        if (cache_hierarchy.l1_access(physical_page * block_size)) {
            instr.cache_l1_hit = true;
            instr.cache_l1_miss = false;
            instr.cache_l2_hit = false;
            instr.cache_l2_miss = false;
            l1_hits++;
        } else {
            instr.cache_l1_hit = false;
            instr.cache_l1_miss = true;
            l1_misses++;
            l2_accesses++;  

            if (cache_hierarchy.l2_access(physical_page * block_size)) {
                instr.cache_l2_hit = true;
                instr.cache_l2_miss = false;
                l2_hits++;
            } else {
                instr.cache_l2_hit = false;
                instr.cache_l2_miss = true;
                l2_misses++;
                cache_hierarchy.memory_access(physical_page * block_size);
            }
        }

        total_instructions++;
        save_results(output_file, instr);  
    }

    // 최종 캐시 통계 저장
    save_final_results(output_file, l1_hits, l1_misses, l2_hits, l2_misses, l2_accesses);

    return 0;
}

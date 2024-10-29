#ifndef TRACEREADER_H
#define TRACEREADER_H

#include <fstream>
#include <string>

struct Instruction {
    uint64_t ip;
    int opcode;
    int src_reg;
    int dst_reg;
    uint64_t mem_addr;
    int mem_size;
    bool is_branch;
    bool branch_taken;

    bool cache_l1_hit;
    bool cache_l1_miss;
    bool cache_l2_hit;
    bool cache_l2_miss;
};

class TraceReader {
public:
    TraceReader(const std::string& trace_file);
    ~TraceReader();

    bool get_next_instruction(Instruction& instr);

private:
    std::ifstream trace_stream;
};

#endif  // TRACEREADER_H

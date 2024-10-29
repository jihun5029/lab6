#include "tracereader.h"
#include <fstream>

TraceReader::TraceReader(const std::string& trace_file) {
    trace_stream.open(trace_file);
}

TraceReader::~TraceReader() {
    if (trace_stream.is_open()) {
        trace_stream.close();
    }
}

bool TraceReader::get_next_instruction(Instruction& instr) {
    if (trace_stream >> instr.ip >> instr.opcode >> instr.src_reg >> instr.dst_reg >> instr.mem_addr
                     >> instr.mem_size >> instr.is_branch >> instr.branch_taken) {
        return true;
    }
    return false;
}

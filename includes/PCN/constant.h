#ifndef PCN_CONSTANT
#define PCN_CONSTANT
#include <unordered_map>
#include <string>
#include <vector>
#include <kasio/generic/protocal_type.h>

namespace PCN {
    enum class INPUT_TYPE { HTTPS, HTTP, TCP, UDP, IMCP, STOP, EXIT, ALL, ETHHDR, IP , ICMP};

    std::unordered_map<std::string, INPUT_TYPE>  STATE_MENT({
        {"https", INPUT_TYPE::HTTPS},
        {"http", INPUT_TYPE::HTTP},
        {"tcp", INPUT_TYPE::TCP},
        {"imcp", INPUT_TYPE::IMCP},
        {"stop", INPUT_TYPE::STOP},
        {"exit", INPUT_TYPE::EXIT},
        {"start", INPUT_TYPE::ALL},
        {"ethhdr",INPUT_TYPE::ETHHDR},
        {"ip",INPUT_TYPE::IP},
        {"icmp",INPUT_TYPE::ICMP}
        });

}


#endif
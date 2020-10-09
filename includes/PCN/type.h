#ifndef PCN_TYPE
#define PCN_TYPE
#include <unordered_map>
#include <string>
#include <vector>
#include <kasio/generic/protocal_type.h>

namespace PCN {
    class Packet {
    public:
        Packet(std::vector<char> packet) {
            this->raw_packet = packet;

            ethhder = new kasio::Ethhdr();
            iphdr = nullptr;
            memcpy(&(*ethhder), &(packet[0]), sizeof(kasio::Ethhdr));

            const int ipRequireMinSize = sizeof(kasio::Ethhdr) + sizeof(kasio::Iphdr);


            if (ipRequireMinSize <= packet.size()) {
                iphdr = new kasio::Iphdr();
                memcpy(&(*iphdr), &(packet[sizeof(kasio::Ethhdr)]), sizeof(kasio::Ethhdr));
            }





        }
        std::vector<char> raw_packet;
        kasio::Ethhdr* ethhder;
        kasio::Iphdr* iphdr;

    };
}


#endif
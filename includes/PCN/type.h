#ifndef PCN_TYPE
#define PCN_TYPE
#include <unordered_map>
#include <string>
#include <vector>
#include <kasio/generic/protocal_type.h>

namespace PCN {

    enum class IP_TYPE  {
        UNKNOW = -1,
        ICMP = 1 ,
        TCP = 6,
        UDP = 11
    };
    class Packet {
    public:
        Packet(std::vector<char> packet) {

            ethhder = new kasio::Ethhdr();
            iphdr = nullptr;
            memcpy(&(*ethhder), &(packet[0]), sizeof(kasio::Ethhdr));

            const int ipRequireMinSize = sizeof(kasio::Ethhdr) + sizeof(kasio::Iphdr);


            if (ipRequireMinSize <= packet.size()) {
                iphdr = new kasio::Iphdr();
                memcpy(&(*iphdr), &(packet[sizeof(kasio::Ethhdr)]), sizeof(kasio::Iphdr));                
                
                auto transportIndex = ipRequireMinSize;
                TransportPacket = std::move(std::vector<char>(
                    packet.begin() + transportIndex,
                    packet.end()));
            }

        }
        
        IP_TYPE GetIpProtocalType() {
            if (iphdr == nullptr) {
                return IP_TYPE::UNKNOW;
            }
            return (IP_TYPE)iphdr->protocol;
        }
        std::vector<char>& GetTransportPacket() {
            return TransportPacket;
        }
        ~Packet() {
            if (ethhder != nullptr)
                delete ethhder;
            if (iphdr != nullptr)
                delete iphdr;

        }

        std::vector<char> TransportPacket;
        kasio::Ethhdr* ethhder;
        kasio::Iphdr* iphdr;
        IP_TYPE iptype;
    };
}


#endif
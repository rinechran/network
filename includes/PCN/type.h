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
                
                iptype = static_cast<IP_TYPE>(iphdr->protocol);
                auto transportIndex = ipRequireMinSize;

                if (iptype == IP_TYPE::TCP) {

                }
                switch (iptype)
                {
                case IP_TYPE::TCP:
                    tcpdr = new kasio::tcphdr();
                    memcpy(&(*iphdr), &(packet[transportIndex]), sizeof(kasio::tcphdr));

                    std::move(std::vector<char>(
                        packet.begin() + transportIndex,
                        packet.end()));


                    break;
                case IP_TYPE::UDP:

                default:
                    break;
                }

                TransportPacket = std::move(std::vector<char>(
                    packet.begin() + transportIndex,
                    packet.end()));
            }

        }
        Packet(const Packet& packet) {
            TransportPacket = packet.TransportPacket;
            if (packet.ethhder != nullptr) {
                ethhder = new kasio::Ethhdr();
                memcpy(ethhder, packet.ethhder, sizeof(kasio::Ethhdr));
            }
            if (packet.iphdr != nullptr) {
                iphdr = new kasio::Iphdr();
                memcpy(iphdr, packet.iphdr, sizeof(kasio::Iphdr));
            }
        }
        Packet operator=(Packet) = delete;
        
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
        kasio::tcphdr* tcpdr;
        kasio::udphdr* udpdr;

        IP_TYPE iptype;
    };
}


#endif
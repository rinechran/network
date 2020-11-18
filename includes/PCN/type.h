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
        UDP = 17
    };
    class Packet {
    public:
        Packet(std::vector<char> packet)  :iphdr(nullptr), tcpdr(nullptr) , udpdr(nullptr){

            ethhder = new kasio::Ethhdr();
            memcpy(&(*ethhder), &(packet[0]), sizeof(kasio::Ethhdr));

            const int ipRequireMinSize = sizeof(kasio::Ethhdr) + sizeof(kasio::Iphdr) ;

            if (ipRequireMinSize <= packet.size()) {
                iphdr = new kasio::Iphdr();
                memcpy(&(*iphdr), &(packet[sizeof(kasio::Ethhdr)]), sizeof(kasio::Iphdr));                
                
                iptype = static_cast<IP_TYPE>(iphdr->protocol);

                switch (iptype)
                {
                case IP_TYPE::TCP:
                    {
                    tcpdr = new kasio::tcphdr();

                    memcpy(&(*tcpdr), &(packet[ipRequireMinSize]), sizeof(kasio::tcphdr));

                    auto tcpTransportIndex = ipRequireMinSize + sizeof(kasio::tcphdr);

                    TransportPacket = std::move(std::vector<char>(
                        packet.begin() + tcpTransportIndex,
                        packet.end()));
                    }
                    break;
                case IP_TYPE::UDP:
                   {
                    udpdr = new kasio::udphdr();

                    memcpy(&(*udpdr), &(packet[ipRequireMinSize]), sizeof(kasio::udphdr));

                    auto udpTransportIndex = ipRequireMinSize + sizeof(kasio::udphdr);

                    TransportPacket = std::move(std::vector<char>(
                        packet.begin() + udpTransportIndex,
                        packet.end()));
                   }   
                    break;
                default:
                    break;
                }

            }

        }
        Packet(const Packet& packet) {
            iptype = packet.iptype;
            iphdr = nullptr;
            tcpdr = nullptr;
            udpdr = nullptr;
            if (packet.ethhder != nullptr) {
                ethhder = new kasio::Ethhdr();
                memcpy(ethhder, packet.ethhder, sizeof(kasio::Ethhdr));
            }
            if (packet.iphdr != nullptr) {
                iphdr = new kasio::Iphdr();
                memcpy(iphdr, packet.iphdr, sizeof(kasio::Iphdr));
            }
            if (packet.udpdr != nullptr) {
                udpdr = new kasio::udphdr();
                memcpy(udpdr, packet.udpdr, sizeof(kasio::udphdr));
            }
            if (packet.tcpdr != nullptr) {
                tcpdr = new kasio::tcphdr();
                memcpy(tcpdr, packet.tcpdr, sizeof(kasio::tcphdr));
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
            if (udpdr != nullptr)
                delete udpdr;
            if (tcpdr != nullptr)
                delete tcpdr;

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
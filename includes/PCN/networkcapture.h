#ifndef PCM_NETWORK_CAPTURE
#define PCM_NETWORK_CAPTURE

#include <unistd.h>
#include <kasio/kasio.h>
#include <string>
#include <future>
#include <memory>
#include <fmt/core.h>
#include <thread>
#include <PCN/type.h>

class PacketCapture;



class Component {
public:
    Component(PacketCapture* other) : m_packetCapture(other){
    }

    PacketCapture * m_packetCapture;
    virtual void recv(PCN::Packet&data) = 0;
};

class PacketStopComponent : public Component {
public:
    PacketStopComponent(PacketCapture* other);
    virtual void recv(PCN::Packet& data) override {
    }
};

class PacketEthhdrComponent : public Component {
public:
    PacketEthhdrComponent(PacketCapture* other) : Component(other) {

    }
public:
    virtual void recv(PCN::Packet& data) override;

};

class PacketIPComponent : public PacketEthhdrComponent {
public:
    PacketIPComponent(PacketCapture* other) : PacketEthhdrComponent(other) {

    }
public:
    virtual void recv(PCN::Packet& data) override {

        kasio::Iphdr * ip = data.iphdr;
        if (ip == nullptr) {
            return;
        }
        fmt::print("Version : {}\n", (unsigned int)ip->version);
        fmt::print("\tType Of Service : {}\n", (unsigned int)ip->tos);
        fmt::print("\tTotal Length : {}\n", (unsigned int)ip->tot_len);
        fmt::print("\tTime To Live: {}\n", (unsigned int)ip->ttl);
        fmt::print("\tProtocol : {}\n", (unsigned int)ip->protocol);
        fmt::print("\tHeader Checksum: {}\n", (unsigned int)ip->check);
        fmt::print("\tSource IP: {}.{}.{}.{}\n", ip->saddr[0], ip->saddr[1], ip->saddr[2], ip->saddr[3]);
        fmt::print("\tDestination IP: {}.{}.{}.{}\n", ip->daddr[0], ip->daddr[1], ip->daddr[2], ip->daddr[3]);

    }

};
class PacketIcmPComponent : public PacketIPComponent {
public:
    PacketIcmPComponent(PacketCapture* other) : PacketIPComponent(other) {

    }
    virtual void recv(PCN::Packet& data) override {

        if (data.GetIpProtocalType() != PCN::IP_TYPE::ICMP) {
            return;
        }

        kasio::Icmphdr icmphdr;
        memcpy(&icmphdr, &(data.GetTransportPacket()), sizeof(kasio::Icmphdr));

        fmt::print("\ttype : {}\n", (unsigned int)icmphdr.type);
        fmt::print("\tCode: {}\n", (unsigned int)icmphdr.code);
        fmt::print("\tCheck Sum: {}\n", (unsigned int)icmphdr.checksum);

    }
};
class PacketTcpComponent : public PacketIPComponent {
public:
    PacketTcpComponent(PacketCapture* other) : PacketIPComponent(other) {

    }
    virtual void recv(PCN::Packet& data) override {
        
        if (data.iptype==PCN::IP_TYPE::TCP) {
            for (char &data : data.TransportPacket) {

                fmt::print("{}", data);
            }
            fmt::print("\n");
        }
    }
};

class PacketHttpComponent : public PacketTcpComponent {
public:
    PacketHttpComponent(PacketCapture* other) : PacketTcpComponent(other) {

    }
    virtual void recv(PCN::Packet& data) override {

        if (data.iptype == PCN::IP_TYPE::TCP && 
            (ntohs(data.tcpdr->source) == 80 || ntohs(data.tcpdr->dest) == 80)) {


            for (char& data : data.TransportPacket) {

                fmt::print("{}", data);
            }
            fmt::print("\n");

        }
    }
};


class PacketUdpComponent : public PacketIPComponent {
public:
    PacketUdpComponent(PacketCapture* other) : PacketIPComponent(other) {

    }
    virtual void recv(PCN::Packet& data) override {
       
        if (data.iptype == PCN::IP_TYPE::UDP) {

            for (char& data : data.TransportPacket) {
                fmt::print("{}", data);
            }
        }
    }
};


class PacketAllComponent : public Component {
public:
    PacketAllComponent(PacketCapture* other) : Component(other) {

    }
    virtual void recv(PCN::Packet& data) override {


    }
};


class PacketCapture {
public:
    PacketCapture() : m_runing(false) {
        m_packetStrategy.reset(new PacketStopComponent(this));
    }
    enum CODE {
        EXIT, ERROR
    };
    std::future<CODE> run() {
        auto i = std::async(std::launch::async, [&]() {return impleRun(); });
        return i;
    }
    CODE impleRun() {
        if (m_socket.open()==false) {
            throw std::runtime_error("Socket Error");
        }
        m_runing = true;

        while (isRunning()) {
            PCN::Packet data = m_socket.recv();
            m_packetStrategy->recv(data);
            Packet.push_back(data);
        }

        return CODE::EXIT;
    }

    void exit() {
        m_runing = false;
    }

    void http() {
        m_packetStrategy.reset(new PacketHttpComponent(this));
    }
    void stop() {
        m_packetStrategy.reset(new PacketStopComponent(this));
    }
    void ethhdr() {
        m_packetStrategy.reset(new PacketEthhdrComponent(this));
    }
    void tcp() {
        m_packetStrategy.reset(new PacketTcpComponent(this));
    }
    void ip() {
        m_packetStrategy.reset(new PacketIPComponent(this));
    }
    void icmp() {
        m_packetStrategy.reset(new PacketIcmPComponent(this));
    }
    void udp() {
        m_packetStrategy.reset(new PacketUdpComponent(this));
    }
    void clear() {
        Packet.clear();
    }
    bool isRunning() {
        return m_runing;
    }
private:
    std::shared_ptr<Component> m_packetStrategy;
    std::vector<PCN::Packet> Packet;
    bool m_runing;
    kasio::basic_socket<kasio::ip::raw> m_socket;
    
};

#endif
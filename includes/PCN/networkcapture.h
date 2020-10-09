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
        fmt::print("\tSource IP: {}\n", (unsigned int)ip->saddr);
        fmt::print("\tDestination IP: {}\n", (unsigned int)ip->daddr);

    }

};
class PacketTcpComponent : public PacketIPComponent {
public:
    PacketTcpComponent(PacketCapture* other) : PacketIPComponent(other) {

    }
    virtual void recv(PCN::Packet& data) override {
        sleep(1);
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
        }
        return CODE::EXIT;
    }

    void exit() {
        m_runing = false;
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

    bool isRunning() {
        return m_runing;
    }
private:
    std::shared_ptr<Component> m_packetStrategy;
    std::vector<PCN::Packet> httpPackets;
    bool m_runing;
    kasio::basic_socket<kasio::ip::raw> m_socket;
    
};

#endif
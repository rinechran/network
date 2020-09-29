#ifndef PCM_NETWORK_CAPTURE
#define PCM_NETWORK_CAPTURE

#include <unistd.h>
#include <kasio/kasio.h>
#include <string>
#include <future>
#include <memory>
#include <thread>
#include <fmt/core.h>
class PacketCapture;


class PacketStrategy {
public:
    PacketStrategy(PacketCapture* other) : m_packetCapture(other){
    }

    PacketCapture * m_packetCapture;
    virtual void recv(std::vector<char> &data) = 0;
};

class PacketAllStrategy : public PacketStrategy {
public:
    PacketAllStrategy(PacketCapture* other) : PacketStrategy(other) {

    }
    virtual void recv(std::vector<char>& data) override {

        kasio::Ethhdr * eth = (kasio::Ethhdr*)(&(data[0]));
        fmt::print("Ethernet Header\n");
        fmt::print("\tSource Address {:x}:{:x}:{:x}:{:x}:{:x}:{:x}\n"
            , eth->h_source[0], eth->h_source[1], eth->h_source[2]
            , eth->h_source[3], eth->h_source[4], eth->h_source[5]);
        fmt::print("\tDestination Address {:x}:{:x}:{:x}:{:x}:{:x}:{:x}\n"
            , eth->h_dest[0], eth->h_dest[1], eth->h_dest[2]
            , eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
        fmt::print("\tprotocal {}\n"
            , (int16_t)eth->type);
    }

};

class PacketTCPStrategy : public PacketStrategy {
public:
    PacketTCPStrategy(PacketCapture* other) : PacketStrategy(other) {

    }
    virtual void recv(std::vector<char>& data) override {
        sleep(1);
    }

};

class PacketCapture {
public:
    PacketCapture() : m_runing(false) {
        m_packetStrategy.reset(new PacketAllStrategy(this));
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
            auto data = m_socket.recv();
            m_packetStrategy->recv(data);
        }
        return CODE::EXIT;
    }

    void exit() {
        m_runing = false;
    }
    void begin() {
    }
    void stop() {

    }
    void tcp() {
        m_packetStrategy.reset(new PacketTCPStrategy(this));
    }
    void changeStrategy() {

    }
    bool isRunning() {
        return m_runing;
    }
    std::shared_ptr<PacketStrategy> m_packetStrategy;
    bool m_runing;
    kasio::basic_socket<kasio::ip::raw> m_socket;
    
};

#endif
#ifndef PCM_NETWORK_CAPTURE
#define PCM_NETWORK_CAPTURE

#include <unistd.h>
#include <kasio/kasio.h>
#include <string>
#include <future>
#include <thread>
class PacketCapture;
class PacketStrategy {
public:
    PacketStrategy(PacketCapture* other) : m_packetCapture(other){
    }

    PacketCapture * m_packetCapture;
    virtual std::string recv() = 0;
};

class PacketAllStrategy : public PacketStrategy {
public:
    PacketAllStrategy(PacketCapture* other) : PacketStrategy(other) {

    }
    virtual std::string recv() override {
        sleep(1);
        return "w";
    }

};

class PacketTCPStrategy : public PacketStrategy {
public:
    PacketTCPStrategy(PacketCapture* other) : PacketStrategy(other) {

    }
    virtual std::string recv() override {
        sleep(1);
        return "tcp";
    }

};

class PacketCapture {
public:
    PacketCapture() : m_runing(false) {
        m_packetStrategy =  new PacketAllStrategy(this);
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
            auto i = m_socket.recv();
            std::string str(i.begin(), i.end());
            std::cout << str << std::endl;
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
        m_packetStrategy = new PacketTCPStrategy(this);
    }
    void changeStrategy() {

    }
    bool isRunning() {
        return m_runing;
    }
    PacketStrategy* m_packetStrategy;
    bool m_runing;
    kasio::basic_socket<kasio::ip::raw> m_socket;
    
};

#endif
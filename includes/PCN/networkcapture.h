#ifndef PCM_NETWORK_CAPTURE
#define PCM_NETWORK_CAPTURE

#include <unistd.h>
#include <kasio/kasio.h>
#include <string>
#include <future>
#include <memory>
#include <thread>
class PacketCapture;



class Component {
public:
    Component(PacketCapture* other) : m_packetCapture(other){
    }

    PacketCapture * m_packetCapture;
    virtual void recv(std::vector<char> &data) = 0;
};

class PacketStopComponent : public Component {
public:
    PacketStopComponent(PacketCapture* other);
    virtual void recv(std::vector<char>& data) override {
    }
};

class PacketEthhdrComponent : public Component {
public:
    PacketEthhdrComponent(PacketCapture* other) : Component(other) {

    }
public:
    virtual void recv(std::vector<char>& data) override;

};

class PacketIPComponent : public PacketEthhdrComponent {
public:
    PacketIPComponent(PacketCapture* other) : PacketEthhdrComponent(other) {

    }
public:
    virtual void recv(std::vector<char>& data) override {
        PacketEthhdrComponent::recv(data);

        fmt::print("");

    }

};
class PacketTcpComponent : public PacketIPComponent {
public:
    PacketTcpComponent(PacketCapture* other) : PacketIPComponent(other) {

    }
    virtual void recv(std::vector<char>& data) override {
        sleep(1);
    }

};
class PacketAllComponent : public Component {
public:
    PacketAllComponent(PacketCapture* other) : Component(other) {

    }
    virtual void recv(std::vector<char>& data) override {


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
            auto data = m_socket.recv();
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
    void changeStrategy() {

    }
    bool isRunning() {
        return m_runing;
    }
    std::shared_ptr<Component> m_packetStrategy;
    bool m_runing;
    kasio::basic_socket<kasio::ip::raw> m_socket;
    
};

#endif
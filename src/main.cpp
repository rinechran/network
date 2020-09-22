#include <iostream>
#include <exception>
#include <string>
#include <future>
#include <thread>
#include <kasio/kasio.h>


class FSM {

};
class PacketCapture {
public:
    enum CODE {
        EXIT,ERROR
    };
    std::future<CODE> run() {
        return std::async(std::launch::async, []() {return CODE::EXIT; });
    }
    CODE impleRun() {

        return CODE::EXIT;
    }

    void exit() {

    }

    void start() {

    }
    void stop() {

    }
    kasio::basic_socket<kasio::ip::raw> socket;

};
class Application {
public:
    Application() :input(' ') {

    }

    void run() {

        std::future<PacketCapture::CODE> packeteCatureEnable = packetcapture.run();

        while (true) {
            std::cin >> input;
            switch (input)
            {
            case 'q':
                packetcapture.exit();
                break;
            case 's':
                packetcapture.start();
                break;
            case 'b':
                packetcapture.stop();
                break;
            default:
                break;
            }
        }
        auto result = packeteCatureEnable.get();

    }
    char input;
    PacketCapture packetcapture;
};
int main() {
    

    Application application;
    application.run();



}
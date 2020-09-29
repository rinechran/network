#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <PCN/type.h>
#include <PCN/networkcapture.h>



class Application {
public:
    Application() {

    }

    void showMenu() {

    }
    void run() {

        std::future<PacketCapture::CODE> packeteCatureEnable = packetcapture.run();
        showMenu();

        while (true) {
            std::string input;

            std::cin >> input;

            switch (PCN::STATE_MENT[input])
            {
            case PCN::INPUT_TYPE::HTTPS:
                break;
            case PCN::INPUT_TYPE::HTTP:
                break;
            case PCN::INPUT_TYPE::TCP:
                packetcapture.tcp();
                break;
            case PCN::INPUT_TYPE::STOP:
                break;
            case PCN::INPUT_TYPE::EXIT:
                packetcapture.exit();
                goto EXIT;
                break;
            default:
                break;
            }
        }
        EXIT:
        auto result = packeteCatureEnable.get();

    }
    PacketCapture packetcapture;
};
int main() {
    

    Application application;
    application.run();



}
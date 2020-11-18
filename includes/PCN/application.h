#ifndef PCN_APPLICATION
#define PCN_APPLICATION

#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <PCN/networkcapture.h>
#include <PCN/constant.h>

class Application {
public:
    Application() = default;

    void showMenu() {

        fmt::print("TCP \n");
        fmt::print("UDP \n");
        fmt::print("HTTP \n");
        fmt::print("ICM \n");
        fmt::print("STOP \n");
        fmt::print("EXIT \n");

    }
    void run() {

        std::future<PacketCapture::CODE> packeteCatureEnable = packetcapture.run();
        showMenu();

        while (true) {
            std::string input;

            std::cin >> input;

            switch (PCN::STATE_MENT[input])
            {
            case PCN::INPUT_TYPE::ICMP:
                packetcapture.icmp();
                break;
            case PCN::INPUT_TYPE::ETHHDR:
                packetcapture.ethhdr();
                break;
            case PCN::INPUT_TYPE::HTTP:
                packetcapture.http();
                break;
            case PCN::INPUT_TYPE::TCP:
                packetcapture.tcp();
                break;
            case PCN::INPUT_TYPE::UDP:
                packetcapture.udp();
                break;
            case PCN::INPUT_TYPE::STOP:
                packetcapture.stop();
                break;
            case PCN::INPUT_TYPE::IP:
                packetcapture.ip();
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

#endif
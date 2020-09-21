#include <kasio/kasio.h>
#include <fmt/color.h>


class PacketCapture {
public:
    PacketCapture() : socket(ioService) {

    }

    void run() {


    }
    kasio::io_service ioService;
    kasio::basic_socket<kasio::ip::raw> socket;
};
int main() {
    

    PacketCapture packetCapture;
    packetCapture.run();



}
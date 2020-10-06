#include <PCN/networkCapture.h>
#include <fmt/core.h>


PacketStopComponent::PacketStopComponent(PacketCapture* other) : Component(other) {

}

void PacketEthhdrComponent::recv(std::vector<char>& data)  {
    kasio::Ethhdr* eth = (kasio::Ethhdr*)(&(data[0]));
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
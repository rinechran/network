#ifndef NETWORK_IP_SOCKET_CPP
#define NETWORK_IP_SOCKET_CPP
#include<vector>
#include<netinet/ip.h>
#include<stdio.h>
#include<sys/socket.h>
#include <string.h>
#include<arpa/inet.h>
#include<kasio/io/io_service.h>
#include<netinet/if_ether.h>  
namespace kasio {
	namespace ip {

		class raw {
		public:
			using Socket_t = int;

			Socket_t open() {
				m_socket =  socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
				if (m_socket < 0) {
					return false;
				}
				return true;
			}
			std::vector<char> recv() {
				std::vector<char> buffer(65555);
				int packet_size = recvfrom(m_socket, &(buffer[0]), buffer.size(), 0, NULL, NULL);
				buffer.resize(packet_size);
				return std::move(buffer);

			}
			Socket_t m_socket;

		};
	}
}
#endif
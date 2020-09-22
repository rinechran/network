#ifndef NETWORK_IP_SOCKET_CPP
#define NETWORK_IP_SOCKET_CPP

#include<netinet/ip.h>
#include<sys/socket.h>
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
			Socket_t m_socket;
		};
	}
}
#endif
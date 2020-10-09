#ifndef KASIO_BASIC_SOCKET
#define KASIO_BASIC_SOCKET


#include<netinet/ip.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<kasio/io/io_service.h>
#include<kasio/raw.h>
#include<kasio/generic/protocal_type.h>

namespace kasio {

	template<typename  T>
	class basic_socket {
	public:
		basic_socket() {
		}

		bool open() {
			 return m_Ip.open();
		}

		std::vector<char> recv() {
			return m_Ip.recv();
		}
		

		io_service m_io;
		
		T m_Ip;
		io_service m_io_serivce;
	};
}
#endif
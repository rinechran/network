#ifndef KASIO_PROTOCAL_TYPE_H
#define KASIO_PROTOCAL_TYPE_H


#define ETH_ALEN 6
#define ETH_TYPE 2

namespace kasio {

	struct Ethhdr
	{
		unsigned char	h_dest[ETH_ALEN];
		unsigned char	h_source[ETH_ALEN];
		std::int16_t	type;
	}  __attribute__((packed));

	struct Iphdr {
        unsigned char ihl : 4;
        unsigned char version : 4;

        unsigned char tos;
        unsigned int tot_len;
        unsigned int id;
        unsigned char ttl;
        unsigned char protocol;
        unsigned int check;

        __u32  saddr;
        __u32  daddr;

    } __attribute__((packed));


}

#endif
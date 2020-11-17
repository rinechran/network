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
        unsigned short tot_len;

        unsigned short id;
        unsigned char flags : 3;
        unsigned short fragmentOffset : 13;

        unsigned char ttl;
        unsigned char protocol;
        unsigned int check;
        unsigned int  saddr;
        unsigned int  daddr;

    } __attribute__((packed));

    struct tcphdr {
        __u16   source;
        __u16   dest;
        __u32   seq;
        __u32   ack_seq;

        __u16   res1 : 4,
            doff : 4,
            fin : 1,
            syn : 1,
            rst : 1,
            psh : 1,
            ack : 1,
            urg : 1,
            ece : 1,
            cwr : 1;

        __u16   window;
        __u16   check;
        __u16   urg_ptr;
    } __attribute__((packed));
    struct udphdr {
        u_short	uh_sport;		
        u_short	uh_dport;		
        short	uh_ulen;		
        u_short	uh_sum;			
    } __attribute__((packed)) ;

    struct Icmphdr
    {
        u_int8_t type;		
        u_int8_t code;		
        u_int16_t checksum;
        union
        {
            struct
            {
                u_int16_t	id;
                u_int16_t	sequence;
            } echo;			
            u_int32_t	gateway;	
            struct
            {
                u_int16_t	__unused;
                u_int16_t	mtu;
            } frag;			
        } un;
    }  __attribute__((packed)) ;






}

#endif
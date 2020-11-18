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
        unsigned char ihl : 4 , version: 4;

        unsigned char tos;

        unsigned short tot_len;
        unsigned short id;
        unsigned short flags;

        unsigned char ttl;
        unsigned char protocol;
        unsigned short check;

        unsigned char  saddr[4];
        unsigned char  daddr[4];

    } __attribute__((packed));

    struct tcphdr {
        __u16   source;
        __u16   dest;
        __u32   seq;
        __u32   ack_seq;

        
        unsigned char dataOffset :4 ,reserved :3 ,ns : 1;;

        unsigned char cwr : 1
            , ece : 1
            , urg : 1
            , ack : 1
            , psh : 1
            , rst : 1
            , syn : 1
            , fln : 1;

        __u16   window;
        __u16   check;
        __u16   urg_ptr;
    } __attribute__((packed));
    struct udphdr {
        u_short	uh_sport;		
        u_short	uh_dport;		
        u_short	uh_ulen;
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
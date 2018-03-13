#pragma once

#define	PROTONUM	3600

struct RawPacket {
	unsigned short protocol_number;
	unsigned short sequence_number;
	unsigned short bits;
	unsigned short int length;
};

class Packet {
public:
	static unsigned short GetType(unsigned short t);

	Packet(int length);
	~Packet();

	void SetType(unsigned int type);
	void SetLength(unsigned short length);
	void SetPayload(void * data, unsigned short length);
	void SetSequenceNumber(unsigned int s);
	RawPacket * RawPkt();
	static void HTON(RawPacket *);
	static void NTOH(RawPacket *);

	unsigned short Length();

private:
	RawPacket * packet_pointer;
	unsigned short payload_length;
	unsigned short total_length;
};

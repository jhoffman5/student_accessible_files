#pragma once

#define	PORT_NUMBER 9990

#define SOP_CODE_NOOP	0
#define SOP_CODE_GO		1
#define	SOP_CODE_ACK	2
#define	SOP_CODE_ERROR	3
#define SOP_CODE_BAD	4

#define	SOP_FLAG_DUP	0x0001

struct SPacket {
	unsigned short convo_id;
	unsigned short seq_num;
	unsigned short op_code;
	unsigned short flags;
};

#define CP_BUFFER_SIZE	122
#define CP_BUFFER_LIMIT	120
#define COP_CODE_NOOP	0
#define COP_CODE_START	1
#define COP_CODE_FINISH	2
#define COP_CODE_DATA	3
#define COP_CODE_BAD	4

#define COP_FLAG_RESEND	0x0001
#define DEF_WINDOW_SIZE	8
#define	TIMEOUT_SECONDS	1
#define MAX_RETRIES		4

struct CPacket {
	unsigned short convo_id;
	unsigned short seq_num;
	unsigned short op_code;
	unsigned short msg_len;
	unsigned short flags;
	unsigned short window_index;
	char msg[CP_BUFFER_SIZE];
};

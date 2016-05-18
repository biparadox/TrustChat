#ifndef SESSION_MSG_H
#define SESSION_MSG_H

enum chat_message_type
{
	MSG_GENERAL=0x01,
	MSG_PRIVATE=0x02,
	MSG_ANNOUNCED=0x04,
};

struct session_msg{
char uuid[DIGEST_SIZE*2];
char sender[DIGEST_SIZE];
char receiver[DIGEST_SIZE];
int  time;
int  length;
char * msg;
int  flag;
};

NAME2VALUE message_type_valuelist[] =
{
	{"GENERAL",MSG_GENERAL},
	{"PRIVATE",MSG_PRIVATE},
	{"ANNOUNCED",MSG_ANNOUNCED},
	
};

struct struct_elem_attr session_msg_desc[]=
{
        {"uuid",OS210_TYPE_STRING,DIGEST_SIZE*2,NULL},
        {"sender",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"receiver",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"time",OS210_TYPE_TIME,sizeof(int),NULL},
        {"length",OS210_TYPE_INT,sizeof(int),NULL},
        {"msg",OS210_TYPE_DEFSTR,0,"length"},
        {"flag",OS210_TYPE_FLAG,sizeof(int),&message_type_valuelist},
	{NULL,OS210_TYPE_ENDDATA,0,NULL}
};

// plugin's init func and kickstart func

#endif

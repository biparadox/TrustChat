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
char * msg;
int  flag;
};

static NAME2VALUE message_type_valuelist[] =
{
	{"GENERAL",MSG_GENERAL},
	{"PRIVATE",MSG_PRIVATE},
	{"ANNOUNCED",MSG_ANNOUNCED},
	{NULL,0}
	
};

static struct struct_elem_attr session_msg_desc[]=
{
        {"uuid",OS210_TYPE_STRING,DIGEST_SIZE*2,NULL},
        {"sender",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"receiver",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"time",OS210_TYPE_TIME,sizeof(int),NULL},
        {"msg",OS210_TYPE_ESTRING,512,NULL},
        {"flag",OS210_TYPE_FLAG,sizeof(int),&message_type_valuelist},
	{NULL,OS210_TYPE_ENDDATA,0,NULL}
};

enum  user_conn_state
{
	USER_CONN_CONNECTED=0x01,
	USER_CONN_SHUTDOWN=0x02,
	USER_CONN_ERROR=0xFF,

};

static NAME2VALUE user_conn_state_valuelist[] =
{
	{"CONNECTED",USER_CONN_CONNECTED},
	{"SHUTDOWN",USER_CONN_SHUTDOWN},
	{"ERROR",USER_CONN_ERROR},
	{NULL,0}
	
};


struct user_addr_list
{
	char user[DIGEST_SIZE];
	BYTE addr[DIGEST_SIZE*2];
	enum user_conn_state state;
	
};

static struct struct_elem_attr user_addr_list_desc[]=
{
        {"user",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"addr",OS210_TYPE_STRING,DIGEST_SIZE*2,NULL},
        {"state",OS210_TYPE_ENUM,sizeof(int),&message_type_valuelist},
	{NULL,OS210_TYPE_ENDDATA,0,NULL}
};


// plugin's init func and kickstart func

#endif

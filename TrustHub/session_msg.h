#ifndef SESSION_MSG_H
#define SESSION_MSG_H

struct session_msg{
char sender[DIGEST_SIZE];
char receiver[DIGEST_SIZE];
int  time;
int  length;
char * msg;
int  flag;
};

struct struct_elem_attr session_msg_desc[]=
{
        {"sender",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"receiver",OS210_TYPE_STRING,DIGEST_SIZE,NULL},
        {"time",OS210_TYPE_TIME,sizeof(int),NULL},
        {"length",OS210_TYPE_INT,sizeof(int),NULL},
        {"msg",OS210_TYPE_DEFSTR,0,"length"},
        {"flag",OS210_TYPE_INT,sizeof(int),NULL},
	{NULL,OS210_TYPE_ENDDATA,0,NULL}
};

// plugin's init func and kickstart func

#endif

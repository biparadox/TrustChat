#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "../include/data_type.h"
#include "../include/struct_deal.h"
#include "../include/crypto_func.h"
#include "../include/extern_struct.h"
#include "../include/extern_defno.h"
#include "../include/message_struct.h"
#include "../include/logic_baselib.h"
#include "../include/sec_entity.h"
#include "../include/main_proc_init.h"
#include "../include/valuename.h"
#include "../include/expand_define.h"

#include "../cloud_config.h"
#include "login_verify.h"
#include "user_info.h"
int login_verify_init(void * sub_proc,void * para)
{
	int ret;
	// add youself's plugin init func here
	return 0;
}

int login_verify_start(void * sub_proc,void * para)
{
	int ret;
	void * recv_msg;
	int i;
	const char * type;


	for(i=0;i<3000*1000;i++)
	{
		usleep(time_val.tv_usec);
		ret=sec_subject_recvmsg(sub_proc,&recv_msg);
		if(ret<0)
			continue;
		if(recv_msg==NULL)
			continue;
		type=message_get_recordtype(recv_msg);
		if(type==NULL)
		{
			printf("message format error!\n");
			continue;
		}
		if(!find_record_type(type))
		{
			printf("message format is not registered!\n");
			continue;
		}
		login_verify_message(sub_proc,recv_msg);
	}

	return 0;
};

int login_verify_message(void * sub_proc,void * message)
{
	const char * type;
	int i;
	int ret;
	printf("begin proc echo \n");
	struct message_box * msg_box=message;
	type=message_get_recordtype(message);

	struct message_box * new_msg;
        struct login_info *login_data;
        struct user_info_list *lib_data;
        struct connect_return *return_data; 
// 	void * record;
	new_msg=message_create("RETC",message);
	return_data=malloc(sizeof(struct connect_return));
	memset(return_data,0,sizeof(struct connect_return));
	i=0;

	ret=message_get_record(message,&login_data,i++);
        if(ret<0)
           return ret;
        ret=FindPolicy(login_data->user,"UL_I",&lib_data);
	if(ret<0)
	{
	 return_data->ret_data=dup_str("login verify system error!",0);
	}
        else if(lib_data==NULL){
         return_data->ret_data=dup_str("no such user!",0);
	}
        else if(strncmp(lib_data->passwd,login_data->passwd,DIGEST_SIZE*2))
        {
         return_data->ret_data=dup_str("error passwd!",0);
	}
	else
	{

          return_data->ret_data=dup_str("login succeed!",0);
          return_data->retval=1;
	}
/*	while(record!=NULL)
	{
		message_add_record(new_msg,record);
		ret=message_get_record(message,&record,i++);
		if(ret<0)
			return ret;
	}*/
        return_data->ret_data_size=strlen(return_data->ret_data);
        message_add_record(new_msg,return_data);
	sec_subject_sendmsg(sub_proc,new_msg);
	return ret;
}

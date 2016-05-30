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
#include <openssl/rsa.h>
#include <openssl/evp.h>

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
#include "session_msg.h"
#include "hub_message_expand.h"

int hub_message_expand_init(void * sub_proc,void * para)
{
	int ret;
	// add youself's plugin init func here
	return 0;
}

int hub_message_expand_start(void * sub_proc,void * para)
{
	int ret;
	void * recv_msg;
	int i;
	const char * type;

	usleep(500*1000);

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
		if(strncmp(type,"MSGD",4)==0)
			proc_echo_message(sub_proc,recv_msg);
	}

	return 0;
};

int proc_echo_message(void * sub_proc,void * message)
{
	const char * type;
	int i;
	int ret;
	
	//struct expand_time_stamp * time_stamp;
	//char * timestr;
	//time_stamp = malloc(sizeof(struct expand_time_stamp));
	printf("begin proc echo \n");
	struct message_box * msg_box=message;

	struct message_box * new_msg;
	struct session_msg * echo_msg;
	time_t tm;

	//if (time_stamp==NULL)
	//	return -ENOMEM;
	//memcpy(time_stamp->tag,"TIME",4);
	//time_stamp->data_size=sizeof(struct expand_time_stamp);


	ret=message_get_record(message,&echo_msg,0);
	if(echo_msg==NULL)
		return 0;

	time(&tm);
	echo_msg->time=tm;

	ret=entity_hash_uuid("MSGD",echo_msg);
	if(ret<0)
		return ret;
	
	new_msg=message_create("MSGD",message);
	
        if(echo_msg->flag==MSG_PRIVATE){
                struct expand_extra_info  *eei;
                eei =malloc(sizeof(struct expand_extra_info));
                if(eei==NULL)
                        return -ENOMEM;
                memset(eei->uuid,0,DIGEST_SIZE*2);
                memcpy(eei->uuid,echo_msg->receiver,DIGEST_SIZE);
                eei->data_size=sizeof(struct expand_extra_info );
                memcpy(eei->tag,"EEIE",4);
                message_add_expand(new_msg,eei);
        }
	else if(echo_msg->flag==MSG_GENERAL){
                struct expand_extra_info  *eei;
		void * search_from_db;
		struct user_addr_list * first_msg;
		ret=GetFirstPolicy(&first_msg,"U2AL");
	        if(ret<0)
        	        return -EINVAL;
       		 //search_from_db=message_create("U2AL",NULL);
       		// if(search_from_db==NULL)
                //	return -EINVAL;
       		 //message_add_record(send_msg,first_msg);
		if(first_msg==NULL)
		{
			printf("find addr failed!\n");
			return -EINVAL;
		}

                eei =malloc(sizeof(struct expand_extra_info));
                if(eei==NULL)
                        return -ENOMEM;
                memset(eei->uuid,0,DIGEST_SIZE*2);
                memcpy(eei->uuid,first_msg->addr,DIGEST_SIZE*2);
                eei->data_size=sizeof(struct expand_extra_info );
                memcpy(eei->tag,"EEIE",4);
                message_add_expand(new_msg,eei);
        }

	message_add_record(new_msg,echo_msg);
	//timestr=ctime_r(&tm,time_stamp->time);
	//if (timestr<=0)
	//	return -EINVAL;

	//message_add_expand(new_msg,time_stamp);
	sec_subject_sendmsg(sub_proc,new_msg);
	return ret;
}

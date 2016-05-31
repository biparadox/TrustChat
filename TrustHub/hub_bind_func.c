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
#include "../include/tesi.h"
#include "../include/tesi_key.h"


#include "../cloud_config.h"
#include "main_proc_func.h"
#include "session_msg.h"
#include "user_info.h"

struct bind_proc_pointer
{
	struct vTPM_wrappedkey * bind_key;
    	struct vTPM_publickey * bind_pubkey;
	TSS_HKEY hBindKey;
	TSS_HKEY hBindPubKey;
};

int bind_pubkey_memdb_init()
{
	int ret;
	char * bindpubkeyname="pubkey/bindpubkey";
	struct vTPM_publickey	*local_bindpubkey;

	local_bindpubkey=malloc(sizeof(struct vTPM_publickey));
	if(local_bindpubkey==NULL)
		return -ENOMEM;

	ret=create_pubkey_struct(local_bindpubkey,NULL,NULL,bindpubkeyname);	
	if(ret<0)
		return ret;

	AddPolicy(local_bindpubkey,"PUBK");
       	ExportPolicy("PUBK");
	return 0;
}

int bind_key_memdb_init()
{
	int ret;
	char * bindkeyname="privkey/bindkey";
	struct vTPM_wrappedkey	*local_bindkey;

	local_bindkey=malloc(sizeof(struct vTPM_wrappedkey));
	if(local_bindkey==NULL)
		return -ENOMEM;

	ret=create_blobkey_struct(local_bindkey,NULL,NULL,"kkk",bindkeyname);	
	if(ret<0)
		return ret;

	AddPolicy(local_bindkey,"BLBK");
       	ExportPolicy("BLBK");
	return 0;
}

int hub_bind_init(void * sub_proc,void * para)
{
	int ret;
	// add youself's plugin init func here
	return 0;
}

int hub_bind_start(void * sub_proc,void * para)
{
	int ret;
	void * recv_msg;
	int i;
	const char * type;
	TSS_RESULT result;



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
		if(strncmp(type,"MSGD",4)==0)
		{

			if(message_get_flag(recv_msg) & MSG_FLAG_CRYPT)
				proc_unbind_message(sub_proc,recv_msg);
			else
				proc_bind_message(sub_proc,recv_msg);
		}
	}
	return 0;
}

int proc_bind_message(void * sub_proc,void * message)
{
	TSS_RESULT result;
	struct bind_proc_pointer * bind_pointer;
	int i;
	int ret;
	void * context;

	struct node_key_list * pub_keylist;

		
	void * blob;
	int blob_size;

	void* bind_blob;
	int bind_blob_size;

	struct user_name_expand * user_info;
	char bindkey_file[DIGEST_SIZE*3];

	ret=message_get_define_expand(message,&user_info,"USNE");
	if(ret<0)
		return ret;
	if(user_info==NULL)
	{
		printf("message has no receiver's info!\n");
		return -EINVAL;
	}
	
	ret=GetFirstPolicy(&pub_keylist,"NKLD");

	if(ret<0)
		return ret;
	while(pub_keylist!=NULL)
	{
		if(strncmp(user_info->name,pub_keylist->username,DIGEST_SIZE)==0)
			break;
		ret=GetNextPolicy(&pub_keylist,"NKLD");
		if(ret<0)
			return ret;
	}

	if(pub_keylist==NULL)
	{
		printf("can't find user %s's public key struct!\n",user_info->name);
	}

	
	TSS_HKEY hBindPubKey;
	sprintf(bindkey_file,"pubkey/%.64s",pub_keylist->nodeBindKey);

	result=TESI_Local_ReadPubKey(&hBindPubKey,bindkey_file);
	if(result!=TSS_SUCCESS)
	{
		printf("load bindpubkey %s error %d!\n",bindkey_file,result);
		return -EINVAL;
	}
	

	blob_size=message_get_blob(message,&blob);
	if(blob_size<=0)
		return -EINVAL;
	result=TESI_Local_BindBuffer(blob,blob_size,hBindPubKey,&bind_blob,&bind_blob_size);
	if ( result != TSS_SUCCESS )
	{
		return -EINVAL;
	}
	

	message_set_blob(message,bind_blob,bind_blob_size);
	message_set_flag(message,MSG_FLAG_CRYPT);

	sec_subject_sendmsg(sub_proc,message);
	return ret;
}

int proc_unbind_message(void * sub_proc,void * message)
{
	TSS_RESULT result;

	int ret;
	struct node_key_list * local_keylist;
		
	void * blob;
	int blob_size;

	void* bind_blob;
	int bind_blob_size;

	struct user_name_expand * user_info;
	char bindkey_file[DIGEST_SIZE*3];

	ret=message_get_define_expand(message,&user_info,"USNE");
	if(ret<0)
		return ret;
	if(user_info==NULL)
	{
		printf("message has no receiver's info!\n");
		return -EINVAL;
	}
	
	ret=GetFirstPolicy(&local_keylist,"LKLD");

	if(ret<0)
		return ret;
	while(local_keylist!=NULL)
	{
		if(strncmp(user_info->name,local_keylist->username,DIGEST_SIZE)==0)
			break;
		ret=GetNextPolicy(&local_keylist,"LKLD");
		if(ret<0)
			return ret;
	}

	if(local_keylist==NULL)
	{
		printf("can't find user %s's private key struct!\n",user_info->name);
	}

	
	TSS_HKEY hBindKey;
	sprintf(bindkey_file,"privkey/%.64s",local_keylist->nodeBindKey);
	result=TESI_Local_ReadKeyBlob(&hBindKey,bindkey_file);
	if(result!=TSS_SUCCESS)
	{
		printf("load bindkey error %d!\n",result);
	}
	result=TESI_Local_LoadKey(hBindKey,NULL,"kkk");
	if(result!=TSS_SUCCESS)
	{
		printf("load bindkey error %d!\n",result);
		return -ENFILE;
	}
	blob_size=message_get_blob(message,&blob);
	if(blob_size<=0)
		return -EINVAL;

	result=TESI_Local_UnBindBuffer(blob,blob_size,hBindKey,&bind_blob,&bind_blob_size);
	if ( result != TSS_SUCCESS )
	{
		return -EINVAL;
	}
	
	message_set_blob(message,bind_blob,bind_blob_size);
	int flag=message_get_flag(message);
	message_set_flag(message,flag&(~MSG_FLAG_CRYPT));

	sec_subject_sendmsg(sub_proc,message);
	return ret;
}

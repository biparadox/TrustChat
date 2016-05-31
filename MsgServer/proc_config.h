#ifndef PROC_CONFIG_H
#define PROC_CONFIG_H


static char * main_proc_name="MsgServer";
static int  (*main_proc_initfunc)()=&MsgServer_init;

static PROCDB_INIT procdb_init_list[]=
{
	{"EEIE",NULL,&expand_extra_info_desc,NULL},
	{"USNE",NULL,&user_name_expand_desc,NULL},
	{"U2AL",&null_init_func,&user_addr_list_desc,&general_lib_ops},
	{"MSGD",&null_init_func,&session_msg_desc,&general_lib_ops},
	{"UL_I",&general_lib_init,&user_info_list_desc,&general_lib_ops},
	{"LOGI",NULL,&login_info_desc,NULL},			
	{"RETC",NULL,&connect_return_desc,NULL},			
	{"NKLD",&null_init_func,&node_key_list_desc,&general_lib_ops},
	{NULL,NULL,NULL,NULL}
};

static PROC_INIT proc_init_list[]=
{
	{"hub_message_expand",PROC_TYPE_MONITOR,&hub_message_expand_init,&hub_message_expand_start},
	{"ms_ser_db",PROC_TYPE_MONITOR,&ms_ser_db_init,&ms_ser_db_start},
	{"key_storage",PROC_TYPE_MONITOR,&key_storage_init,&key_storage_start},
	{NULL,0,NULL,NULL}
};

#endif // PROC_CONFIG_H

#ifndef PROC_CONFIG_H
#define PROC_CONFIG_H


static char * main_proc_name="MsgHub";
static int  (*main_proc_initfunc)()=&MsgHub_init;

static PROCDB_INIT procdb_init_list[]=
{
	{"EEIE",NULL,&expand_extra_info_desc,NULL},
	{"USNE",NULL,&user_name_expand_desc,NULL},
	{"U2AL",&null_init_func,&user_addr_list_desc,&general_lib_ops},
	{"MSGD",&general_uuid_lib_init,&session_msg_desc,&general_lib_ops},
	{"UL_I",&general_lib_init,&user_info_list_desc,&general_lib_ops},
	{"LOGI",NULL,&login_info_desc,NULL},
	{"RETC",NULL,&connect_return_desc,NULL},
//	{"NKLD",&null_init_func,&node_key_list_desc,&general_lib_ops},
	{NULL,NULL,NULL,NULL}
};

static PROC_INIT proc_init_list[]=
{
	{"hub_message_expand",PROC_TYPE_MONITOR,&hub_message_expand_init,&hub_message_expand_start},
	{"friend_list",PROC_TYPE_MONITOR,&friend_list_init,&friend_list_start},
	{"json_port",PROC_TYPE_MONITOR,&json_port_init,&json_port_start},
        {"echo_plugin",PROC_TYPE_MONITOR,&echo_plugin_init,&echo_plugin_start},
	{"ws_port",PROC_TYPE_MONITOR,&websocket_port_init,&websocket_port_start},
	{NULL,0,NULL,NULL}
};

#endif // PROC_CONFIG_H

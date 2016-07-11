#ifndef PROC_CONFIG_H
#define PROC_CONFIG_H


static char * main_proc_name="Monitor";
static int  (*main_proc_initfunc)()=&Monitor_init;

static PROCDB_INIT procdb_init_list[]=
{
	{"EEIE",NULL,&expand_extra_info_desc,NULL},
	{"USNE",NULL,&user_name_expand_desc,NULL},
	{"U2AL",&null_init_func,&user_addr_list_desc,&general_lib_ops},
	{"MSGD",&null_init_func,&session_msg_desc,&general_lib_ops},
	{"UL_I",&null_init_func,&user_info_list_desc,&general_lib_ops},
	{"LOGI",NULL,&login_info_desc,NULL},
	{"RETC",NULL,&connect_return_desc,NULL},
	{NULL,NULL,NULL,NULL}
};

static PROC_INIT proc_init_list[]=
{
	{"ws_port",PROC_TYPE_MONITOR,&websocket_port_init,&websocket_port_start},
	{NULL,0,NULL,NULL}
};

#endif // PROC_CONFIG_H

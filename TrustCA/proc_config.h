#ifndef PROC_CONFIG_H
#define PROC_CONFIG_H


static char * main_proc_name="TrustCA";
static int  (*main_proc_initfunc)()=&TrustCA_init;

static PROCDB_INIT procdb_init_list[]=
{
	{"VM_T",&vtpm_memdb_init,&vtpm_info_desc,&general_lib_ops},
	{"PUBK",&public_key_memdb_init,&publickey_desc,&general_lib_ops},
	{"BLBK",&null_init_func,&wrappedkey_desc,&general_lib_ops},
	{"USRI",&null_init_func,&aik_user_info_desc,&general_lib_ops},
	{"CERI",&null_init_func,&aik_cert_info_desc,&general_lib_ops},
	{"NKLD",&null_init_func,&node_key_list_desc,&general_lib_ops},
	{"KREC",&null_init_func,&key_request_cmd_desc,&general_lib_ops},
	{NULL,NULL,NULL,NULL}
};

static PROC_INIT proc_init_list[]=
{
	{"aik_casign",PROC_TYPE_MONITOR,&aik_casign_init,&aik_casign_start},
	{"key_storage",PROC_TYPE_MONITOR,&key_storage_init,&key_storage_start},
	{"file_receiver",PROC_TYPE_MONITOR,&file_receiver_init,&file_receiver_start},
	{NULL,0,NULL,NULL}
};

#endif // PROC_CONFIG_H

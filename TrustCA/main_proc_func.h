#ifndef MAIN_PROC_FUNC_H
#define MAIN_PROC_FUNC_H
#include "../include/vtpm_struct.h"
#include "../include/vtpm_desc.h"
#include "../include/tesi_key.h"
#include "../include/tesi_key_desc.h"
#include "../include/tesi_aik_struct.h"
#include "aik_casign_func.h"
#include "session_msg.h"
#include "key_storage_func.h"
#include "file_receiver_func.h"

int TrustCA_init();

int public_key_memdb_init();
int vtpm_memdb_init();
int login_name_memdb_init();


#endif

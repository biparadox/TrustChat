FLAGS= -g -o 
CFLAGS= -g -c -DUSER_MODE 
CC=gcc
CCP=g++
MAIN_PROC=MsgServer
PLUGIN_PROC_OBJ= hub_message_expand.o ms_ser_db.o key_storage_func.o file_receiver_func.o
INIT_DB_OBJ= general_lib_init.o

main: $(MAIN_PROC)
$(MAIN_PROC):  main_proc.c $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)
	$(CC) $(FLAGS) $(MAIN_PROC) main_proc.c connector_process_func.o router_process_func.o $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)  -L../lib -lopenstacktrust -lentity -lrouter -lpolicy_ui -lmemdb -lconnector -lmessage -llogicdb -lstruct -lsysfunc -lcrypto_func -lpthread
$(MAIN_PROC)_func.o: $(MAIN_PROC)_func.c main_proc_func.h
	$(CC) $(CFLAGS) $(MAIN_PROC)_func.c
general_lib_init.o:  general_lib_init.c main_proc_func.h
	$(CC)  $(CFLAGS) general_lib_init.c 
hub_message_expand.o:  hub_message_expand.c main_proc_func.h
	$(CC)  $(CFLAGS) hub_message_expand.c 
ms_ser_db.o:  ms_ser_db.c main_proc_func.h
	$(CC)  $(CFLAGS) ms_ser_db.c 
key_storage_func.o:  key_storage_func.c main_proc_func.h
	$(CC)  $(CFLAGS) key_storage_func.c 
file_receiver_func.o: file_receiver_func.c file_receiver_func.h
	$(CC)  $(CFLAGS) file_receiver_func.c 
	
clean:
	rm -f $(MAIN_PROC) *~ *.o *.a
	ln -s ../../general/connector_process_func.o .
	ln -s ../../general/router_process_func.o .
	ln -s ../../general/main_proc.c .

FLAGS= -g -o 
CFLAGS= -g -c -DUSER_MODE 
CC=gcc
CCP=g++
MAIN_PROC=TrustHub
PLUGIN_PROC_OBJ=aik_process_func.o  file_receiver_func.o key_manage_func.o hub_bind_func.o
INIT_DB_OBJ= general_lib_init.o

main: $(MAIN_PROC)
$(MAIN_PROC):  main_proc.c $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)
	$(CC) $(FLAGS) $(MAIN_PROC) main_proc.c connector_process_func.o router_process_func.o $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)  -L../lib -lopenstacktrust -ltesi -ltspi -lcrypto -lentity -lrouter -lpolicy_ui -lmemdb -lconnector -lmessage -llogicdb -lstruct -lsysfunc -lcrypto_func -lpthread
$(MAIN_PROC)_func.o: $(MAIN_PROC)_func.c main_proc_func.h
	$(CC) $(CFLAGS) $(MAIN_PROC)_func.c
aik_process_func.o:  aik_process_func.c main_proc_func.h
	$(CC)  $(CFLAGS) aik_process_func.c 
file_receiver_func.o:  file_receiver_func.c main_proc_func.h
	$(CC)  $(CFLAGS) file_receiver_func.c 
general_lib_init.o:  general_lib_init.c main_proc_func.h
	$(CC)  $(CFLAGS) general_lib_init.c 
key_manage_func.o:  key_manage_func.c main_proc_func.h
	$(CC)  $(CFLAGS) key_manage_func.c 
hub_bind_func.o:  hub_bind_func.c main_proc_func.h
	$(CC)  $(CFLAGS) hub_bind_func.c 
cleankey:
	rm lib/* cert/*.req cert/*.val cert/*.sda privkey/* pubkey/*
clean:
	rm -f $(MAIN_PROC) *~ *.o *.a
	ln -s ../../general/connector_process_func.o .
	ln -s ../../general/router_process_func.o .
	ln -s ../../general/main_proc.c .

FLAGS= -g -o 
CFLAGS= -g -c -DUSER_MODE 
CC=gcc
CCP=g++
MAIN_PROC=TrustCA
PLUGIN_PROC_OBJ=aik_casign_func.o key_storage_func.o file_receiver_func.o

main: $(MAIN_PROC)
$(MAIN_PROC):  main_proc.c $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ)
	$(CC) $(FLAGS) $(MAIN_PROC) main_proc.c connector_process_func.o router_process_func.o $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) -L../lib -lopenstacktrust -lentity -lrouter -lpolicy_ui -lmemdb -lconnector -lmessage -llogicdb -lstruct -lsysfunc -lcrypto_func -ltesi -ltspi -lcrypto -lpthread
$(MAIN_PROC)_func.o: $(MAIN_PROC)_func.c main_proc_func.h
	$(CC) $(CFLAGS) $(MAIN_PROC)_func.c
aik_casign_func.o:  aik_casign_func.c main_proc_func.h
	$(CC)  $(CFLAGS) aik_casign_func.c 
key_storage_func.o:  key_storage_func.c main_proc_func.h
	$(CC)  $(CFLAGS) key_storage_func.c 
file_receiver_func.o: file_receiver_func.c file_receiver_func.h
	$(CC)  $(CFLAGS) file_receiver_func.c 
cleankey: 
	rm lib/* pubkey/* cert/*.sda cert/*.val
clean:
	rm -f $(MAIN_PROC) *~ *.o *.a
	ln -s ../../general/connector_process_func.o .
	ln -s ../../general/router_process_func.o .
	ln -s ../../general/main_proc.c .

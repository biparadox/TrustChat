FLAGS= -g -o 
CFLAGS= -g -c -DUSER_MODE 
CC=gcc
CCP=g++
MAIN_PROC=MsgHub
PLUGIN_PROC_OBJ= hub_message_expand.o json_port_func.o login_verify.o friend_list.o echo_plugin_func.o websocket_func.o
INIT_DB_OBJ= general_lib_init.o

main: $(MAIN_PROC)
$(MAIN_PROC):  main_proc.c $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)
	$(CC) $(FLAGS) $(MAIN_PROC) main_proc.c connector_process_func.o router_process_func.o $(MAIN_PROC)_func.o $(PLUGIN_PROC_OBJ) $(INIT_DB_OBJ)  -L../lib -lopenstacktrust -lentity -lrouter -lpolicy_ui -lmemdb -lconnector -lmessage -llogicdb -lstruct -lsysfunc -lcrypto_func -lpthread -lwebsockets
$(MAIN_PROC)_func.o: $(MAIN_PROC)_func.c main_proc_func.h
	$(CC) $(CFLAGS) $(MAIN_PROC)_func.c
#echo_plugin_func.o:  echo_plugin_func.c main_proc_func.h
#	$(CC)  $(CFLAGS) echo_plugin_func.c 
general_lib_init.o:  general_lib_init.c main_proc_func.h
	$(CC)  $(CFLAGS) general_lib_init.c 
hub_message_expand.o:  hub_message_expand.c main_proc_func.h
	$(CC)  $(CFLAGS) hub_message_expand.c 
json_port_func.o:  json_port_func.c main_proc_func.h
	$(CC)  $(CFLAGS) json_port_func.c 
login_verify.o:  login_verify.c main_proc_func.h
	$(CC)  $(CFLAGS) login_verify.c 
friend_list.o:  friend_list.c main_proc_func.h
	$(CC)  $(CFLAGS) friend_list.c 
echo_plugin_func.o:  echo_plugin_func.c main_proc_func.h
	$(CC)  $(CFLAGS) echo_plugin_func.c 
websocket_func.o: websocket_func.c websocket_func.h
	$(CC)  $(CFLAGS) websocket_func.c 
clean:
	rm -f $(MAIN_PROC) *~ *.o *.a
	ln -s ../../general/connector_process_func.o .
	ln -s ../../general/router_process_func.o .
	ln -s ../../general/main_proc.c .

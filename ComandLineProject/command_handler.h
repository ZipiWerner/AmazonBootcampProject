#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "gas_cam.h"
#include "hashtable.h"
#include "comanddetails.h"
#define START_RECORD "strrcd"
#define STOP_RECORD "stprcd"
#define DO_SNAPSHOT "dosnp"
extern gazapi_t *p_gaz;
extern handler* my_handler;
char ** splitCmd(char * commandStr,int *len);
void insertCmdDetToHash(HashTable* ht ,cmdFunc cf,helpFunc hf ,char* name);
void start_command_line(HashTable * ht);
gazapi_t* load_libary();
#endif // COMMAND_HANDLER_H

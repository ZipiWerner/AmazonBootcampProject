#ifndef COMANDLINEFUNC_H
#define COMANDLINEFUNC_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "comandfunc.h"





int start_record_cli(handler *,char **cmdArr,int size);

int stop_record_cli(handler *,char **cmdArr,int size);

int do_snapshot_cli(handler *,char ** cmdArr,int size);
#endif // COMANDLINEFUNC_H

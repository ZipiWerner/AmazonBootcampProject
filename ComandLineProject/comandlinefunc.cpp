#include "comandlinefunc.h"
int start_record_cli(handler * handle,char **cmdArr,int size)
{
    record_t * record=(record_t *)malloc(sizeof(record_t));
    //get the information from the json
    record->height=SNAPSHOT_HEIGHT;
    record->width=SNAPSHOT_WIDTH;
    //the parameter that i dont get we need to take out from the json
   start_record(handle,record);
   return 1;

}
int stop_record_cli(handler * handle,char **cmdArr,int size)
{
    stop_record(handle,NULL);
    return 1;
}
int do_snapshot_cli(handler * handle,char ** cmdArr,int size){
    //get snapshot from the json
    do_snapshot(handle,NULL);
    return 1;
}

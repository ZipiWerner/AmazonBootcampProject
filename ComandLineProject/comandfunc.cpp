#include "comandfunc.h"

void start_record(handler * handle ,record_t *record){
  p_gaz->start_record(handle,record);
}
void stop_record(handler * handle,record_t *record){
    p_gaz->stop_record(handle);
}
void do_snapshot(handler * handle,ppm_image * p)
{
    p_gaz->do_snapshot(handle);
}


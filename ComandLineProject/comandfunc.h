#ifndef COMANDFUNC_H
#define COMANDFUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gas_cam.h>



extern gazapi_t *p_gaz;
void start_record(handler * handle ,record_t *);
void stop_record(handler * handle,record_t *);
void do_snapshot(handler * handle,ppm_image*);




#endif // COMANDFUNC_H

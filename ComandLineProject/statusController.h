#ifndef STATUSCONTROLLER_H
#define STATUSCONTROLLER_H

#include <stdio.h>
#include <dlfcn.h>
#include <assert.h>
#include "gas_cam.h"
#include <unistd.h>
#include<signal.h>
#include <time.h>
#include <errno.h>
#include<pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
extern gazapi_t *p_gaz;
//extern handler* my_handler;
typedef struct flash_t{
    int rate;
    int is_active;
    int gpio;
}flash_t;
enum STATUS_MACHINE{
    BLINK_ON=1,
    BLINK_OFF=2,
    FLASH_ON=3,
    FLASH_OFF=4
};
enum TIME_LONG{
    RECORD_RATE=500,
    SNAPSHOT_RATE=300
};

void sig_handler(int signo);
int msleep(long msec);
void led_on();
void led_off();
void * led_thread(void * arg);
void *status_thread(void * arg);
void status_app(handler * my_handler);
#endif // STATUSCONTROLLER_H

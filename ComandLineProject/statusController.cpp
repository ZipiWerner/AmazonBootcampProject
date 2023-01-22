#include "statusController.h"


int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {

        errno = EINVAL;
        return -1;
    }
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int export_gpio(){
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/export");
        exit(1);
    }

    if (write(fd, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(1);
    }

    close(fd);

    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction

    fd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio24/direction");
        exit(1);
    }

    close(fd);
    fd = open("/sys/class/gpio/gpio24/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio24/value");
        exit(1);
    }
    return fd;
}
int unexport_gpio(){
    int fd;
    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/unexport");
        exit(1);
    }
    if (write(fd, "24", 2) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(1);
    }
    close(fd);
    return 1;
}
void led_on(int * rate,int fd)
{

    //I dont use the gpio yet...
    printf("the led is onnnnnnnnnn\n");
    //    if (write(fd, "1", 1) != 1) {
    //        perror("Error writing to /sys/class/gpio/gpio24/value");
    //        exit(1);
    //    }

}
void led_off(int fd){
    printf("\nthe led is offffffffff\n");
    //I dont use the gpio yet...
    printf("\n\n");
    //    if (write(fd, "0", 1) != 1) {
    //        perror("Error writing to /sys/class/gpio/gpio24/value");
    //        exit(1);
    //    }
}
void * led_thread(void * arg)
{

    flash_t * my_flash =((flash_t *)(arg));
    printf("flash rate %d",my_flash->rate);
    enum STATUS_MACHINE cur_state;
    switch (my_flash->rate) {
    case SNAPSHOT_RATE:
        cur_state=FLASH_ON;
        break;
    case RECORD_RATE:
        cur_state=BLINK_ON;
        break;
    }
    int fd;
    // fd= export_gpio();
    while(my_flash->is_active)
    {
        switch(cur_state)
        {
        case FLASH_ON:
            cur_state=FLASH_OFF;
            led_on(&(my_flash->rate),fd);
            break;
        case FLASH_OFF:
            printf("finish flash\n");
            my_flash->is_active=0;
            led_off(fd);
            break;
        case BLINK_ON:
            cur_state=BLINK_OFF;
            led_on(&(my_flash->rate),fd);
            break;
        case BLINK_OFF:
            cur_state=BLINK_ON;
            led_off(fd);
            break;
        }
        msleep(my_flash->rate);

    }
    //if the flash not need to br active now but need to off rhe flash
    if(cur_state==BLINK_OFF)
        led_off(fd);
    // unexport_gpio();
}
void *status_thread(void * arg){

    handler *my_handler=(handler*)arg;
    status my_status=my_handler->status;
    status old_status=INIT;
    pthread_t blink,flash;
    flash_t *record_struct=(flash_t *)malloc(sizeof(flash_t)),*snapshot_struct=(flash_t *)malloc(sizeof(flash_t));
    //when we finish the program the status wold be 0
    while(my_status)
    {
        if(my_status != old_status)
        {
            if((my_status&RECORD_ACTIVE))
            {
                record_struct->is_active=1;
                record_struct->rate=RECORD_RATE;
                pthread_create((&blink),NULL,led_thread,record_struct) ;
            }
            if((my_status& STOP_ACTIVE))
            {
                printf("stop Active");
                record_struct->is_active=0;
                pthread_join(blink,NULL);
            }
            if((my_status&SNAPSHOT_ACTIVE))
            {  snapshot_struct->is_active=1;
                snapshot_struct->rate=SNAPSHOT_RATE;
                pthread_create(&flash,NULL,led_thread,snapshot_struct);
            }
        }
        msleep(500);
        old_status=my_status;
        my_status=my_handler->status;
    }
}
void status_app(handler * my_handler)
{
    pthread_t thread;
    pthread_create((&thread),NULL,status_thread,(void*)my_handler);

}

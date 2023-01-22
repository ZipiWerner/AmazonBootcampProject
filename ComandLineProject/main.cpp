#include <QCoreApplication>

#include "comanddetails.h"
#include "hashtable.h"
#include "comandlinefunc.h"
#include "helpfunc.h"
#include "gas_cam.h"
#include "statusController.h"
#include "command_handler.h"
#include <stdlib.h>
#include <stdio.h>
gazapi_t *p_gaz;
handler* my_handler;
int sockfd;
void sig_handler(int signo)
{
    if (signo == SIGINT)
    {       printf("received SIGINT\n");
        p_gaz->signal_handler_interrupt(my_handler);
        exit(0);
    }

}
int main(int argc, char *argv[]){
    printf("start command line!\n");
    QCoreApplication a(argc, argv);

    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    HashTable* ht = create_table(CAPACITY_HASH);
    p_gaz=load_libary();
    void* handle=p_gaz->init();
    my_handler=(handler*)(handle);
    status_app(my_handler);
    insertCmdDetToHash(ht,start_record_cli,help_start_record,START_RECORD);
    insertCmdDetToHash(ht,stop_record_cli,help_stop_record,STOP_RECORD);
    insertCmdDetToHash(ht,do_snapshot_cli,help_do_snapshot,DO_SNAPSHOT);
    start_command_line(ht);
    while(1)
    {
        printf("nothing\n");

        sleep(2);
    }
    //    p_gaz->start_record(my_handler,NULL);
    //    p_gaz->do_snapshot(my_handler);
    //    sleep(10);
    //    p_gaz->stop_record(my_handler);
    free_table(ht);
}


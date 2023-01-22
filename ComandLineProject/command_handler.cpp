#include "command_handler.h"
#include "comandlinefunc.h"
#include "helpfunc.h"
#include <QCoreApplication>
void start_command_line(HashTable * ht)
{

    char commandStr[30] ;
    gets(commandStr);
    int size=0;

    char ** cmdArr=splitCmd(commandStr,&size);
    struct comandDetails * command=  ht_search(ht,cmdArr[0]);
    if( command!=NULL)
    {
        if(strcmp(cmdArr[size-1],"--help")==0)
            command->helpfunc();
        else
            if(!command->cmdfunc(my_handler,cmdArr,size))
                printf("Sorry, your parameter isnt valid!");
    }
    else{
        printf("Sorry, the command isnt valid!");
    }


}
char ** splitCmd(char * commandStr,int *len)
{

    char delim[] = " ";
    char *ptr = strtok(commandStr, delim);
    int size=0;
    char ** cmdArr=(char**)malloc(sizeof(char*)*size);
    while(ptr != NULL)
    {
        cmdArr=(char**)realloc(cmdArr,sizeof(char*)*++size);
        cmdArr[size-1]=ptr;
        printf("'%s'\n", ptr);
        ptr = strtok(NULL, delim);
    }
    *len=size;
    return cmdArr;
}
void insertCmdDetToHash(HashTable* ht ,cmdFunc cf,helpFunc hf ,char* name)
{
    struct comandDetails * cmdDet= createComandDet(cf,hf,name);
    ht_insert(ht,cmdDet->nameofCmd,cmdDet);

}
gazapi_t* load_libary()
{
   //void* libHandle= dlopen("/home/zipi/sambashare/build-gas_cam-Desktop-Debug/libgas_cam.so.1.0.0",RTLD_LAZY);
    void* libHandle= dlopen("/home/zipi/sambashare/build-gas_camara_libary-Desktop-Debug/libgas_camara_libary.so.1.0",RTLD_LAZY);
    assert(libHandle);
    return (gazapi_t*)dlsym(libHandle,"p_gaz_api");
}

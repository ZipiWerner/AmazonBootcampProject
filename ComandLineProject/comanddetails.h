#ifndef COMANDDETAILS_H
#define COMANDDETAILS_H
#include <stdlib.h>
#include <stdio.h>
#include <gas_cam.h>
typedef int (*cmdFunc)(handler *,char**,int);
typedef void(*helpFunc)();
struct comandDetails{
    cmdFunc cmdfunc;
    helpFunc helpfunc;
    char * nameofCmd;

};
struct comandDetails * createComandDet(cmdFunc cf,helpFunc h,char * str);

#endif // COMANDDETAILS_H

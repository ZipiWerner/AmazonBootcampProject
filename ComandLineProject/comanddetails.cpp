#include "comanddetails.h"

struct comandDetails * createComandDet(cmdFunc cf,helpFunc h,char * str)
{
    struct comandDetails * cmd=(struct comandDetails *)malloc(sizeof(struct comandDetails ));
    cmd->cmdfunc=cf;
    cmd->helpfunc=h;
    cmd->nameofCmd=str;
    return cmd;

}

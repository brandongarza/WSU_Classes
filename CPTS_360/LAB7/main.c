#include "type.h"
#include "lab7.h"
#include "lab7.c"

int main(int argc, char *argv[])
{
    int i, cmd; 
    char line[128], cname[64], parameter[64];
    init();
    mount_root(argv[1]);

    //menu("");
    while(1)
    {
        memset(pathname, 0, 128);
        memset(parameter, 0, 64);
        memset(cname, 0, 64);

        printf("COMMAND$: ");
        fgets(line, 128, stdin);
        line[strlen(line)-1] = 0;
        if (line[0]==0) continue;

        sscanf(line, "%s %s %s", cname, pathname, parameter);

        if(parameter[0] != 0)
        {
            strcat(pathname, " ");
            strcat(pathname, parameter);
        }

        for(i = 0; i < 28; i++)
        {
            if(strcmp(cmnds[i], cname) == 0)
            {
                    fptr[i](pathname);
            }
        }
    }
}

#include "type.h"

#include "util.c"
#include "mount_root.c"
#include "ls.c"
#include "quit.c"
#include "pwd.c"
#include "cd.c"
#include "mkdir.c"
#include "rmdir.c"
#include "creat.c"
#include "link.c"
#include "unlink.c"
#include "symlink.c"
#include "stat.c"
#include "chmod.c"
#include "touch.c"
#include "open.c"
#include "close.c"


int main(int argc, char *argv[]) {

    if (argc > 1) {
        disk = argv[1];
	} else {
		printf("main(): enter disk name\n");
		exit(1);
	}

    init();
    mount_root();

    while (1) {

		printf("\n[ls|cd|pwd|quit|mkdir|rmdir|creat|link|unlink|symlink|stat|chmod|touch|open|close]\n");

        printf("cs360@cmd: ");

        fgets(line, 128, stdin);
        line[strlen(line) - 1] = 0;

        if (strlen(line) == 0) {
			printf("main(): no command entered\n");            
			continue;
		}

		// reset input arrays, after every itteration
		memset(pathname, 0, 64);
		memset(newFileName, 0, 64);
		
        sscanf(line, "%s %s %s", cmd, pathname, newFileName);

	
		void(*fptr[])() = { my_quit, make_dir, creat_file, my_rmdir, my_link, my_symlink, my_unlink, my_stat, my_chmod, my_touch, my_open, my_close, ls, my_chdir, pwd};
 
		int option = findCmd(cmd);    

		if (option != -1) {
			if (option < 4) {
				(*fptr[option])();
			} else if (option == 4 || option == 5) {
				(*fptr[option])(pathname, newFileName);
			} else if (option == 8) {
				char tempstring[64];
				strcpy(tempstring, pathname);
				memset(pathname, 0, 64);
				strcpy(pathname, newFileName);
				memset(newFileName, 0, 64);
				strcpy(newFileName, tempstring);
				(*fptr[option])(pathname);
			}else if (option == 11) {
				(*fptr[option])(pathname[0] - 48); // convert from char to int
			} else {
				(*fptr[option])(pathname);
			}			
		} else {
			printf("Invalid commmand\n");
		}
		
    }
}

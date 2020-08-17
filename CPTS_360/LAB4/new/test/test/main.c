
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <libgen.h> 
#include <fcntl.h> 

#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>
#include <dirent.h>


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: my rcp source destination\n");
    }
    return myrcp(argv[1], argv[2]);
}


int myrcp( char* f1, char* f2)
{
    struct stat s1, s2;

    int f2_status = lstat(f2,&s2);

    if(lstat(f1,&s1) < 0)
    {
        printf("file does not exist\n");

        return 1;
    }


    if(S_ISREG(s1.st_mode) || S_ISLNK(s1.st_mode))
    {
        if(f2_status <0 ||S_ISREG(s2.st_mode) || S_ISLNK(s2.st_mode))
        {
            return cpf2f(f1,f2);
        }
        else
        {
            return cpf2d(f1,f2);
        }
    }


    else if (S_ISDIR(s1.st_mode))
    {
        if(s1.st_ino == s2.st_ino)
        {
        printf( "NO: SAME directory\n");
        }

        if(f2_status >= 0 && !S_ISDIR(s2.st_mode))
        {
            printf("Cannot copy a directory to a non directory file\n");
            return 1;
        }

        else if(f2_status < 0)
        {
            mkdir(f2, s1.st_mode);

            return cpd2d(f1, f2);
        }

        else
        {
            char fullpath1[4096], fullpath2[4096];

            realpath(f1, fullpath1);

            realpath(f2, fullpath2);

            if(strncmp(fullpath1, fullpath2, strlen(fullpath1)) == 0)
            {
                printf("NO: can't copy INTO a subDIR\n");

                return 1;
            }

            char * base = basename(f1);

            char buffer[4096];

            strcat(strcat(strcpy(buffer, f2), "/"), base);

            mkdir(buffer, s1.st_mode);

            return cpd2d(f1, buffer);
        }
    }
}


int cpf2f(char * f1, char * f2)
{
    struct stat s1 ,s2;

    lstat(f1, &s1);

    int f2_exists = lstat(f2, &s2);

    char buffer[4096];


    if(s1.st_ino == s2.st_ino)
    {
        printf("NO: SAME file\n");

        return 1;
    }

    else if(S_ISLNK(s1.st_mode) && f2_exists >= 0)
    {
        printf("Cannot copy a link to another existing file!\n");

        return 1;
    }

    else if(S_ISLNK(s1.st_mode))
    {
        buffer[readlink(f1, buffer, 4096)] = '\0';

        symlink(buffer, f2);

        return 0;
    }

    int fd1 = open(f1, O_RDONLY);

    int fd2 = open(f2, O_WRONLY|O_CREAT|O_TRUNC, s1.st_mode);

    int len;

    while(len = read(fd1, buffer, 4096))
    {
        write(fd2, buffer, len);
    }
    return 0;
}


int cpf2d(char* f1, char* f2)
{
    char * base = basename(f1);
    char destination[4096];

    strcpy(destination, f2);
    strcat(destination, "/");
    strcat(destination, base);

    struct stat s2;

    int exists = stat(destination, &s2);

    if(exists < 0)
    {
        cpf2f(f1, destination);
    }
    else
    {
        if(S_ISDIR(s2.st_mode))
        {
            cpf2d(f1, destination);
        }
        else
        {
            cpf2f(f1, destination);
        }
    }
}


void cpd2d(char *d1, char *d2)
{
    struct stat dstat, stat1, stat2;
    char d3[100];
    char temp[100];

    strcpy(temp, d2);

    //if d2 does not exist, make d2
    if (stat(d2, &dstat) < 0) 
    {
        mkdir(d2, ACCESSPERMS);
        strcpy(d3, d2);
    }
    else
    {
        strcpy(d3, strcat(strcat(temp,"/"), basename(d1)));

        //if d2 does not contain file named basename(d1), make one

        if (check_dir_contain(d1, d2) == 0)
        {
            mkdir(d3, ACCESSPERMS);
        }
    }
    //copy content of d1 over to d3

    copy_content_d2d(d1,d3);
}


//given d1 and d2 exist, copy content of d1 to d2

void copy_content_d2d(char *d1, char *d2)
{
    if (dir_empty(d1) == 1 || strcmp(basename(d1),"..") == 0 ||
        strcmp(basename(d1),".") == 0)
    {
        return;
    }

    struct stat dstat;
    struct dirent *ep;

    DIR *dp = opendir(d1);

    char d3[100];//path of each entry of d1
    char d4[100];//path of each entry of d2

    while (ep = readdir(dp))
    {
        //check type of each entry

        strcpy(d3,d1); strcat(d3, "/"); strcat(d3, ep->d_name);
        strcpy(d4, d2); strcat(d4, "/"); strcat(d4, ep->d_name);

        stat(d3, &dstat);

        if (S_ISREG(dstat.st_mode) == 1)
        {
            cpf2f(d3, d4);
        }
        else if (S_ISDIR(dstat.st_mode) == 1)
        {
            mkdir(d4, ACCESSPERMS);

            copy_content_d2d(d3, d4);
        }
        else
        {
            printf("cp: cannot copy special files\n");

            exit(1);
        }
    }
    closedir(dp);
}


int check_dir_contain(char *f1, char *d1)
{
    int flag = 0;

    char *f1_basename = basename(f1);

    struct dirent *ep;

    DIR *dp = opendir(d1);

    while (ep = readdir(dp))
    {
        if (strcmp(f1_basename, ep->d_name) == 0)
        {
            flag = 1;

            break;
        }
    }
    closedir(dp);

    return flag;
}


int dir_empty(char *d)
{
    int count = 0;

    struct dirent *ep;

    DIR *dp = opendir(d);

    while (ep = readdir(dp))
    {
        count++;

        if (count > 2)
        {
            break;
        }
    }  

    if (count <=2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
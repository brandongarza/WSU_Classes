#ifndef H_H
#define H_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h> //This library allows us to set the files how we want.
#include <unistd.h> //Allows us to use unix commands like chdir and execve

char *commandPath[16];
char *homePath;

//This will get the command paths
getPath()
{
  int i = 0;
  char *tok;
  char *name = "PATH";
  char *tempname = getenv(name);

  tok = strtok(tempname, ":");
  while (tok)
  {
    commandPath[i] = tok;
    tok = strtok(NULL, ":");
    i++;
  }
  commandPath[i] = NULL;
}

//This will get the home path
getHome()
{
  int i = 0;
  int j = 0;
  char *name = "HOME";
  char *tempname = getenv(name);
  homePath = (char*)malloc(sizeof(char)*strlen(tempname));
  while (tempname[i])
  {
    homePath[j] = tempname[i];
    j++;
    i++;
  }
  homePath[j] = 0;
}

//Asks the user for a command and reutrns the input in the form we want
char* getInput()
{
  char input[1024];
  char *temp = NULL;
  int input_length = -1;

  printf("Input commmand: ");
  fgets(input, 1024, stdin);
  input_length = strlen(input);

  temp = (char*)malloc(sizeof(char)*input_length);
  strcpy(temp, input);
  //This gets rid of the newline character from fgets
  if(temp[input_length-1] == '\n')
    temp[input_length-1] = 0;

  return temp;
}

//Parses the input to create an array of args
char** parseInput(char* in_string)
{
  int i = 0;
  char *string = NULL;
  char *tempstring = NULL;
  char **returnArr = (char**)malloc(sizeof(char*)*20);

  string = strtok(in_string, " ");
  while (string)
  {
    tempstring = (char*)malloc(sizeof(char)*strlen(string));
    strcpy (tempstring, string);
    returnArr[i] = tempstring;
    string = strtok(NULL, " ");
    i++;
  }
  returnArr[i] = NULL;
  return returnArr;
}

//Determines the given command and runs it
void runCommand(char** inputArr, char* const envp[])
{
  int i = 0;
  char *temp;

  if (strcmp(inputArr[0], "exit") == 0)
    exit(1);
  else if (strcmp(inputArr[0], "cd") == 0)
  {
    if (inputArr[1])
      chdir(inputArr[1]);
    else
      chdir(homePath);
  }
  else
    forkChild(inputArr, envp);

  //This clears the input_array
  while(inputArr[i])
  {
    free(inputArr[i]);
    i++;
  }
  free(inputArr);
}

int forkChild(char** inputArr, char* const envp[])
{
  int i = 0;
  int status = 0;
  int pipe = 0;
  int pid;
  char** head = NULL;
  char** tail = NULL;

  head = (char**)malloc(sizeof(char*)*20);
  tail = (char**)malloc(sizeof(char*)*20);

  //Prints out myargv
  while(inputArr[i])
  {
    printf("myargv[%d] = %s\n", i, inputArr[i]);
    i++;
  }
  printf("myargv[%d] = %s\n", i, inputArr[i]);
  printf("\n");
  i = 0;

  pid = fork();

  if (pid < 0)
  {
    printf("ERROR: Can't fork!\n");
    exit(1);
  }

  if (pid)
  {
    printf("Forking child with PID = %d\n", pid);
    pid = wait(&status);
  }
  else
  {
    pipe = getPipe(inputArr, head, tail);
    printf ("pipe = %d\n\n", pipe);
    //pipe = 0;
    if(pipe)
    {
      i = 0;
      while(head[i])
      {
        printf("Head[%d] = %s\n", i, head[i]);
        i++;
      }
      printf("Head[%d] = %s\n", i, head[i]);

      i = 0;
      while(tail[i])
      {
        printf("Tail[%d] = %s\n", i, tail[i]);
        i++;
      }
      printf("Tail[%d] = %s\n", i, tail[i]);
      Pipeline(head, tail, envp);
    }
    else
    {
      runInput(inputArr, envp);
    }

  }
  free(head);
  free(tail);
  printf("\nChild has exited with status = %d\n", status);
  return status;
}

//Returns 1 if we have a pipe
int getPipe(char** inputArr, char** head, char** tail)
{
  int i = 0;
  int j = 0;
  int returnval = 0;
  char* tempstr;

  while (returnval == 0 && inputArr[i])
  {
    if (strcmp(inputArr[i], "|") == 0)
    {
      returnval = 1;
      tempstr = inputArr[i];
      inputArr[i] = NULL;
      i++;

      //This sets up the tail portion of the given input
      while(inputArr[i])
      {
        tail[j] = inputArr[i];
        i++;
        j++;
      }
      inputArr[i] = NULL;
      tail[j] = NULL;
      i = 0;
      j = 0;

      while(inputArr[i])
      {
        head[j] = inputArr[i];
        i++;
        j++;
      }
      head[j] = NULL;
    }
    i++;
  }

  return returnval;
}

//This is where we create our pipe
void Pipeline (char** head, char** tail, char* const envp[])
{
  int pid;
  int pd[2];
  int status;

  pipe(pd);

  pid = fork();

  if (pid) //Parent
  {
    close(pd[0]);
    close(1);
    dup(pd[1]);
    pid = wait(&status);
    runInput(tail, envp);
  }
  else //Child
  {
    close(pd[1]);
    close(0);
    dup(pd[0]);
    runInput(head, envp);
  }
}

//Checks if there is a redirect. 1 for input, 2 for output, 3 for append, 0 for none
char* getRedirect (char** inputArr, int* redir)
{
  int i = 1;
  char* temp = NULL;
  char* temp2 = NULL;

  while((*redir) == 0 && inputArr[i])
  {
    if(strcmp(inputArr[i], "<") == 0) //Input
      *redir = 1;
    else if(strcmp(inputArr[i], ">") == 0) //Output
      *redir = 2;
    else if(strcmp(inputArr[i], ">>") == 0) //APPEND
      *redir = 3;

    if (*redir)
    {
      temp = inputArr[i+1];
      temp2 = inputArr[i];
      inputArr[i] = NULL;
      inputArr[i+1] = NULL;
      free(temp2);
    }
    i++;
  }
  return temp;
}

void doRedirect(char* file, int redir)
{
  if (redir == 1)
  {
    close(0);
    open(file, O_RDONLY);
  }
  else if (redir == 2)
  {
    close(1);
    open(file, O_WRONLY|O_CREAT, 0644);
  }
  else if (redir == 3)
  {
    close(1);
    open(file, O_APPEND|O_WRONLY|O_CREAT, 0644);
  }
  else
    printf("ERROR: Could not redirect!\n");

}

//This is for all of the other commands
void otherCommand(char** inputArr, char* const envp[])
{
  int i = 0;
  char cmd[128];
  char new[1024];

  strcpy(cmd, inputArr[0]);
  //This loop checks each bin for the command
  //printf("Searching for the command %s in the following locations:\n", inputArr[0]);
  while(commandPath[i])
  {
    //printf("commandPath[%d] = %s\n", i, commandPath[i]);
    strcpy(new, commandPath[i]);
    strcat(new, "/");
    strcat(new, cmd);
    execve(new, inputArr, envp);
    i++;
  }
  printf ("ERROR: Command %s not found!\n", inputArr[0]);
}

//Checks if there is a redirect and runs
void runInput(char** inputArr, char* const envp[])
{
  int redir = 0;
  char* file = NULL;

  file = getRedirect(inputArr, &redir);
  if(redir)
  {
    doRedirect(file, redir);
  }
  otherCommand(inputArr, envp);
}

#endif
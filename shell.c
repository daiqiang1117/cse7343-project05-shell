/* Qiang Dai
A simple REPL / shell for Unix, for CSE 7343 Project 5
*/
 
#include <stdio.h>
#include <stdlib.h> //abort()
#include <string.h> //strcmp()
#include <stdbool.h> // expands true as 1 and false as 0
#include <unistd.h> //getlogin()
 
#define EXIT 0
#define TYPE 1
#define COPY 2
#define DELETE 3
#define EXECUTE 4
#define ERROR 5
 
char* sysUsername();
void error(char* command);
bool fileExist(char* filename);
int cmdLength(char* command);
int commandType(char* command);
void type(char* filename);
char* firstFileName(char* command);
char* secondFileName(char* command);
void copy(char* source, char* dest);
void delete(char* filename);
void execute(char* filename);
 
/* exit: should terminate the shell
** type <file>: print the contents of `file` to stdout
** copy <source> <dest>: copy `source` to `dest`
** delete <file>: deletes `file`
** attempt to execute a program if not one of the above commands
*/
int main(int argc, char** argv) 
{
  printf("Note: This is another shell!\n");
  char command[100] = {0};
  while (true) {
    memset(command, 0 , strlen(command) + 1);
    printf("%s> ", sysUsername());
    //here has the risk of buffer overflow
    scanf("%s", command);
    switch(commandType(command))
    {
      //0 is Exit
      case 0:
        abort();
      //1 is type
      case 1:
        break;
      //2 is copy
      case 2:
        break;
      //3 is delete
      case 3:
        break;
      //4 is execute
      case 4:
        break;
      //default is error
      default:
        error(command);
    }
  }
  return 0;
}
 
//return the current system username
//this method should be update to use safer function
//reference : http://linux.die.net/man/3/getlogin_r
char* sysUsername() 
{
  return getlogin();
}
 
// Displays an error message on stdout
void error(char* command) 
{
  printf("Command not found: %s\n", command);
}


//reference on stackoverflow
bool fileExist(char* filename)
{
  if( access (filename, F_OK) != -1)
    return 1;
  return 0;
}

int cmdLength(char* command)
{
  char *pch;
  pch = strchr(command, ' ');
  if(pch != NULL)
    return pch - command + 1;
  else
    return strlen(command);
}

// return the command type: 0 is exit, 1 is type, 2 is copy, 3 is delete, 4 is execute
int commandType(char* command) 
{
  //TODO
  int const len = cmdLength(command);
  char cmd[len];
  strncpy(cmd, command, len);
  if (!strncmp(cmd, "exit", 4))
    return EXIT;
  else if (!strncmp(cmd, "copy", 4))
    return COPY;
  else if (!strncmp(cmd, "delete", 6))
    return DELETE;
  else if (fileExist(cmd))
    return EXECUTE;
  else
    return ERROR;
}
 
// Prints the contents of `filename` to stdout
void type(char* filename) 
{
  // TODO
}
 
// Copies the bytes from `source` to `dest`
void copy(char* source, char* dest) {
  // TODO
}
 
// Deletes a file named `filename`
void delete(char* filename) 
{
  // TODO
}
 
// Executes a program named `filename`
void execute(char* filename) 
{
  // TODO
}
 
// Returns the second word in a command phrase
char* firstFileName(char* command) 
{
  // TODO
  return 0;
}
 
// Returns the third word in a command phrase
char* secondFileName(char* command) 
{
  // TODO
  return 0;
}
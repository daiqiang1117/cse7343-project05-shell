/* Qiang Dai
A simple REPL / shell for Unix, for CSE 7343 Project 5
*/
 
#include <stdio.h>   //basic I/O
#include <stdlib.h>  //abort()
#include <string.h>  //strcmp(), strchr(), strlen()
#include <stdbool.h> //expands true as 1 and false as 0
#include <unistd.h>  //getlogin()
 
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
char* firstFileName(char* command, int cmdType);
char* secondFileName(char* command, int cmdType);

void type(char* filename);
void copy(char* source, char* dest);
void delete(char* filename);
void execute(char* filename);
 
/* exit: should terminate the shell
** type <file>: print the contents of `file` to stdout
** copy <source> <dest>: copy `source` to `dest`
** delete <file>: deletes `file`
** attempt to execute a program if not one of the above commands
*/

//to store first file name on heap
char* name1;
//to store second file name on heap
char* name2;

int main(int argc, char** argv) 
{
  printf("Note: This is another shell!\n");
  char command[100] = {0};
  while (true) {
    memset(command, 0 , strlen(command) + 1);
    printf("%s> ", sysUsername());
    //that is c style input include space
    scanf("%[^\n]%*c", command);
    printf("Command: %s\n", command);
    
    switch(commandType(command))
    {
      //0 is Exit
      case 0:
        abort();

      //1 is type
      case 1:
        //invalidate type
        if(blankNum(command) != 1){
          printf("try \'type <filename>\'\n");
          break;
        }
        else
        {
          type(firstFileName(command, TYPE));
          free(name1);
        }
        break;

      //2 is copy
      case 2:
        //invalidate copy
        if(blankNum(command) != 2){
          printf("try \'copy <filename1> <filename2>\'\n");
          break;
        }
        else{
          copy(firstFileName(command, COPY), secondFileName(command, COPY));
          free(name1);
          free(name2);
        }
        break;

      //3 is delete
      case 3:
        //invalidate delete
        if(blankNum(command) != 1){
          printf("try \'delete <filename>\'\n");
          break;
        }
        else
        {
          delete(firstFileName(command, TYPE));
          free(name1);
        }
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

int blankNum(char* command){
  char *pch;
  int i = 0;
  pch = strchr(command, ' ');
  while(pch != NULL){
    i++;
    pch = strchr(pch + 1, ' ');
  }
  return i;
}

int cmdLength(char* command)
{
  char *pch;
  pch = strchr(command, ' ');
  if(pch != NULL)
    return pch - command;
  else
    return strlen(command);
}

// return the command type: 0 is exit, 1 is type, 2 is copy, 3 is delete, 4 is execute
int commandType(char* command) 
{
  //TODO
  // int const len = cmdLength(command);
  // char cmd[len];
  // strncpy(cmd, command, len);
  if (!strcmp(command, "exit"))
    return EXIT;
  else if (!strncmp(command, "type", 4))
    return TYPE;
  else if (!strncmp(command, "copy", 4))
    return COPY;
  else if (!strncmp(command, "delete", 6))
    return DELETE;
  else if (fileExist(command))
    return EXECUTE;
  else
    return ERROR;
}
 
// Prints the contents of `filename` to stdout
// Reference: stackoverflow
void type(char* filename) 
{
  // TODO
  if(fileExist(filename))
  {
    int c;
    FILE *file;
    file = fopen(filename, "r");
    if (file) {
      while ((c = getc(file)) != EOF)
        putchar(c);
      printf("\n");
      fclose(file);
    }
  }
  else
    printf("File \'%s\' doesn't exist \n", filename);
}
 
// Copies the bytes from `source` to `dest`
void copy(char* source, char* dest) {
  // TODO
  if(fileExist(source)){
    int c;
    FILE *fs, *fd;
    fs = fopen(source, "r");
    fd = fopen(dest, "w");
    if (fs && fd) {
      while ((c = getc(fs)) != EOF)
        putc(c, fd);
      fclose(fs);
      fclose(fd);
    }
  }
  else
    printf("Source file \'%s\' doesn't exist \n", source);
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
char* firstFileName(char* command, int cmdType) 
{
  // TODO
  char *ptr = command + cmdLength(command) + 1;
  int nameLen;
  char *pch;
  if(cmdType == TYPE || cmdType == DELETE)
    pch = strchr(ptr, '\0');
  else
    pch = strchr(ptr, ' ');
  nameLen = pch - ptr;
  name1  = (char *)malloc(nameLen);
  strncpy(name1, ptr, nameLen);
  return name1;
}
 
// Returns the third word in a command phrase
char* secondFileName(char* command, int cmdType) 
{
  // TODO
  char *ptr, *pch;
  ptr = strchr(command, ' ');
  ptr = strchr(ptr + 1, ' ');
  pch = strchr(++ptr , '\0');
  int nameLen = pch - ptr ;
  name2  = (char *)malloc(nameLen);
  strncpy(name2, ptr, nameLen);
  return name2;
}
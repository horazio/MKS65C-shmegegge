#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

int main(){
  int id;
  char * data;
  char response[256];
  if((id = shmget(420, 200 * sizeof(char), 0664 | IPC_CREAT)) == -1){
    printf("Errror: %s\n", strerror(errno));
    exit(1);
  }
  data = shmat(id, NULL, 0);
  if(strlen(data) == 0){
    printf("The memory was just created\n");
  }else{
    printf("This is the shared memory:\n%s\n", data);
  }
  
  printf("Would you like to change the data? (yes/no) ");
  fgets(response, 256, stdin);
  
  if(!strcmp(response, "yes\n")){
    printf("What will it be? ");
    fgets(response, 256, stdin);
    strcpy(data, response);
    printf("Wrote\n");
  }
  
  printf("Would you like to delete the segment? (yes/no) ");
  fgets(response, 256, stdin);
  if(!strcmp(response, "yes\n")){
    shmctl(id, IPC_RMID, NULL);
  }else{
    shmdt(data);
  }
  
  return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(){
  int f, randtime, fd, bytes;
  int * ray = malloc(8);
      
  fd = open("/dev/random",O_RDONLY);
    if(fd < 0){
        printf("Error opening random\n");
        return 0;
    }
  bytes = read(fd,ray,8);
  if(bytes < 0){
    printf("Error reading random\n");
    return 0;
  }
  close(fd);
  
  printf("Forking now\n");
  f = fork();

  if(f){ //parent process 
    f = fork();
    if(f){ //parent process
      int status, childPID;
      childPID = wait(&status);
      printf("%d finished after sleeping %d seconds\n", childPID, WEXITSTATUS(status));
      printf("Parent is done\n");
    }
    else{ //child 2 process
      randtime = (abs(ray[1]) % 16) + 5;
      free(ray);
      printf("Child 2: my PID is %d\n", getpid());
      printf("Child 2 sleeping for %d seconds\n",randtime);
      sleep(randtime);
      printf("Child 2 is done\n");
      return randtime;
    }
  }
  else{ //child 1 process
    randtime = (abs(ray[0]) % 16) + 5;
    free(ray);
    printf("Child 1: my PID is %d\n", getpid());
    printf("Child 1 sleeping for %d seconds\n",randtime);
    sleep(randtime);
    printf("Child 1 is done\n");
    return randtime;
  }
  return 0;
}

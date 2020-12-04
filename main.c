#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int f, f2, status, num1, num2, parentpid;

int main() {

  srand(time(0));
  parentpid = getpid();
  printf("Parent  PID: %d\n", parentpid);
  f = fork();
  if (getpid()==parentpid) {
    f2 = fork();
  }
  num1 = num2 = rand()%9+2;
  while (num1==num2) {
    num2 = rand()%9+2;
  }
  if (!f) { // CHILD 1:
    printf("Child 1 PID: %d\n", getpid());
    sleep(num1);
    printf("Child 1 finished sleeping.\n");
    return num1;
  }
  else {
    if (!f2) { // CHILD 2:
      printf("Child 2 PID: %d\n\n", getpid());
      sleep(num2);
      printf("Child 2 finished sleeping.\n");
      return num2;
    }
    else { // PARENT:
      if (num1<num2) {
        int child1pid = waitpid(f, &status, 0);
        printf("Child 1 PID: %d\tSlept for %d seconds.\n\n", child1pid, WEXITSTATUS(status));
        int child2pid = waitpid(f2, &status, 0);
        printf("Child 2 PID: %d\tSlept for %d seconds.\n\n", child2pid, WEXITSTATUS(status));
      }
      else {
        int child2pid = waitpid(f2, &status, 0);
        printf("Child 2 PID: %d\tSlept for %d seconds.\n\n", child2pid, WEXITSTATUS(status));
        int child1pid = waitpid(f, &status, 0);
        printf("Child 1 PID: %d\tSlept for %d seconds.\n\n", child1pid, WEXITSTATUS(status));
      }
      printf("Parent is finished. Ended program.\n");
    }
  }

  return 0;

}

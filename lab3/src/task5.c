#include <unistd.h>
#include <stdio.h>

void main(int argc, char *argv[])
{
  printf("Будет выполнена программа %s...\n\n",
         argv[0]);
  printf("Выполняется %s", argv[0]);
  pid_t pid;
  switch(pid=fork())
  {
      case 0:
        execl("parallel_min_max"," ","--seed" ,"3", "--array_size", "10", "--pnum", "2", NULL);
      exit(0);
      default:
      printf("Hello, Wordl!");
      return;
  }
  //execl("parallel_min_max"," ","--seed" ,"3", "--array_size", "10", "--pnum", "2", NULL);
  //return;
}
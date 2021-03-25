#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <time.h>

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args) {
  int sum = 0;
  // TODO: your code here 
  for(int i = args->begin; i < args->end; i++)
  {
   sum += *(args->array+i); 
  }
  printf("%d \n", sum);
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  /*
   *  TODO:
   *  threads_num by command line arguments
   *  array_size by command line arguments
   *	seed by command line arguments
   */
  

  uint32_t threads_num = -1;
  uint32_t array_size = -1;
  uint32_t seed = -1;
  
while (true) {
int current_optind = optind ? optind : 1;

   static struct option options[] = {{"threads_num", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"seed", required_argument, 0, 0},
                                      {0, 0, 0}};
  
  int option_index = 0;
  int c = getopt_long(argc, argv, "f", options, &option_index);

  
  
  if (c == -1) break;
  
   switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            threads_num = atoi(optarg);
            // your code here
            // error handling
            printf("%d\n", threads_num);
            if(threads_num <= 0)
            {
             printf("threads_num is a positive number\n");
             return 1; 
            }
            break;
          case 1:
            array_size = atoi(optarg);
            //printf("%d\n", &array_size);
            // your code here
            // error handling
            if (array_size <= 0) {
             printf("array_size is a positive number\n");
             return 1;
            }
            break;
          case 2:
            seed = atoi(optarg);
            // your code here
            // error handling
            if (seed <= 0) {
             printf("seed is a positive number\n");
             return 1;
            }
            break;
            
          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }

if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || threads_num == -1 ) {
    printf("Usage: %s --threads_num \"num\" --array_size \"num\" --seed \"num\" \n",
           argv[0]);
    return 1;
  }
pthread_t threads[threads_num];
printf("%d %d %d \n", threads_num, seed, array_size);
  /*
   * TODO:
   * your code here
   * Generate array here
   */
   
  

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  for(int i =0; i < array_size; i++)
  {
      printf("%d ", array[i]);
  }

clock_t begin = clock();


int thread_len = array_size/threads_num;
int extra_len = array_size - thread_len*threads_num; 

  struct SumArgs args[threads_num];
  for(int i =0; i < threads_num; i++)
  {
      
      if( i == threads_num - 1)
      {
          args[i].begin = i*thread_len;
          args[i].end = array_size;
      }
      else 
      {
        args[i].begin = i*thread_len;
        args[i].end = (i+1)*thread_len;
      }
  }

  for (uint32_t i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    printf("%d \n", sum);
    total_sum += sum;
  }

  free(array);
  printf("Total: %d\n", total_sum);
  clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("Time: %lf\n", time_spent);

  
  return 0;
}

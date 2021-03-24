#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args) {
  int sum = 0;
  // TODO: your code here 
  for(int i = args.begin; i < args.end; i++)
  {
   sum += args.array[i]; 
  }
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
  int current_optind = optind ? optind : 1;
   static struct option options[] = {{"threads_num", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"seed", required_argument, 0, 0},
                                      {0, 0, 0}};
  
  int option_index = 0;
  int c = getopt_long(argc, argv, "f", options, &option_index);

  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;
  
  pthread_t threads[threads_num];
  
  if (c == -1) break;
  
   switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            threads_num = atoi(optarg);
            // your code here
            // error handling
            if(threads_num <= 0)
            {
             printf("threads_num is a positive number\n");
             return 1; 
            }
            break;
          case 1:
            array_size = atoi(optarg);
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
            }
          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  

  /*
   * TODO:
   * your code here
   * Generate array here
   */
  

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

  struct SumArgs args[threads_num];
  for (uint32_t i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args)) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (uint32_t i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  free(array);
  printf("Total: %d\n", total_sum);
  return 0;
}

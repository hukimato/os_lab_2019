#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int k = -1;
int mod = -1;
int pnum = -1;
/* A shared variable for two threads */
int answer = 1;


pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void factorial (int *num)
{
    
    while(*num > 1)
    {
        /*pthread_mutex_lock(&mut);
        answer = (answer * ((k/mod) % 2 ? mod-1 : 1)) % mod;
		for (int i=2; i<=k%mod; ++i)
        {
            
			answer = (answer * i) % mod;
             pthread_mutex_unlock(&mut);
        }
		k /= mod;*/


        pthread_mutex_lock(&mut);
        
        //answer = ((answer%mod)*((*num)%mod))%mod;
        answer = answer**num;
        printf("answer = %d\n", answer);
        (*num)--;
        printf("num = %d\n", *num);
        
        pthread_mutex_unlock(&mut);
    }
    
}
  

int main(int argc, char **argv) {
  //int k = -1;
  //int mod = -1;
  //int pnum = -1;

while (1) {
 int current_optind = optind ? optind : 1;

static struct option options[] = {{"k", required_argument, 0, 0},
                                    {"pnum", required_argument, 0, 0},
                                    {"mod", required_argument, 0, 0},
                                    {0, 0, 0}};

 int option_index = 0;
 int c = getopt_long(argc, argv, "f", options, &option_index);

 if (c == -1) break;
 switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            k = atoi(optarg);
            // your code here
            // error handling
            if(k <= 0)
            {
             printf("seed is a positive number\n");
             return 1; 
            }
            break;
          case 1:
            pnum = atoi(optarg);
            // your code here
            // error handling
            if (pnum <= 0) {
             printf("array_size is a positive number\n");
             return 1;
            }
            break;
          case 2:
            mod = atoi(optarg);
            // your code here
            // error handling
            if (mod <= 0) {
             printf("pnum is a positive number\n");
             return 1;
            }
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      default:
        printf("getopt returned character code 0%o?\n", c);
    }
  }
printf("%d %d %d %d\n", k,pnum,mod, answer);
const int PNUM = pnum;
pthread_t threads[PNUM];


for (int i = 0; i < pnum+1; i++) {
    if (pthread_create(&threads[i], NULL, (void *)factorial, (void*) &k) != 0) {
        printf("main error: can't create thread\n");
        exit(1);
    }
}


for (int i = 0; i < pnum+1; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
        printf("main error: can't join thread, status\n");
        exit(1);
    }
    printf("joined\n");
}
printf("Answer = %d\n", answer%mod);

return 0;
}



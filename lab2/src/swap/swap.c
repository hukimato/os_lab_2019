#include "swap.h"

void Swap(char *left, char *right)
{
	char* tmp = (char*)malloc(sizeof(char));
    *tmp = *left;
    *left = *right;
    *right = *tmp;
}

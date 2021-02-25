#include "revert_string.h"

void RevertString(char *str)
{
    int lenght = strlen(str);
    for(int j=0; j < lenght/2; ++j)
    {
        str[j] = str[j] + str[lenght-j-1];
        str[lenght-j-1]=str[j]-str[lenght-j-1];
        str[j]=str[j]-str[lenght-j-1];
    }


	/*char* tmp = (char*)malloc(sizeof(char) * (strlen(str)+1));
    for (int i =0; i <= strlen(str); i++)
    {
        tmp[i] = str[strlen(str)-i-1];
    }
    tmp[strlen(str)] = '\0';
    return tmp;*/
}


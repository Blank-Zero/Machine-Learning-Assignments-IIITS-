#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fptr;
    fptr = fopen("dataset-2.txt","r");

    fclose(fptr);
}
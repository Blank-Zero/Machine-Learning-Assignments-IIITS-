#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct set
{
    /* data */
    float area;
    float perimeter;
    float compactness;
    float length_of_kernel;
    float width_of_kernel;
    float asymmetry_coefficient;
    float length_of_kernel_groove;
    int class;
} SET;

void ReadAll(FILE *fptr,SET *data[],int max)
{
    int i=0;
    while(!feof(fptr) && i<max)
    {
        data[i] = (SET *)malloc(sizeof(SET));
        fscanf(fptr,"%f",&(data[i]->area));
        fscanf(fptr,"%f",&(data[i]->perimeter));
        fscanf(fptr,"%f",&(data[i]->compactness));
        fscanf(fptr,"%f",&(data[i]->length_of_kernel));
        fscanf(fptr,"%f",&(data[i]->width_of_kernel));
        fscanf(fptr,"%f",&(data[i]->asymmetry_coefficient));
        fscanf(fptr,"%f",&(data[i]->length_of_kernel_groove));
        fscanf(fptr,"%d",&(data[i]->class));
        ++i;
    }
}

void Swap(int *a,int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
    return;
}

void DataSwap(SET *data[],SET *newdata[],int num[],int max)
{
    int i;
    for(i=0;i<max;i++)
        newdata[i] = data[num[i]];    
    return;
}

int main()
{
    srand((unsigned int)time(NULL));

    FILE *filePointer;
    filePointer = fopen("seeds.txt","r");

    if(filePointer == NULL)
    {
        printf("failed to open the file");
        return 0;
    }
    printf("Works fine\n");
    
    SET *data[210];

    ReadAll(filePointer,data,210);

    fclose(filePointer);

    int num[210];
    int i;
    for(i=0;i<210;i++)
        num[i] = i;

    for(i=0;i<1000;i++)
        Swap(&(num[rand()%210]),&(num[rand()%210]));
    
    SET *newdata[210];
    DataSwap(data,newdata,num,210);
    
    FILE *filewriter;
    filewriter = fopen("SwapedSeeds.txt","w");
    
    for(i=0;i<210;i++)
        fprintf(filewriter,"%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n",newdata[i]->area,newdata[i]->perimeter,newdata[i]->compactness,newdata[i]->length_of_kernel,newdata[i]->width_of_kernel,newdata[i]->asymmetry_coefficient,newdata[i]->length_of_kernel_groove,newdata[i]->class);

    fclose(filewriter);

    return 0;
}
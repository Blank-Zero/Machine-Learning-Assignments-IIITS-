#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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


// void read_values(FILE *fptr)
// {
//     float i = 0;
//     fscanf(fptr,"%f",&i);
//     printf("%f\n",i);

//     int count = 8;
//     while(!feof(fptr) && count > 0)
//     {
//         fscanf(fptr,"%f",&i);
//         printf("%f\n",i);
//         --count;
//     }
//     return;
// }

void WriteTestValues(SET *test)
{
    printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%d\n",test->area,test->perimeter,test->compactness,test->length_of_kernel,test->width_of_kernel,test->asymmetry_coefficient,test->length_of_kernel_groove,test->class);
}

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

int main()
{
    // printf("Hello world");
    FILE *filePointer;
    filePointer = fopen("seeds.txt","r");

    if(filePointer == NULL)
    {
        printf("failed to open the file");
        return 0;
    }
    printf("Works fine\n");
    // read_values(filePointer);
    
    SET *data[210];

    ReadAll(filePointer,data,210);

    fclose(filePointer);
    // WriteTestValues(data[5]);
    return 0;
}
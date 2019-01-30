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

void WriteTestValues(SET *test[],int n)
{
    int i;
    for(i=0;i<n;i++){
        printf("%f\t%f\t%f\n",test[i]->area,test[i]->perimeter,test[i]->compactness);
    }

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

    // WriteTestValues(data[5]);
    int i,r=7;

    // SET *test;
    // test=data[0];
    // printf("%f\n",test->area );
    SET *test[210/r];
    SET *train[210-(210/r)];
    for(i=0;i<7;i++){
      int j;
      for (j=30*i;j<30*(i+1);j++){
        test[j-(30*i)]=data[j];
      }
      int limit=0;
      for (j=0;j<210;j++){
        if(j<30*i || j>=30*(i+1)){
          train[limit]=data[j];
          printf("%d\t%d\n",j,limit);
          ++limit;
        }
      }
    }
    WriteTestValues(&test,30);
    printf("\n\n");
    WriteTestValues(&train,180);
    return 0;
}

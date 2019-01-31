#include<stdio.h>
#include<stdlib.h>

typedef struct Mat
{
    int mat[32][32];
    int class;
} MAT;

void GetMatrix(FILE *fptr,int arr[32][32],int *class)
{
    int i,j;
    for(i=0;i<32;i++)
    {
        for(j=0;j<32;j++)
        {
            arr[i][j] = (int)fgetc(fptr) - 48;
        }
        if(fgetc(fptr) == '\n')
            continue;
    }
    fscanf(fptr,"%d",class);
    return;
}

void PrintMatrix(int arr[][32])
{
    int i,j;
    for(i=0;i<32;i++)
    {
        for(j=0;j<32;j++)
        {
            printf("%d",arr[i][j]);
        }
        printf("\n");
    }
    return;
}

int main()
{
    FILE *fptr;
    fptr = fopen("dataset-2.txt","r");
    // int *arr[32][32] = (int *)malloc(sizeof(int[32][32]));
    // int arr[32][32];
    // int class[1934];
    MAT *dataset[1934];
    int i;
    for(i=0;i<1934;i++)
    {
        dataset[i] = (MAT *)malloc(sizeof(MAT));
        GetMatrix(fptr,dataset[i]->mat,&(dataset[i]->class));
        if(fgetc(fptr)=='\n')
            printf("\n%d\n",dataset[i]->class);
        // PrintMatrix(dataset[i]->mat);
        
    }
    // GetMatrix(fptr,arr);
    
    // PrintMatrix(arr);
    fclose(fptr);
}
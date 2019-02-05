#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define data_count 1930
#define r_value 15
#define cls_count 10

typedef struct Mat
{
    int mat[32][32];
    int class;
} MAT;

float mod(float x){
  if(x<0){
    return (-1)*x;
  }
  return x;

}

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
    printf("\n\n");
    return;
}

void SortUpto_K(float kon[][2],int k,int max)
{
    int i;
    int j;
    for(i=0;i<k;i++)
    {
      int min = i;

      for(j=i;j<max;j++)
      {
        if(kon[min][0] > kon[j][0])
        {
          min = j;
        }
      }
      float temp = kon[min][0];
      kon[min][0] = kon[i][0];
      kon[i][0] = temp;
      temp = kon[min][1];
      kon[min][1] = kon[i][1];
      kon[i][1] = temp;

    }
}

float Minkowski_distance(int p,MAT *test,MAT *train){
  int l,m;
  float distance_of_test=0;
  for(l=0;l<32;l++){

    for(m=0;m<32;m++){

        distance_of_test=distance_of_test+mod(pow((test->mat[l][m]-train->mat[l][m]),p));
    }
  }
  distance_of_test=pow(distance_of_test,1.0/p);
  // printf("%f\n",distance_of_test );
  return distance_of_test;

}

int FindMaxClass(float kon[][2],MAT *train[],int k)
{
    int arrClassCount[cls_count];
    int i;
    for(i=0;i<cls_count;i++)
      arrClassCount[i] = 0;
    for(i=0;i<k;i++)
    {
      //printf("%d\n", train[((int)kon[i][1])]->class);
      ++arrClassCount[train[((int)kon[i][1])]->class];
    }
    int max = 0;
    for(i=1;i<cls_count;i++)
    {
      if(arrClassCount[max] < arrClassCount[i])
        max = i;
    }
    return max+1;
}

float FindAccuracy(int k,int p,MAT *test[],MAT *train[],int l){
    int i,j;
    int true=0;

    float distance_of_test;
    int assign[data_count/r_value];
    for(i=0;i<data_count/r_value;i++){
        float kon[data_count-(data_count/r_value)][2];
            //printf("%d\n",data_count-(data_count/r_value));
        for(j=0;j<data_count-(data_count/r_value);j++){
            //printf("%d\t%d\n",j,train[j]->class );
            distance_of_test=Minkowski_distance(p,test[i],train[j]);
            kon[j][0]=distance_of_test;
            kon[j][1]=j;
        }
        SortUpto_K(kon,k,data_count-(data_count/r_value));
        int z,y;
        for(z=0;z<k;z++){
          //printf("%f\t%d\n",kon[z][0],train[((int)kon[i][1])]->class);
        }
        //printf("\n");
        assign[i] = FindMaxClass(kon,train,k)-1;
        //printf("%d\t%d\n",assign[i],test[i]->class );
        if(assign[i]==test[i]->class)
          ++true;

    }
    return (true/(1.0*data_count/r_value))*100;
}


void R_fold(MAT *dataset[]){
    MAT *test[data_count/r_value];
    MAT *train[data_count-(data_count/r_value)];
    int l,m;
    int k=7,p=2;
    int test_count=data_count/r_value;
    int train_count=data_count-(data_count/r_value);

    float accuracy[r_value];
    for(l=0;l<r_value;l++){

      for (m=test_count*l;m<test_count*(l+1);m++){
        test[m-(test_count*l)]=dataset[m];
        // printf("%d\t%d\n",m-(test_count*l),m );
        //PrintMatrix(test[m-(test_count*l)]->mat);
      }

      int limit=0;
      for (m=0;m<data_count;m++){
        if(m<test_count*l || m>=test_count*(l+1)){
          train[limit]=dataset[m];

          //PrintMatrix(train[limit]->mat);
          ++limit;
        }

      }
          //////        finding k and p values    ////////

      accuracy[l]= FindAccuracy(k,p,test,train,l);
      printf("%d\t%f%\n",l+1,accuracy[l]);

    }


}

int main()
{
    FILE *fptr;
    fptr = fopen("dataset-2.txt","r");
    // int *arr[32][32] = (int *)malloc(sizeof(int[32][32]));
    // int arr[32][32];
    // int class[1934];
    MAT *dataset[data_count];
    int i;
    for(i=0;i<data_count;i++)
    {
        dataset[i] = (MAT *)malloc(sizeof(MAT));
        GetMatrix(fptr,dataset[i]->mat,&(dataset[i]->class));
        if(fgetc(fptr)=='\n');
          //  printf("\n%d\n",dataset[i]->class);
        // PrintMatrix(dataset[i]->mat);

    }
    // GetMatrix(fptr,arr);

    // PrintMatrix(arr);
    fclose(fptr);
    R_fold(dataset);




}

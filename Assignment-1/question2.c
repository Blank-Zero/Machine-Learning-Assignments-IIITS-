#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define TestSetsCount 1930
#define RFold 15
#define MaxClass 10

typedef struct data                           
{
    int dat[32][32];
    int Cl;
} DATAMat;

float Absolute(float x){
  if(x<0){
    return (-1)*x;
  }
  return x;

}

void TakeData(FILE *fptr,int arr[32][32],int *class)
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

void PrintData(int arr[][32])
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

void FindMinofK(float DistanceData[][2],int k,int max)
{
    int i;
    int j;
    for(i=0;i<k;i++)
    {
      int min = i;

      for(j=i;j<max;j++)
      {
		if(DistanceData[min][0] > DistanceData[j][0])
		{
		  min = j;
		}
      }
      float temp = DistanceData[min][0];
      DistanceData[min][0] = DistanceData[i][0];
      DistanceData[i][0] = temp;
      temp = DistanceData[min][1];
      DistanceData[min][1] = DistanceData[i][1];
      DistanceData[i][1] = temp;

    }
}

float FindMinDistance(int p,DATAMat *test,DATAMat *train){
  int l,m;
  float distance=0;
  for(l=0;l<32;l++){

    for(m=0;m<32;m++){

        distance=distance+Absolute(pow((test->dat[l][m]-train->dat[l][m]),p));
    }
  }
  distance=pow(distance,1.0/p);
  return distance;

}

int FindMaxClass(float DistanceData[][2],DATAMat *train[],int k)
{
    int ClassesMatch[MaxClass];
    int i;
    for(i=0;i<MaxClass;i++)
      ClassesMatch[i] = 0;
    for(i=0;i<k;i++)
    {
      ++ClassesMatch[train[((int)DistanceData[i][1])]->Cl];
    }
    int max = 0;
    for(i=1;i<MaxClass;i++)
    {
      if(ClassesMatch[max] < ClassesMatch[i])
        max = i;
    }
    return max+1;
}

float Precision(int k,int p,DATAMat *test[],DATAMat *train[],int l){
    int i,j;
    int true=0;

    float distance;
    int assign[TestSetsCount/RFold];
    for(i=0;i<TestSetsCount/RFold;i++){
        float DistanceData[TestSetsCount-(TestSetsCount/RFold)][2];
        for(j=0;j<TestSetsCount-(TestSetsCount/RFold);j++){
            distance=FindMinDistance(p,test[i],train[j]);
            DistanceData[j][0]=distance;
            DistanceData[j][1]=j;
        }
        FindMinofK(DistanceData,k,TestSetsCount-(TestSetsCount/RFold));
        int z,y;
        assign[i] = FindMaxClass(DistanceData,train,k)-1;
        if(assign[i]==test[i]->Cl)
          ++true;

    }
    return (true/(1.0*TestSetsCount/RFold))*100;
}


void CrossValidation(DATAMat *dataset[]){
    DATAMat *test[TestSetsCount/RFold];
    DATAMat *train[TestSetsCount-(TestSetsCount/RFold)];
    int l,m;
    int k=7,p=2;
    int test_count=TestSetsCount/RFold;
    int train_count=TestSetsCount-(TestSetsCount/RFold);

    float accuracy[RFold];
    for(l=0;l<RFold;l++){

      for (m=test_count*l;m<test_count*(l+1);m++){
        test[m-(test_count*l)]=dataset[m];
      }

      int limit=0;
      for (m=0;m<TestSetsCount;m++){
        if(m<test_count*l || m>=test_count*(l+1)){
          train[limit]=dataset[m];

          ++limit;
        }
      }
      accuracy[l]= Precision(k,p,test,train,l);
      printf("%d\t%f%\n",l+1,accuracy[l]);
    }


}

int main()
{
    FILE *fptr;
    fptr = fopen("dataset-2.txt","r");
    DATAMat *dataset[TestSetsCount];
    int i;
    for(i=0;i<TestSetsCount;i++)
    {
        dataset[i] = (DATAMat *)malloc(sizeof(DATAMat));
        TakeData(fptr,dataset[i]->dat,&(dataset[i]->Cl));
        if(fgetc(fptr)=='\n');
    }
    fclose(fptr);
    CrossValidation(dataset);
}

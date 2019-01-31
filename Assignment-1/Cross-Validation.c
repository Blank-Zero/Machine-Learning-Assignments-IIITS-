#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

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


void WriteTestValues(SET *test[],int n)
{
    int i;
    for(i=0;i<n;i++){
        printf("%f\t%f\t%d\n",test[i]->area,test[i]->perimeter,test[i]->class);
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

float Minkowski_distance(int p,float area,float perimeter,float compactness,float length_of_kernel,float width_of_kernel,float asymmetry_coefficient,float length_of_kernel_groove){
  double distance;
  distance=pow(area,p)+pow(perimeter,p)+pow(compactness,p)+pow(length_of_kernel,p)+pow(width_of_kernel,p)+pow(asymmetry_coefficient,p)+pow(length_of_kernel_groove,p);
  distance=pow(distance,1.0/p);
  return distance;
}

// void Swap(float *a,float *b)
// {
//     *a = *a ^ *b;
//     *b = *a ^ *b;
//     *a = *a ^ *b;
//     return;
// }

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
<<<<<<< HEAD
        }
=======
          // Swap(&(min[0]),&(kon[j][0]));
          // Swap(&(min[1]),&(kon[j][1]));
        }
>>>>>>> dc420e2dbd2fed8eb9b1a01bcb354e83928443fc
      }
      float temp = kon[min][0];
      kon[min][0] = kon[i][0];
      kon[i][0] = temp;
      temp = kon[min][1];
      kon[min][1] = kon[i][1];
      kon[i][1] = temp;

    }
}

int FindMaxClass(float kon[][2],SET *train[],int k,int clscount)
{
    int arrClassCount[clscount];
    int i;
    for(i=0;i<clscount;i++)
      arrClassCount[i] = 0;
    for(i=0;i<k;i++)
    {
      ++arrClassCount[train[((int)kon[i][1])]->class - 1];
    }
    int max = 0;
    for(i=1;i<clscount;i++)
    {
      if(arrClassCount[max] < arrClassCount[i])
        max = i;
    }
    return max+1;
}

int main()
{
    int l,m;
    FILE *filePointer;
    filePointer = fopen("SwapedSeeds.txt","r");

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
    int r=7;

    // SET *test;
    // test=data[0];
    // printf("%f\n",test->area );
    SET *test[210/r];
    SET *train[210-(210/r)];
    for(l=0;l<7;l++){

      for (m=30*l;m<30*(l+1);m++){
        test[m-(30*m)]=data[m];
      }
      int limit=0;
      for (m=0;m<210;m++){
        if(m<30*l || m>=30*(l+1)){
          train[limit]=data[m];
          ++limit;
        }
      }
      printf("hello %d\n",l);
          //////        finding k and p values    ////////

      int k=9,p=2;
      float distace_of_test;
      int assign[210/r];
      int true = 0;
      // for(i=0;i<30;i++)
      //   assign[i] = 0;
      int i,j;
      for(i=0;i<(210/r);i++){
        float kon[210-210/r][2];
        printf("hello%d  %d\n",i,210/r);

        for (j=0;j<210-(210/r);j++){
          printf("%d\n",j);

          distace_of_test=Minkowski_distance(p,train[j]->area-test[i]->area,train[j]->perimeter-test[i]->perimeter,train[j]->compactness-test[i]->compactness,train[j]->length_of_kernel-test[i]->length_of_kernel,train[j]->width_of_kernel-test[i]->width_of_kernel,train[j]->asymmetry_coefficient-test[i]->asymmetry_coefficient,train[j]->length_of_kernel_groove-test[i]->length_of_kernel_groove);
          kon[j][0] = distace_of_test;
          kon[j][1] = j;
        }
        printf("%d\n",i);
        SortUpto_K(kon,k,210-210/r);

        assign[i] = FindMaxClass(kon,train,k,3);
        printf("%d\t%d\n",assign[i],test[i]->class);
        if(assign[i]==test[i]->class)
          ++true;
        }

        printf("%d\t%f\n" ,l ,true/(210.0/r));


    int k=9,p=2;
    float KNN[k];
    float distace_of_test;
    int assign[30];
    // for(i=0;i<30;i++)
    //   assign[i] = 0;
    for(i=0;i<30;i++){
      float kon[180][2];
      for (j=0;j<180;j++){
        distace_of_test=Minkowski_distance(p,train[j]->area-test[i]->area,train[j]->perimeter-test[i]->perimeter,train[j]->compactness-test[i]->compactness,train[j]->length_of_kernel-test[i]->length_of_kernel,train[j]->width_of_kernel-test[i]->width_of_kernel,train[j]->asymmetry_coefficient-test[i]->asymmetry_coefficient,train[j]->length_of_kernel_groove-test[i]->length_of_kernel_groove);

        // printf("%f\n",distace_of_test);
        kon[i][0] = distace_of_test;
        kon[i][1] = j;
      }
      SortUpto_K(kon,k,180);
      int k;
      for(k=0;k<9;k++)
      {
        printf("%f\t%f\n",kon[k][0],kon[k][1]);
      }
      final_class=mod(kon);
      if(test[i]->class==final_class)
        true++;

    }



    }

    //////        finding k and p values    ////////

    // int k=9,p=2;
    // float distace_of_test;
    // int assign[210/r];
    // int true = 0;
    // // for(i=0;i<30;i++)
    // //   assign[i] = 0;
    // for(i=0;i<210/r;i++){
    //   float kon[210-210/r][2];
    //   for (j=0;j<210-210/r;j++){
    //     distace_of_test=Minkowski_distance(p,train[j]->area-test[i]->area,train[j]->perimeter-test[i]->perimeter,train[j]->compactness-test[i]->compactness,train[j]->length_of_kernel-test[i]->length_of_kernel,train[j]->width_of_kernel-test[i]->width_of_kernel,train[j]->asymmetry_coefficient-test[i]->asymmetry_coefficient,train[j]->length_of_kernel_groove-test[i]->length_of_kernel_groove);
    //     kon[j][0] = distace_of_test;
    //     kon[j][1] = j;
    //   }
    //   // printf("\nBefore:\n");
    //   // for(k=0;k<9;k++)
    //   // {
    //   //   printf("%f\t%f\n",kon[k][0],kon[k][1]);
    //   // }
    //   // k = 9;
    //   SortUpto_K(kon,k,210-210/r);
    //   // printf("\nafter:\n");
    //   // int k;
    //   // for(k=0;k<9;k++)
    //   // {
    //   //   printf("%f\t%f\n",kon[k][0],kon[k][1]);
    //   // }
    //   assign[i] = FindMaxClass(kon,train,k,3);
    //   // printf("%d\t%d\n",assign[i],test[i]->class);
    //   if(assign[i]==test[i]->class)
    //     ++true;
    // }
    // printf("\n%f\n",true/(210.0/r));





    return 0;
}

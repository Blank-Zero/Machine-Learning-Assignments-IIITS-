#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define r 7     // defining r-fold
#define MAX 210   //Defining max input values

typedef struct set    // Created sturct for storing the dataset of each element
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


void WriteTestValues(SET *test[],int n)     // Function for writing a attribute values of a set
{
    int i;
    for(i=0;i<n;i++){
        printf("%f\t%f\t%d\n",test[i]->area,test[i]->perimeter,test[i]->class);
    }
}

void ReadAll(FILE *fptr,SET *data[],int max)        // Function to read all values from the file and store it in the 
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

float mod_f(float num)      // Function for modulus of a given number
{
    if(num<0)
        return num * (-1);
    return num;
}

// function for finding the minkowski distance
float Minkowski_distance(int p,float area,float perimeter,float compactness,float length_of_kernel,float width_of_kernel,float asymmetry_coefficient,float length_of_kernel_groove)     
{
  double distance;
  distance=mod_f(pow(area,p))+mod_f(pow(perimeter,p))+mod_f(pow(compactness,p))+mod_f(pow(length_of_kernel,p))+mod_f(pow(width_of_kernel,p))+mod_f(pow(asymmetry_coefficient,p))+mod_f(pow(length_of_kernel_groove,p));
  distance=mod_f(pow(distance,1.0/p));
  return distance;
}

// void Swap(float *a,float *b)
// {
//     *a = *a ^ *b;
//     *b = *a ^ *b;
//     *a = *a ^ *b;
//     return;
// }


void SortUpto_K(float kon[][2],int k,int max)       // Fucntion for findind the least values upto k in a given array
{
    int i,j;
    for(i=0;i<k;i++)
    {
        int min = i;

        for(j=i;j<max;j++)                  // Find the minimum value from the array
        {
            if(kon[min][0] > kon[j][0])
            {
                min = j;
            }
        }
        float temp = kon[min][0];           // Swaping the mininum values and the least indexes
        kon[min][0] = kon[i][0];
        kon[i][0] = temp;
        temp = kon[min][1];
        kon[min][1] = kon[i][1];
        kon[i][1] = temp;
    }
}

int FindMaxClass(float kon[][2],SET *train[],int k,int clscount)        // Function to find the class to be assigned
{
    int arrClassCount[clscount];
    int i;
    for(i=0;i<clscount;i++)                                         // Initiate the classcount value with zeros
      arrClassCount[i] = 0;
    for(i=0;i<k;i++)
    {
      ++arrClassCount[train[((int)kon[i][1])]->class - 1];          // Increament the class values from the kon array
    }
    int max = 0;
    for(i=1;i<clscount;i++)                                          // Find the class with maximum matches
    {
      if(arrClassCount[max] < arrClassCount[i])
        max = i;
    }
    return max+1;                                                   // Return the class with max value
}

float FindAccuracy(int k,int p,SET *test[],SET *train[]){           // Function to find Accuracy

  float distace_of_test;
  int assign[MAX/r];
  int true = 0;
  // for(i=0;i<30;i++)
  //   assign[i] = 0;
  int i,j;
  for(i=0;i<(MAX/r);i++){
    float kon[MAX-MAX/r][2];

    for (j=0;j<MAX-(MAX/r);j++){
      //printf("%d\n",test[1]->class);

      distace_of_test=Minkowski_distance(p,train[j]->area-test[i]->area,train[j]->perimeter-test[i]->perimeter,train[j]->compactness-test[i]->compactness,train[j]->length_of_kernel-test[i]->length_of_kernel,train[j]->width_of_kernel-test[i]->width_of_kernel,train[j]->asymmetry_coefficient-test[i]->asymmetry_coefficient,train[j]->length_of_kernel_groove-test[i]->length_of_kernel_groove);
      kon[j][0] = distace_of_test;
      kon[j][1] = j;
    }
    SortUpto_K(kon,k,MAX-MAX/r);

    assign[i] = FindMaxClass(kon,train,k,3);
    //printf("%d\t%d\n",assign[i],test[i]->class);
    if(assign[i]==test[i]->class)
      ++true;
    }

    return (true/(MAX*1.0/r))*100;
}


int main()
{
    int l,m;
    float final_accuracy=0;
    float accuracy[r];
    FILE *filePointer;                                       // File pointer to get the file and its data
    filePointer = fopen("SwapedSeeds.txt","r");

    if(filePointer == NULL)
    {
        printf("failed to open the file");
        return 0;
    }
    printf("Works fine\n");
    // read_values(filePointer);

    SET *data[MAX];                                         // Data set

    ReadAll(filePointer,data,MAX);                          // To get the data from filepointer

    fclose(filePointer);
    // WriteTestValues(data[5]);
    //int r=7;

    // SET *test;
    // test=data[0];
    // printf("%f\n",test->area );
    SET *test[MAX/r];                                        // Test set
    SET *train[MAX-(MAX/r)];                                 // Train set

    int k=11,p=4;
    printf("\nFor k=%d , p=%d and r=%d the accuracy is :\n\n",k,p,r);

    for(l=0;l<r;l++){

      for (m=MAX/r*l;m<(MAX/r)*(l+1);m++){
        test[m-((MAX/r)*l)]=data[m];
      }
      int limit=0;
      for (m=0;m<MAX;m++){
        if(m<(MAX/r)*l || m>=(MAX/r)*(l+1)){
          train[limit]=data[m];
          ++limit;
        }
      }
          //////        finding k and p values    ////////

      accuracy[l]= FindAccuracy(k,p,test,train);
      printf("%d\t%f%\n",l+1,accuracy[l]);

    }

    for(l=0;l<r;l++){
      final_accuracy=final_accuracy+accuracy[l];
    }
    printf("Final accuracy of the dataset = %f%\n",final_accuracy/(r*1.0));
    return 0;
}

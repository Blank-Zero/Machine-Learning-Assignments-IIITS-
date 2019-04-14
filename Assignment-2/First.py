import random

def GetFloat(data):
    li = []
    for i in data:
        li.append(float(i))
    return li

def Shuffler(data):
    li = list(range(0,len(data),1))
    for _ in range(1000):
        i,j = random.randint(0,len(data)-1) , random.randint(0,len(data)-1)
        li[i] , li[j] = li[j] , li[i]

    newdata = []
    for i in li:
        newdata.append(data[i])
    
    return newdata

def LineFunc(data,slope_m,constant_c):
    line = 0.0
    for i in range(len(slope_m)):
        line = line + slope_m[i] * data[i]
    return line + constant_c

def GradientDecent(TrainingSet,slope_m,constant_c):
    D_slope = [0.0,0.0,0.0,0.0,0.0,0.0]
    D_const = 0.0
    
    for data in TrainingSet:
        pred = LineFunc(data,slope_m,constant_c)
        for i in range(len(D_slope)):
            D_slope[i] = D_slope[i] + data[i] * (data[len(data)-1] - pred)
        D_const = D_const + data[len(data)-1] - pred

    D_const = (-1.0/len(TrainingSet))*D_const
    for i in range(len(D_slope)):
        D_slope[i] = (-1.0/len(TrainingSet))*D_slope[i]

    # print(D_slope)
    # print(D_const)
    return D_slope, D_const
    
def FindError(testset,slope,constant):
    error = 0
    for data in testset:
        error = error + (data[len(data)-1] - LineFunc(data,slope,constant))**2
        # print(error)
    error = error/(2.0*float(len(testset)))
    return error


if __name__ == "__main__":    
    dataset = []
    fileptr = open("Dataset-1.txt",'r')
    for line in fileptr:
        data = line.split()
        data = GetFloat(data)
        # print(data)
        dataset.append(data)
    fileptr.close()

    # print(dataset[5])

    dataset = Shuffler(dataset)

    # fileptr = open("testfile.txt","w")
    # for i in dataset:
    #     fileptr.write(str(i)+'\n')
    # fileptr.close()

    trainset = dataset[0:200]
    testset = dataset[200:len(dataset)]

    slope_m = [0.0,0.0,0.0,0.0,0.0,0.0]
    constant_c = 0
    learning_step = 0.02
    
    for _ in range(10000):
        D_slope, D_const = GradientDecent(trainset,slope_m,constant_c)
        for i in range(len(slope_m)):
            slope_m[i] = slope_m[i] - learning_step*D_slope[i]
        constant_c = constant_c - learning_step*D_const
    
    error = FindError(trainset,slope_m,constant_c)
    print("Training set error:{}".format(error))

    error = FindError(testset,slope_m,constant_c)
    print("Test set error:{}".format(error))

    print("Slope:{}".format(slope_m))
    print("constant:{}".format(constant_c))

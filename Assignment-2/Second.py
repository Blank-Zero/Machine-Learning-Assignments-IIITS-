

import random

def Shuffler(data):
    li = list(range(0,len(data),1))
    for _ in range(1000):
        i,j = random.randint(0,len(data)-1) , random.randint(0,len(data)-1)
        li[i] , li[j] = li[j] , li[i]

    newdata = []
    for i in li:
        newdata.append(data[i])
    
    return newdata

def LineFunc(data,slope,constant):
    line = 0
    for i in range(len(slope)):
        line += slope[i] *data[i]
    line += constant
    if line > 0:
        return 1
    else:
        return -1

def GradiantDecent(dataset, slope_m, constant_c):
    D_slope = [0.0,0.0,0.0,0.0]
    D_const = 0.0

    for data in dataset:
        pred = LineFunc(data,slope_m,constant_c)
        for i in range(len(slope_m)):
            D_slope[i] = D_slope[i] + data[i] * (data[len(data)-1] - pred)
        D_const = D_const + data[len(data)-1] - pred
    
    D_const = (-2.0/len(dataset))*D_const
    for i in range(len(slope_m)):
        D_slope[i] = (-2.0/len(dataset))*D_slope[i]

    return D_slope, D_const

def FindError(dataset, slope, constant):
    error = 0
    for data in dataset:
        # error = error + data[len(data)-1] - LineFunc(data,slope,constant)
        if data[len(data)-1] != LineFunc(data,slope,constant):
            error+=1
    return error


if __name__ == "__main__":
    dataset = []
    fileptr = open("Dataset-2.txt","r")
    for line in fileptr:
        data = line.split(",")
        newdata = []
        for i in range(4):
            newdata.append(float(data[i]))
        if data[4] == "Iris-virginica\n":
            newdata.append(1)
        else:
            newdata.append(-1)
        dataset.append(newdata)
    fileptr.close()

    # print(dataset)
    dataset = Shuffler(dataset)
    # print(dataset)

    trainset = dataset[0:70]
    testset = dataset[70:]

    slope_m = [0.0,0.0,0.0,0.0]
    constant_c = 0.0
    learning_step = 0.01

    for _ in range(10000):
        D_slope, D_const = GradiantDecent(trainset,slope_m,constant_c)
        for i in range(len(slope_m)):
            slope_m[i] = slope_m[i] - learning_step * D_slope[i]
        constant_c = constant_c - learning_step * D_const

    error = FindError(trainset,slope_m,constant_c)
    print("Training set error:{}".format(error))

    error = FindError(testset,slope_m,constant_c)
    print("Test set error:{}".format(error))

    print("Slope:{}".format(slope_m))
    print("constant:{}".format(constant_c))

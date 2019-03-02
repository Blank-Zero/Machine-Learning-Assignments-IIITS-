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

    
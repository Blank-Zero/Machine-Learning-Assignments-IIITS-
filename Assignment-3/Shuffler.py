import random

def getFloat(data):
    li = []
    for i in data:
        li.append(float(i))
    return li

def shuffuler(dataset):
    li = list(range(0,len(dataset),1))
    for _ in range(100000):
        i,j = random.randint(0,len(dataset)-1) , random.randint(0,len(dataset)-1)
        li[i],li[j] = li[j],li[i]

    newData = []
    for i in li:
        newData.append(dataset[i])

    return newData

if __name__ == '__main__':
    # initialize the dataset
    dataset = []

    # open the file and read the data
    fileptr = open("Colon_Cancer_CNN_Features.csv",'r')
    for line in fileptr:
        data = line.split(',')
        data = getFloat(data)
        # print(data)
        dataset.append(data)
    fileptr.close()

    # shuffle the data
    dataset = shuffuler(dataset)

    # open file to write the shuffled data
    fileptr = open("Shuffled_Data.csv",'w')
    for data in dataset:
        for i in range(0,len(data)-1):
            fileptr.write("{},".format(data[i]))
        fileptr.write("{}\n".format(data[len(data)-1]))
    
    fileptr.close()


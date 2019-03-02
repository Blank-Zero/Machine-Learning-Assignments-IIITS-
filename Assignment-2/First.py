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


dataset = []
fileptr = open("Dataset-1.txt",'r')
for line in fileptr:
    data = line.split()
    data = GetFloat(data)
    # print(data)
    dataset.append(data)
fileptr.close()

print(dataset[5])

dataset = Shuffler(dataset)

fileptr = open("testfile.txt","w")
for i in dataset:
    fileptr.write(str(i)+'\n')
fileptr.close()
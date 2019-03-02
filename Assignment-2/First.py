def GetFloat(data):
    li = []
    for i in data:
        li = float(i)
    return li

dataset = []
fileptr = open("Dataset-1.txt",'r')
for line in fileptr:
    data = line.split()
    data = GetFloat(data)
    # print(data)
    dataset.append(data)
fileptr.close()

# print(dataset)
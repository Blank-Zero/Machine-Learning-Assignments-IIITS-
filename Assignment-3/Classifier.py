
def getFloat(data):
    li = []
    for i in data:
        li.append(float(i))
    return li

if __name__ == "__main__":
    # initialize the dataset
    dataset = []

    # open the file and read the data
    fileptr = open("Colon_Cancer_CNN_Features.csv",'r')
    for line in fileptr:
        data = line.split(',')
        data = getFloat(data)
        dataset.append(data)
    fileptr.close()

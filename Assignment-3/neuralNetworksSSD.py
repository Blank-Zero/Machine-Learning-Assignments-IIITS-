def getFloat(data):
    li = []
    for i in data:
        li.append(float(i))
    return li

def createNetwork(intputSize,hiddenUnits,classCount):
    network = []
    hiddenLayer = [{'weights': [1 for i in range(intputSize + 1)]} for i in range(hiddenUnits)]
    network.append(hiddenLayer)
    outputLayer = [{'weights': [1 for i in range(hiddenUnits + 1)]} for i in range(classCount)]
    network.append(outputLayer)
    return network

def lineFunc(weights,inputs):
    result = weights[-1]
    for i in range(len(inputs)-1):
        result += weights[i] * inputs[i]
    # print(result)
    return result
    # return result/100.0

def sigmondFunc(weights,inputs):
    # print(1.0/(1.0+(2.71828**(-1.0*lineFunc(weights,inputs)))))
    return 1.0/(1.0+(2.71828**(-1.0*lineFunc(weights,inputs))))

def forwordPropagation(network,data):
    inputs = data[0:-1]
    for layer in network:
        outputs = []
        for neuron in layer:
            neuron['output'] = sigmondFunc(neuron['weights'], inputs)
            outputs.append(neuron['output'])
        inputs = outputs
    return inputs

def sigmondDervFunc(output):
    return output * (1-output)

def calculateErrors(network,target):
    for i in reversed(range(len(network))):
        layer = network[i]
        if i == len(network) - 1:
            for j in range(len(layer)):
                neuron = layer[j]
                neuron['delta'] = (target[j] - neuron['output']) * sigmondDervFunc(neuron['output'])
                        
        else:
            for j in range(len(layer)):
                neuron = layer[j]
                error = 0.0
                for k in range(len(network[i+1])):
                    nextNeuron = network[i+1][k]
                    error += nextNeuron['delta'] * neuron['weights'][k] * sigmondDervFunc(neuron['output'])
                neuron['delta'] = error

def updateWeights(network,data,learningRate):
    inputs = data[0:-1]
    for i in range(len(network)):
        if i != 0:
            inputs = [neuron['output'] for neuron in network[i-1]]
        for neuron in network[i]:
            for j in range(len(inputs)):
                neuron['weights'][j] += learningRate * neuron['delta'] * inputs[j]
            neuron['weights'][-1] += learningRate * neuron['delta']


def trainNetwork(network,trainSet,learningRate,titrations,classCount):
    for _ in range(titrations):
        sumError = 0
        for data in trainSet:
            outputs = forwordPropagation(network,data)
            target = [0 for i in range(classCount)]
            target[int(data[-1])-1] = 1
            sumError += sum([(target[i]-outputs[i])**2 for i in range(len(target))])
            calculateErrors(network,target)
            updateWeights(network,data,learningRate)
        print("error:{}".format(sumError))

def calculateAccuracy(network,dataSet):
    error = 0
    for data in dataSet:
        outputs = forwordPropagation(network,data)
        if (int(data[-1]-1) != outputs.index(max(outputs))):
            error += 1
    print("error count:{} and len of dataset:{}".format(error,len(dataSet)))
    return error/(1.0*len(dataSet))


def PrintNetwork(network):
    for layer in network:
        print('\n\n')
        for neuron in layer:
            print(neuron)
            print('\n\n')

if __name__ == "__main__":
    # initialize the dataset
    dataset = []

    # open the file and read the data
    fileptr = open("Shuffled_Data.csv",'r')
    for line in fileptr:
        data = line.split(',')
        data = getFloat(data)
        dataset.append(data)
    fileptr.close()

    # initialize parameter
    attributeCount = len(dataset[0])-1
    hiddenUnits = 5
    classCount = 4
    trainSet = dataset[0:5218]
    testSet = dataset[5218:]
    learningRate = 0.001

    for hiddenUnits in range(5,16):
        print("\n\nFor hiddenunits:{}".format(hiddenUnits))
        # create network
        network = createNetwork(attributeCount,hiddenUnits,classCount)

        # train the network with trainset
        trainNetwork(network,trainSet,learningRate,20,4)
        print("\n\nerror with train set: {}".format(calculateAccuracy(network,trainSet)))
        print("\n\nerror with test set: {}\n\n\n".format(calculateAccuracy(network,testSet)))
        # PrintNetwork(network)

import random

def getFloat(data):
    li = []
    for i in data:
        li.append(float(i))
    return li

def initializeNetwork(inputSize,hiddenUnitSize,outputs):
    network = list()
    hidden_layer = [{'weights':[random.randint(1,1) for i in range(inputSize + 1)]} for i in range(hiddenUnitSize)]
    network.append(hidden_layer)
    output_layer = [{'weights':[random.randint(1,1) for i in range(hiddenUnitSize + 1)]} for i in range(outputs)]
    network.append(output_layer)
    return network

def lineFunc(weights,inputs):
    result = weights[-1]
    for i in range(len(inputs)-1):
        result += weights[i] * inputs[i]
    return result

def sigmondFunc(weights,inputs):
    return 1.0/(1+(2.71828**(-1.0*lineFunc(weights,inputs))))

def sigmondFuncDerv(output):
    return output * (1-output)

def forwordPropagate(network,data):
    inputs = data
    for layer in network:
        outputs = []
        for neuron in layer:
            neuron['output'] = sigmondFunc(neuron['weights'], inputs)
            outputs.append(neuron['output'])
        inputs = outputs
    return inputs

def backwordPropagateError(network,expected):
    for i in reversed(range(len(network))):
        layer = network[i]
        errors = list()
        if i != len(network)-1:
            for j in range(len(layer)):
                error = 0.0
                for neuron in network[i + 1]:
                    error += (neuron['weights'][j] * neuron['delta'])
                errors.append(error)
        else:
            for j in range(len(layer)):
                neuron = layer[j]
                errors.append(expected[j] - neuron['output'])
        for j in range(len(layer)):
            neuron = layer[j]
            neuron['delta'] = errors[j] * sigmondFuncDerv(neuron['output'])


def upadateWeights(network,data,learningRate):
    for i in range(len(network)):
        inputs = data[0:-1]
        if i != 0:
            inputs = [neuron['output'] for neuron in network[i-1]]
        for neuron in network[i]:
            for j in range(len(inputs)):
                neuron['weights'][j] += learningRate * neuron['delta'] * inputs[j]
            neuron['weights'][-1] += learningRate * neuron['delta']

def trainNetwork(network, trainSet, learningRate, n_epoch, classCount):
    for epoch in range(n_epoch):
        sumError = 0
        for data in trainSet:
            outputs = forwordPropagate(network,data[0:-1])
            expected = [0 for i in range(classCount)]
            expected[int(data[-1])-1] = 1
            sumError += sum([(expected[i]-outputs[i])**2 for i in range(len(expected))])
            backwordPropagateError(network,expected)
            upadateWeights(network, data, learningRate)
        print('trail:{} learningRate:{} error:{}'.format(epoch,learningRate,sumError))


def calculateAccuracy(network,dataSet):
    error = 0
    for data in dataSet:
        outputs = forwordPropagate(network,data)
        if (int(data[-1]-1) != outputs.index(max(outputs))):
            error += 1
    return error/(1.0*len(dataSet))


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

    # initailize parameters
    attributeCount = len(dataset[0])
    hiddenUnitCount = 5
    classCount = 4
    trainSet = dataset[0:5218]
    testSet = dataset[5218:len(dataset)]
    learningRate = 0.001
    
    network = initializeNetwork(attributeCount-1,hiddenUnitCount,classCount)

    # print(network[0])
    trainNetwork(network,trainSet,learningRate,20,4)
    print("\n\n\ntrainError:{}\n\n\n".format(calculateAccuracy(network,trainSet)))
    print("\n\n\nTestError:{}\n\n\n".format(calculateAccuracy(network,testSet)))
    # for layer in network:
    #     print(layer)
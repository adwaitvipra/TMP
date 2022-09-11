
graph = { '1' : {'2':5,'4':6} , '2':{'3': 4,'6': 2}, '3':{'5':8}, '4':{'6':1,'7':4}, '5' : {'6':4,'7':8}, '6':{'7':2}, '7':{'1': 5} }

def goalTest(currNode, goal):
    if currNode == goal:
        return True
    return False

def getCost(src, dest, graph):
    if src == dest:
        return 0
    return graph[src[dest]] if graph[src[dest]] else -1

def getSucc(node, graph):
    if node in graph:
        return graph[node]
    return -1


def getMin(queue):
    minCost = list(queue.keys())[0]

    for x in queue:
        if queue[x] < queue[minCost]:
            minCost = x
    return x
def getPathCost(closedList, graph):
    cost = 0
    for i in range(len(closedList)-1):
        cost += getCost(closedList[i], closedList[i+1], graph)
    return cost

def UCS(start, goal, graph):
    closedList = []
    priorityQueue ={}

    currNode = start
    closedList.append(start)
    succ = getSucc(start, graph)
    for i in succ:
        priorityQueue[i] = getCost(currNode, currNode, graph)
 
    while len(priorityQueue):        
        currNode = priorityQueue.pop(getMin(priorityQueue))
        closedList.append(currNode)
        succ = getSucc(currNode, graph)
        
        if goalTest(currNode, goal):
            return [start, goal, closedList, getPathCost(closedList)]
        
        for i in succ:
            if i in closedList:
                continue
            if i in priorityQueue:
                priorityQueue[i] = min(getCost(currNode, i), priorityQueue[i])
            else:
                priotityQueue[i] = getCost(currNode, i)

print(UCS('1', '7', graph))

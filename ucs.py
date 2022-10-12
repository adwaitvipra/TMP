# class to store the node
class Node:
    def __init__(self, state, parent=0, pathCost=0):
        self.state = state
        self.parent = parent
        self.pathCost = pathCost
# graph or search space
space = { 
        'A': [(5, 'B'), (7, 'C'),(3, 'D')],
        'B': [(2, 'E'), (10, 'F')],
        'C': [(6, 'G')],
        'D': [(11, 'H')],
        'E': [(9, 'H')],
        'F': [(4, 'H')],
        'G': [(6, 'H')],
        'H': []
        }

def printTraversal(openList, N, closedList, goalTest, successor):

    print("\nOpen List : ", openList, "\nN : ", N, "\nClosed List : ", closedList, "\nGoal Test : ", goalTest, "\nSucc(N) : ", successor)
    
    return

def goalTest(currNode, goalState):
    if(currNode.state == goalState):
        return True
    return False

def getSucc(space, currNode):
    return space[currNode.state]

def getSolution(currNode):
    soln = [currNode.state]
    while(currNode.parent != 0):
        soln.insert(0,currNode.parent.state)
        currNode = currNode.parent
    return soln

def getPath(currNode, solution):
    while(currNode.parent != 0):
        getPath(currNode.parent)
def getNodeWithSameState(openList, currNode):
    for obj in openList:
        if obj.state == currNode.state:
            return obj
def uniformCostSearch(space, startState, goalState):
    currNode = Node(startState,0,0)
    openList = [currNode]
    closedList = []
    while(len(openList)):

        currNode = openList.pop(0)
        if(goalTest(currNode, goalState)):
            return [startState, goalState, currNode.pathCost, getSolution(currNode)]

        closedList.append(currNode.state)
        
        children = getSucc(space, currNode)
        printTraversal(openList, currNode, closedList, goalTest(currNode, goalState), children) 
        for i, j in children:
            child = Node(j, currNode, currNode.pathCost + i)
            if(child.state not in closedList or child.state not in [ obj.state for obj in openList]):
                openList.append(child)
            else if (
                        child.state in [obj.state for obj in openList] and
                        (tmp = getNodeWithSameState(space, child)).pathCost > child.pathCost
                    ):
                tmp = child
        openList.sort(key = lambda x : x.pathCost, reverse = True)

print(uniformCostSearch(space, 'A', 'H'))

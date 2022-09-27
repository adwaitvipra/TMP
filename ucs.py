# class to store the node
class Node:
    def __init__(self, state, parent, pathCost):
        self.state = state
        self.parent = parent
        self.pathCost = pathCost

# graph or search space
space = { 
        'A': [(5, 'B'), (7, 'C'),(3, 'D')],
        'B': [(5, 'A'), (2, 'E'), (10, 'F')],
        'C': [(7, 'A'), (6, 'G')],
        'D': [(3, 'A'), (11, 'H')],
        'E': [(2, 'B'), (9, 'H')],
        'F': [(10, 'B'), (4, 'H')],
        'G': [(1, 'C'), (6, 'H')],
        'H': [(11, 'D'), (9, 'E'), (4, 'F'), (6, 'G')]
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
    if(!currNode)
        return []
    soln = []
    while(currNode.parent != 0):
        soln.insert(0,parent)
        currNode = parent
    return soln
    
def uniformCostSearch(space, startState, goalState):
    currNode = Node(startState,0,0)
    openList = [currNode]
    openListCostState= [(currNode.pathCost, currNode.state)]
    closedList = []
    while(!len(openList)):

        currNode = openList.pop(0)
        
        if(goalTest(currNode, goalState)):
            return currNode
        
        closedList.append(currNode.state)
        
        children = getSucc(state, currNode)
        for i, j in children:
            child = Node(j, currNode, currNode.pathCost + i)
            if (child.state not in closedList or child.state not in [j in for i, j in openListCostState]):
                openList.append(child)
                openListCostState.append((child.pathCost, child.state))
            else if (child.state in [ j for i, j in openListCostState] and 

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
# g(n) : gives the cost of path from root to current node n
g = {}
def printTraversal(openList, N, closedList, goalTest, successor):

    print("\nOpen List : ", openList, "\nN : ", N, "\nClosed List : ", closedList, "\nGoal Test : ", goalTest, "\nSucc(N) : ", successor)
    
    return

def goalTest(currNode, goal):
    if(currNode == goal):
        return True
    return False

def getSucc(space, currNode):
    return space[currNode]


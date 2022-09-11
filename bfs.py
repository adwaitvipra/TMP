# breadth first search
graph = {'A':['B','C'],'B':['A','C','D','E'],'C':['A','B','D'], 'D':['B', 'C','F', 'E'], 'E':['B','D','F'], 'F':['D','E']}

def printTraversal(openList, N, closedList, goalTest, successor):
    print("\nOpen List : ", openList, "\nN : ", N, "\nClosed List : ", closedList, "\nGoal Test : ", goalTest, "\nSucc(N) : ", successor)
    return


def succ(currNode, graph):
    if currNode in graph:
        return graph[currNode]
    return []

def bfs(graph, start, goal):
    openList=[]
    closedList=[]
    openList.insert(0, start)
    while(len(openList)!=0):
        x = openList.pop(0)
        if(x not in closedList):
            closedList.append(x)
        else:
            continue
        printTraversal(openList, x, closedList, x == goal, succ(x, graph))        
        if (x == goal):
            return [closedList, goal]
        tmp = graph[x]
        for i in tmp:
            if((i not in closedList) and (i not in openList)):
                openList.append(i)
            else:
                continue
        
    return [closedList, -1]

print("\n\t\tAnswer = ",bfs(graph, "A","F"))
print("\n\t\tAnswer = ",bfs(graph, "B", "K"))

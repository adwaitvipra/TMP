graph = { '1' : ['2', '4'] , '2':['1', '3', '6'], '3':['2', '5'], '4':['1', '6', '7'], '5' : ['3', '6', '7'], '6' : ['2', '4', '5', '7'], '7':['4', '5', '6']}

def goalTest(currNode, goal):
    if currNode == goal:
        return True
    return False

def DFS(currNode, goal, graph, maxDepth):
    print("Current Node = ", currNode)

    if goalTest(currNode, goal):
        return True

    if maxDepth <= 0:
        return False

    for node in graph[currNode]:
        if DFS(node, goal, graph, maxDepth - 1):
            return True
    return False

def IDDFS(currNode, goal, graph, maxDepth):
    for depth in range(maxDepth):
        if DFS(currNode, goal, graph, depth):
            return True
    return False
start = '1'
goal = '7'
if IDDFS(start, goal, graph, 4):
    print("Path exists from %s to %s"%(start, goal))
else:
    print("Path does not exists from %s to %s"%(start, goal))

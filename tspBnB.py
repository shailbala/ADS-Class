from SSTree import SSTree, Node
import copy, timeit

Inf = 99999
lInf = 99000

def reduceRow(A, r, c):
    '''
    Test Run:
    A = [[1,2,3], [3,4,5], [5,6,9]]
    reduceRow(A, 3, 3)
    ---
    [0, 1, 2]
    [0, 1, 2]
    [0, 1, 4]
    Cost = 9
    '''
    ## total cost for row reduction
    cost = 0
    for row in range(r):
        ## find minimum in each row
        if min(A[row]) >= lInf:
            smallest=0
        else:
            smallest = min(A[row])
        cost = cost + smallest
        ## subtract it from each element
        for i in range(c):
            A[row][i] = A[row][i] - smallest

        #print(A[row])
    return cost

def reduceCol(A, r, c):
    '''
    Test Run:
    A = [[1,2,3], [3,4,5], [5,6,9]]
    reduceCol(A, 3, 3)
    ---
    [0, 0, 0]
    [2, 2, 2]
    [4, 4, 6]
    Cost = 6
    '''
    ## total cost for column reduction
    cost = 0
    for col in range(c):
        smallest = A[0][col]
        ## find minimum in each column
        for i in range(r):
            if A[i][col] < smallest:
                smallest = A[i][col]
        #print("smallest found for this col: ", smallest)
        if smallest >= lInf:
            smallest = 0
        cost = cost + smallest
        ## subtract minimum from the column elements
        for i in range(r):
            A[i][col] = A[i][col] - smallest
    ## print
    ##for i in range(r):
    ##    print(A[i])
    return cost

def makeInf(A, nList):
    '''
    takes square matrix A and list of nodes nList
    makes A[row] = Inf and A[col] = Inf for all middle nodes
    For first node, makes A[row] = Inf
    For last node, makes A[col = Inf
    Also, makes all intermediate relations infinity
    
    A = 5x5 matrix, nList = [0, 4, 3]
    Rows to make Inf: A[0] (first), A[4] (middle)
    Cols to make Inf: A[4] (middle), A[3] (last)
    Intermediate relations to make Inf:
    A[0][4], A[0][3], A[4][0], A[4][3], A[3][0], A[3][4]
    '''
    global Inf
    ## rows only
    ## except last node
    for i in nList[:len(nList)-1]:
        for j in range(len(A)):
            A[i][j] = Inf

    ## columns only, except first node
    for j in nList[1:]:
        for i in range(len(A)):
            A[i][j] = Inf

    ## all other relations
    for i in nList:
        for j in nList:
            A[i][j] = Inf
            A[j][i] = Inf
    

    #return A

def reduceMatrix(A, n=-1):
    if n==-1:
        n = len(A)
    return reduceRow(A, n, n) + reduceCol(A, n, n)

def getRestNodes(original, visited):
    '''
    original = list of all vertices
    visited = list of visited vertices
    return all those vertices that are in original but not in visited
    '''
    path = original[:]
    for each in visited:
        path.remove(each)
    return path

def tsp(g, start=0):
    global Inf
    ## print graph
    ##print(g)

    ## empty state space tree
    n = len(g)
    vertexList = [i for i in range(n)]
    matrix = copy.deepcopy(g)
    tree = SSTree(n)
    upper = Inf
    ## priority queue for nodes
    pq = []
    path = []
    final_path = []

    ## make root node
    costRootReduction = reduceMatrix(g)
    root = Node(start, costRootReduction, g)
##    print("Root reduced matrix: ")
##    for each2 in g:
##      print(each2)
##    print("Cost of reduction: ", costRootReduction)

    costMatrix = copy.deepcopy(g)
    #print(costMatrix)
    
    ## insert into tree and get label
    label = tree.setRoot(root)
    #print("Label for root: ", label)
    ## insert into priority queue
    pq.append((root.cost, root.label))
    #upper = root.cost
    if root.cost >= lInf:
        print("No solution!")
        return
    ## add start vertex to the path, final answeer
    path.append(start)

    ## expand first node, get unexpanded nodes first
    #nextNodes = tree.getUnexpandedNodes()
    nextNodes = getRestNodes(vertexList, tree.getPath(label))

    while(len(pq)!=0):
        pq.sort()
        ## get node of least cost
        #print(pq)
        [cost, label] = pq.pop(0)
        z = tree.getNode(label)
        print("\n**********Next node in queue: ")
        print(z)
        #print("cost of popped node: ", cost)
        #print("Popped node: ", label)
        if cost > upper:
            print(":::::::::::::::::Node Killed!:::::::::::::::::")
            tree.killNode(tree.getNode(label))
            continue
        root = tree.getNode(label)
        #print("\n\nRoot popped from queue: ", root)
        ## expand the node with least cost

        #tree.expand(root.vertex)
        
        nextNodes = getRestNodes(vertexList, tree.getPath(root.label))
        #print("NextNodes: ", nextNodes)
        matrixParent = copy.deepcopy(root.matrix)

        for each in nextNodes:
            ## reduction cost
            #print("child node: ", each)
            p = tree.getPath(root.label)
            #print("Path returned from tree: ", p)
            p.append(each)
            #print("Path for this node: ", p)
            
            matrixCurr = copy.deepcopy(matrixParent)
            makeInf(matrixCurr, p)
            #print("martixCurr after making Inf: ", matrixCurr)
            #print("root vertex:", root.vertex)
            cost = reduceMatrix(matrixCurr)
##            print("\nReduced Matrix")
##            for each2 in matrixCurr:
##                print(each2)
            #print("cost of reduction: ", cost)
            cost = cost  + costMatrix[root.vertex][each] + root.cost
            #print("root.vertex:", root.vertex)
            #print("each: ", each)
            #print("Cost Matrix:", costMatrix)
            #print("cost of reduction: ", cost)
            if cost < upper:
                #print("cost < upper ")
                ## add this node to tree
                ## node(vertex, cost, matrix, parent, level)
                node = Node(each, cost, matrixCurr, root.label, root.level+1)
                #print(node)

                if root.level==(n-1):
                    upper = cost
                    print("******************\nLeaf node reached\n", node)
                    print("******************Upper updated to: ", upper)
                    #print("\n\tLeaf's parent node reached!\n\tUpdating Upper...")
                    final_path = tree.getPath(root.label)
                    final_path.extend(getRestNodes(vertexList, tree.getPath(root.label)))
                    #print("Final path as found: ", final_path)
                    continue
                tree.addNode(root.label, node)
                pq.append((cost, node.label))

    ## append the starting node in the end
    final_path.append(final_path[0])
    
    ## print cost
    cost = 0
    for i in range(n):
        cost = cost + matrix[final_path[i]][final_path[i+1]]
    for i in range(len(final_path)):
        final_path[i] = final_path[i] + 1
    return final_path, cost

## main()
n = 5
g1 = [[Inf, 20, 30, 10, 11],
     [15, Inf, 16, 4, 2],
     [3, 5, Inf, 2, 4],
     [19, 6, 18, Inf, 3],
     [16, 4, 7, 16, Inf]]
g2 = [[Inf, 10, 15, 20], 
        [10, Inf, 35, 25], 
        [15, 35, Inf, 30], 
        [20, 25, 30, Inf]]

####################################
g1 = [[Inf, 10, 12, 30],
      [24, Inf, 6, 12],
      [22, 11, Inf, 4],
      [3, 7, 10, Inf]]

start = timeit.default_timer()

print("Final solution to TSP: ")
path, cost = tsp(g1)

print("Path: "+str(path))
print("Total Cost: "+str(cost))

stop = timeit.default_timer()
print('Time: ', stop - start)

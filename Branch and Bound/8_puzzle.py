from SSTree import SSTree, Node
import math, timeit

N = 8

class Node:
    def __init__(self, cost, matrix, dist = 0, path=-1, level=1):
        self.cost = cost
        self.dist = dist
        self.matrix = matrix
        if path == -1:
            ## root node
            self.path = [0]
        else:
            self.path = path[:]
        self.level = level
        self.label = -1
        ## status: 2=Expanded, 1=Live, 0=Killed
        self.status = 1

    def setLabel(self, label):
        self.label = label
        self.path.append(self.label)

    def __str__(self):
        n = int(math.sqrt(len(self.matrix)))
        #print("n: ", n)
        s = "\n" +"Level: "+str(self.level)+", Moves: "+str(self.dist)
        ## print matrix
        for i in range(n):
            s = s+"\n"+str(self.matrix[n*i:n*i+n])
        return s

    def __eq__(self, other):
        return self.matrix == other.matrix

    def __lt__(self, other):
        return self.cost < other.cost

def newNode(currNode, move, nodeList):
    ## generates a new node based on given move from current node curr
    ## and compares if it already exists in nodeList
    N = int(math.sqrt(len(currNode.matrix)))
    c = list(currNode.matrix)   ## make a copy
    i = c.index(0)   ## position of empty tile
    if move == "U" and i>2:
        ## move up
        c[i], c[i-N] = c[i-N], c[i]
    elif move == "D" and i<(N*(N-1)):
        ## move down
        c[i], c[i+N] = c[i+N], c[i]
    elif move == "R" and i%N != (N-1):
        ## move right
        c[i], c[i+1] = c[i+1], c[i]
    elif move == "L" and i%N != 0:
        ## move left
        c[i], c[i-1] = c[i-1], c[i]
    n = Node(-1, c, currNode.dist+1, currNode.path, currNode.level+1)
    n.setLabel(nodeList[-1].label+1)
    if not n in nodeList:
        nodeList.append(n)
        return n
    return 0

def calculateCost(curr, final):
    global N
    count = 0
    for i in range(N):
        count = count + abs(curr.index(i) - final.index(i))%int(math.sqrt(N+1))
    return count

def printPath(node, tree):
    print("Printing final solution:")
    for i in node.path:
        ## each label in i
        ## find the label in i, print that node
        for each in tree:
            if each.label == i:
                print(each)

def n_puzzle(initial, final):
    global N

    ## for priority queue
    pq = []
    ## empty state space tree
    tree = []
    moves = ["U", "D", "R", "L"]
    ##find N (for 8 puzzle, N=8)
    N = len(initial)-1

    ##print("beginning, finding cost between initial and final")
    cost = calculateCost(initial, final)
    root = Node(cost, initial)
    root.setLabel(1)

    ## insert into priority queue
    pq.append(root)
    tree.append(root)
    ## set root as expanded
    root.status = 2

    if initial == final:
        return 0

    while(len(pq)!=0):
        pq.sort()
        ## get node of least cost
        #print(pq)
        node = pq.pop(0)
        #print("Popped node: ", node)
        node.status = 2
        ## reached final node?
        if node.cost == 0:
            #print(node)
            printPath(node, tree)
            return node.dist
        
        ## expand node for all possible moves
        for move in moves:
            child = newNode(node, move, tree)
            ## if it is not a valid move, new node will not be created
            ## check if node creation was successful
            if child:
                ##print("Child created, finding cost for child")
                child.cost = calculateCost(child.matrix, final)
                ## add to priority queue
                pq.append(child)
        if len(tree) > 1000:
            print("No solution, max limit reached!")
            return -1

## main()
n = 5
initial = [1, 2, 3, 5, 6, 0, 7, 8, 4]
final = [1, 2, 3, 5, 8, 6, 0, 7, 4]

#initial = [1, 2, 3, 8, 0, 4, 7, 6, 5]
#final = [2, 8, 1, 0, 4, 3, 7, 6, 5]

#initial = [1, 2, 3, 0, 4, 6, 7, 5, 8]
#final = [1, 2, 3, 4, 5, 6, 0, 7, 8]

initial = [1, 3, 4, 15, 2, 0, 5, 12, 7, 6, 11, 14, 8, 9, 10, 13]
final = [1, 3, 4, 15, 2, 0, 5, 12, 7, 6, 11, 14, 8, 9, 13, 10]
start = timeit.default_timer()
n_puzzle(initial, final)
stop = timeit.default_timer()
print('Time: ', stop - start)

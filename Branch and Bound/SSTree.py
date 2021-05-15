class Node:
    def __init__(self, vertex, cost, matrix, parentLabel=-1, level=1):
        self.vertex = vertex
        self.cost = cost
        self.matrix = matrix
        self.parent = parentLabel
        self.level = level
        self.label = -1

    def setLabel(self, label):
        self.label = label

    def __str__(self):
        s = "Node: "+str(self.vertex+1)+", Level: "+str(self.level)+", Cost: "+str(self.cost)
        s = s + "\nCost = c(parent, this) + r + r^"
        s = s+"\nMatrix: "
        for each in self.matrix:
            s = s+ "\n["
            for e in each:
                if e > 99000:
                    s = s + "Inf "
                else:
                    s = s + str(e) + " "
            s = s + "]"
        return s

#class 

class SSTree:
    def __init__(self, nodes=0) :
        ### nodes = number of nodes
        ### nodes start from 0 to nodes-1
        self.nodes = nodes
        # Store the adjacency list as a dictionary
        # {1 : [Node, Node, Node],
        # label : [Node, Node]}
        self.adjList = {}
        ## update it with a Node object
        self.root = -1
        self.lastLabel = 0
        ## initialize dict with 2 items
        ## {0:list of all unexpanded nodes (vertex number, not label),
        ## 1: list of all expanded nodes}
        ##self.expanded = dict({0:[i for i in range(nodes)], 1:[]})
        ##print("Initializing tree...")
        ##print("Expanded nodes: ", self.expanded[1])
        ##print("Unexpanded nodes: ", self.expanded[0])

    # Directed edges only
    ## src is node label, dstNode is Node object
    def addNode(self, src, dstNode) :
        ## no edge from node src
        if src not in self.adjList :
            self.adjList[src] = []
        #print("sssssssss=", self.lastLabel)
        dstNode.setLabel(self.lastLabel+1)
        #print("dstNode ddd=", dstNode.label)
        self.lastLabel = self.lastLabel+1
        #print("\n\nAdding node: ", dstNode)
        self.adjList[src].append(dstNode)
        #print(self.adjList)
    
    ## for printing
    def __str__(self) :
        for item in self.adjList.items() :
            print(item)

##    ## mark visited
##    def expand(self, node):
##        self.expanded[1].append(node)
##        self.expanded[0].remove(node)
##
##    ##
##    def getUnexpandedNodes(self):
##        return self.expanded[0]

    ## node is Node object
    def setRoot(self, node):
        self.root = node
        node.setLabel(1)
        #print("Inside setRoot, node is: ", node)
        self.adjList[1] = []
        self.lastLabel = 1
        ## label for root node is 1, return label
        return 1

    def setRootCost(self, cost):
        self.root.cost = cost

    def minCostNode(self, parent):
        t = self.adjList[parent]

    def getNode(self, label):
        if label == 1:
            return self.root
        for item in self.adjList.values():
            #print("Tree :", self.adjList.values())
            for each in item:
                #print("ttttttttttt=",each.label)
                if each.label == label:
                    #print("rrrrrrrrrrrrrrr=",each.label)
                    return each
            
    def getPath(self, label):
        '''returns path from root to this node as a list'''
        l = []
        #print("Inside getPath(), label: ", label)
        ## find node with given label
        if label == 1:
            ## root node
            #print("returning: ", [self.root.vertex])
            return [self.root.vertex]
        
        node = self.getNode(label)
        
        while(node.label!=self.root.label):
            l.append(node.vertex)
            label = node.parent
            node = self.getNode(label)
        l.append(self.root.vertex)
        #print("returning: ", l)
        l.reverse()
        return l

    def killNode(self, node):
        self.adjList.pop(node.label, None)
        try:
            self.adjList[node.parent].remove(node)
        except:
            pass
    

import timeit

class Graph:
    def __init__(self, v = 0):
        self.v = v
        self.e = []
        self.adjMat = []
        ## populate adj Matrix
        for i in range(v):
            self.adjMat.append([])
            for j in range(v):
                ## very high value ~infinity, no edge
                self.adjMat[i].append(10000)

    def addEdges(self, u, v, weight):
        if u >= self.v or v >= self.v:
            ## vertex not present
            return
        elif u != v:
            self.adjMat[u][v] = weight
            self.adjMat[v][u] = weight
            self.e.append((weight, u, v))

    def addVertices(self, n):
        for i in range(n):
            self.adjMat.append([])
            for j in range(self.v, self.v+n):
                self.adjMat[i].append(10000)

    def getVertexSet(self):
        v = []
        for i in range(self.v):
            v.append(i)
        return v

    def getVertexSize(self):
        return self.v
        
##    def getEdges(self):
##        return self.e
        
    def getEdges(self):
        #print("getEdges begins")
        e = []
        for i in range(self.v):
            for j in range(self.v):
                weight = self.adjMat[i][j]
                #print("weight: ", weight)
                ## if not already taken
                if not(((weight, i, j) in e) or (((weight, j, i)  in e))) and i!=j and weight< 10000:
                    e.append((weight, i, j))
                    #print("e: ",e)
        #print("returns: ", e)
        return e

def partition(a, p, r, index = 0):
    x = a[r][index]
    i = p-1
    for j in range(p, r):
        if a[j][index] < x:
            i = i+1
            a[i], a[j] = a[j], a[i]
    a[i+1], a[r] = a[r], a[i+1]
    return i+1

def quicksort(A, p, r, index=0):
    if p<r:
        q = partition(A, p, r, index)
        quicksort(A, p, q-1, index)
        quicksort(A, q+1, r, index)

class UnionFind:
    def __init__(self,val,parent):
        self.val = val
        self.p = parent

    def changeParent(self,parent):
        self.p = parent

    def getParent(self):
        return self.p

class ArrayUnionFind:
    """Holds the three "arrays" for union find"""
    def __init__(self, S):
        self.parent = {}
        for s in range(S):
            ## map vertes i with i, in the beginning, in its own set
            self.parent[s] = s
        ## size of each set is 1, self element
        self.size = dict((s,1) for s in range(S)) # size[s] = size of set s
        ## items for each set is self element
        self.items = dict((s,[s]) for s in range(S)) # item[s] = list of items in set s
                                
    def make_union_find(S):
        """Create a union-find data structure"""
        return ArrayUnionFind(S)

    
                
def find(UF, s):
    """Return the id for the group containing s"""
    #print("UF=",UF.parent)
    #print("s=", s)
    return UF.parent[s]

def union(UF, a, b):
    """Union the two sets a and b"""
    if not (a in UF.items and b in UF.items):
        return
    
    # make a be the smaller set
    if UF.size[a] > UF.size[b]:
        a,b = b,a
    
    # put the items in a into the larger set b
    for s in UF.items[a]:
        UF.parent[s] = b
        UF.items[b].append(s)
    # the new size of b is increased by the size of a
    UF.size[b] += UF.size[a]
    # remove the set a (to save memory)
    del UF.size[a]
    del UF.items[a]


def kruskal_mst(G):
    """Return a minimum spanning tree using kruskal's algorithm"""
    
    edges = G.getEdges()
    #print("Edges list", edges)
    
    #print(len(edges))
    num = len(edges)

    ## sort according to weight
    quicksort(edges, 0, num-1)
    #print("Sorted Edges list", edges)
    
    # for edges in increasing weight
    mst = [] # list of edges in the mst

    #UFarr = ArrayUnionFind()
    t = G.getVertexSize()
    #print("t: ", t)
    UFarr = ArrayUnionFind(t)
    #union-find data structure
    v = G.getVertexSize()
    
    # for edges in increasing weight
    ## only run for v-1 iterations
    for i in range(v-1):
        ## take first element from sorted edges
        e = edges.pop(0)
        #print("inside for, e: ", e)
        
        ## two sets for two end vertices
        setu = find(UFarr, e[1])
        setv = find(UFarr, e[2])
        
        # if u,v are in different components
        ## adding it doesn't cause a cycle
        if setu != setv:
            ## add to mst
            mst.append((e[1], e[2], e[0]))
            union(UFarr, setu, setv)
            
    l = 0
    print("printing mst:")
    for u, v, d in mst:
        print("u " + str(u) + " v " + str(v) + " d " + str(d))
        l = l+d
    
    print("Total length of MST: ", l)
    return mst


g = Graph(5)
##g.addEdges(u, v, weight)
g.addEdges(0, 2, 3)
g.addEdges(2, 3, 5)
g.addEdges(4, 2, 10)
g.addEdges(1, 0, 45)
g.addEdges(1, 4, 4)
g.addEdges(2, 1, 3)

start = timeit.default_timer()

kruskal_mst(g)


stop = timeit.default_timer()

print('Time: ', stop - start)

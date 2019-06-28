# Importing
from random import randint

# Functions
# --- Generate a Random Letter
def gen():
	return chr(randint(65,90))
def FIND(x):
	global father
	if(father[x] == x):
		return x
	father[x] = FIND(father[x])
	return father[x]
def UNION(x,y):
	global father
	father[FIND(y)] = FIND(x)
def addEdge(x,y):
	global adjlist, unions, edges
	if(FIND(x) != FIND(y)):
		UNION(x,y)
		unions += 1
	adjlist[x].append(y)
	adjlist[y].append(x)
	z = min(x,y)
	w = max(x,y)
	edges[(z,w)] = 1

print('Start definitions ... ',end='')
# Definitions
# --- Define |V| = N of a Graph
n = 200
# --- Define |E| = M of a Graph
m = 5*n
# --- Define R as Number os Labels (Maximum of 456976 Diferent Labels)
r = 4569
# --- Define D for the search
d = 2
labels = []
while len(labels) < r:
	label =  gen() + gen() + gen() + gen()
	if(label not in labels):
		labels.append(label)
glabels = [None for i in range(n)] #todo = replace to  _
glabelsn = 0
# --- Define Father for UNION-FIND of Tree Construction
father = [i for i in range(n)]
# --- Define Adjacency List
adjlist = [[] for i in range(n)]
unions = 0
edges = {}
print('done')

print('Start answers ... ',end='')
# Defining a the Answers
qn = 4
qm = 3
lmax = 11 # <- Number of resulttree vertices ##to do ?
query = [(0,1),(0,2),(0,3)]
qlabels = [labels[i] for i in range(qn)]
glabels[0] = qlabels[0]
glabels[6] = qlabels[1]
glabels[3] = qlabels[1]
glabels[7] = qlabels[2]
glabels[4] = qlabels[2]
glabels[10] = qlabels[2]
glabels[5] = qlabels[3]
glabels[9] = qlabels[3]
glabels[8] = qlabels[3]
qlabels[1] = labels[qn]
qlabels[2] = labels[qn+1]
glabelsn = 11
resulttree = [(0,10),(0,1), (0,4), (4,8), (0,5),
			  (5,7), (5,6), (1,2), (2,3), (2,9)]
print('done')

print('Start constructing tree ... ',end='')
# Constructing the Tree
while(unions != n - 1):
	u = randint(0,n-1)
	v = randint(0,n-1)
	if(v != u and FIND(v) != FIND(u)):
		addEdge(u,v)
print('done')

print('Start completing graph ... ',end='')
# Completing the Graph
while(len(edges) != m):
	u = randint(lmax,n-1)
	v = randint(lmax,n-1)
	z = min(u,v)
	w = max(u,v)
	if(u != v and (z,w) not in edges):
		addEdge(u,v)
print('done')

print('Start labeling ... ',end='')
# Defining the Label
while(glabelsn != n):
	u = randint(0,n-1)
	if(glabels[u] == None):
		l = randint(qn,r-1)
		glabels[u] = labels[l]
		glabelsn += 1 
print('done')

print('Start generating archives ... ',end='')
# Generating the Archives
# --- Save Graph (.graph)
pathGraph = 'RandomizedDataBase/database_1.graph'
gfile = open(pathGraph,'w')
gfile.write('%d %d\n' % (n,m))
for i in range(n):
	gfile.write('%s\n' % (glabels[i]))
for i in edges:
	u,v = i
	gfile.write('%d %d\n' % (u,v))
gfile.close()
# --- Save Query (.query)
pathQuery = 'RandomizedDataBase/database_1_1.query'
qfile = open(pathQuery,'w')
qfile.write('%d %d %d\n' % (qn,qm,d))
for i in range(qn):
	qfile.write('%s\n' % (qlabels[i]))
for i in query:
	u,v = i
	qfile.write('%d %d\n' % (u,v))
qfile.close()
print('done')
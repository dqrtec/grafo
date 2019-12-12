# --- Importing --- #
from random import randint
from time import time
from os import system

def importQuery():
	global adj, n, m, labels, v
	arq = open("import.query","r")
	q = arq.read()[:-1].split('\n')
	c = 0
	n, m = [int(i) for i in q[c].split(" ")]
	v = n
	labels = []
	c += 1
	for i in range(n):
		labels.append(q[c])
		c += 1
	adj = [[] for i in range(n)]
	for i in range(m):
		a, b = [int(j) for j in q[c].split(" ")]
		adj[a].append(b)
		adj[b].append(a)
		c += 1	

def exportQuery(where,cnt):
	global adj, n, m, labels, v

	arq = open(where+"/%s.query" % cnt,"w")
	arq.write("%d %d %d\n" % (v, n, m))
	for i in range(n):
		print(i)
		arq.write(labels[i] + '\n')
	for i in range(n):
		for j in adj[i]:
			if i < j:
				arq.write(f"{i} {j}\n")
	arq.close()
	
def generateEQuery(d = 1):
	global adj, n, m, labels
	if(d < 1):
		raise Exception('D menor que 1.')
	d -= 1
	if(d == 0):
		return 0
	nl = n
	ml = 0
	adjl = [[] for i in range(n + m*(d))]
	for i in range(n):
		for j in adj[i]:
			if(j > i):
				adjl[n].append(i)
				adjl[i].append(n)
				lb = generateRandomLabel()
				labels.append(lb)
				ml += 1
				for k in range(d-2):
					adjl[n].append(n+1)
					adjl[n+1].append(n)
					lb = generateRandomLabel()
					labels.append(lb)
					n += 1
					ml += 1
				adjl[n].append(j)
				adjl[j].append(n)
				lb = generateRandomLabel()
				labels.append(lb)
				n += 1
				ml += 1
	adj = adjl
	n = len(adj)
	m = ml

def generateRandomLabel():
	global labels
	while True:
		s = "ABCDEFGHIJKLMOPQRSTUVXWYZ0123456789"
		label = "".join([s[randint(0,34)] for i in range(8)])
		if(label not in labels):
			return label

def generateLinkingTree(ntree,arcinput,arcoutput):
	inpath = "linkingtree/" + arcinput + ".query"
	outpath = "linkingtree/" + arcoutput + ".graph"
	
	cmd = f"linkingtree/linkingtree {ntree} {inpath} {outpath}"
	
	system(cmd)

	print("finalizado")
	
		

def move(FROM,TO):
	arq = open(FROM,'r')
	s = arq.read()
	arq.close()
	
	arq = open(TO,'w')
	arq.write(s)
	arq.close()
	
# --- Main --- #
'''
importQuery()
generateEQuery(3)
exportQuery('linkingtree',"resp")
generateLinkingTree(10,"resp","resp")
'''
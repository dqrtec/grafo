#http://arborjs.org/

import pygame
import sys
import random
import threading
import time

import Main as gera

def salvarGrafo(lista_vetices,delta,n):
	arquivo_saida = open("import.query",'w')
	dicionarioVertices = {}
	listaLabels = []
	conjuntoArestas = set()
	for i in range(len(lista_vetices)):
		verticeAtual = lista_vetices[i]
		dicionarioVertices[ verticeAtual ] = i
		listaLabels.append(verticeAtual.label)

	for i in range(len(lista_vetices)):
		verticeAtual = lista_vetices[i]
		for j in verticeAtual.listaAdj:
			u = dicionarioVertices[ verticeAtual ]
			w = dicionarioVertices[j]
			conjuntoArestas.add( (u,w) )

	arquivo_saida.write( '%d %d\n' % (len(lista_vetices),len(conjuntoArestas)) )
	for i in listaLabels:
		arquivo_saida.write('%s\n' % (i))
	for i , j in conjuntoArestas:
		arquivo_saida.write('%d %d\n' % (i,j))
	arquivo_saida.close()

	gera.importQuery()
	print("Delta = "+str(delta))
	gera.generateEQuery()#int(delta.label))
	gera.exportQuery('linkingtree',"resp")
	print("|Vg| = "+str(n))
	qtd = len(lista_vetices)+len(conjuntoArestas)*(delta-1)
	qtd = n - len(conjuntoArestas)*(delta-1)
	gera.generateLinkingTree(n-len(lista_vetices),"resp","resp")

	print("Grafo G gerado com sucesso")

class Entrada:
	def __init__(self,TelaInicial,nome,x,y):
		self.TelaInicial = TelaInicial
		self.x = x
		self.y = y
		self.retangulo = pygame.draw.rect(TelaInicial, pygame.Color(255,0,0) , pygame.Rect(x, y, 120, 60) ,0)
		self.label = ""

	def concatenarLabel(self,palavraAConcatenar):
		self.label = self.label + palavraAConcatenar

	def removerUltimaLetraLabel(self):
		self.label = self.label[:-1]

	def desenhar(self,TelaInicial):
		pygame.draw.rect(TelaInicial, pygame.Color(255,34,90) , pygame.Rect(self.x, self.y, 120, 60) ,0)

class Vertice:
	def __init__(self,TelaInicial,cor_vertice,x,y):
		self.TelaInicial = TelaInicial
		self.x = x
		self.y = y
		self.retangulo = pygame.draw.circle(TelaInicial,cor_vertice, (x,y) ,20)
		self.label = ""
		self.coloracao = cor_vertice
		self.listaAdj = []

	def setLabel(self,labelNova):
		self.label = labelNova

	def concatenarLabel(self,palavraAConcatenar):
		self.label = self.label + palavraAConcatenar

	def removerUltimaLetraLabel(self):
		self.label = self.label[:-1]

	def adicionarVerticeAdj(self,veticeAdj):
		self.listaAdj.append(veticeAdj)
		veticeAdj.listaAdj.append(self)

	def setColoracao(self,corNova):
		self.coloracao = corNova

	def atualizarPosicao(self):
		self.retangulo = pygame.draw.circle(self.TelaInicial, self.coloracao, (self.x, self.y), 20)

	def excluirVertice(self):
		for i in self.listaAdj:
			i.listaAdj.remove(self)

pygame.init()

red = pygame.Color(255,0,0)
green = pygame.Color(0,255,0)
blue = pygame.Color(0,0,255)
black = pygame.Color(0,0,0)
bkg = pygame.Color(255,240,200)

TelaInicial = pygame.display.set_mode((900,600))
TelaInicial.fill(bkg)

fpsController = pygame.time.Clock()
fpsController.tick(60) # 60 frames por segundo #tick(framerate=0)

pygame.display.flip()#atualiza a tela

logo = pygame.image.load("g1.png")
logo = pygame.transform.scale(logo, (32, 32))
pygame.display.set_icon(logo)
pygame.display.set_caption('Gerado de Grafos')

imagemSave = pygame.image.load("saveIco.png")
imagemSave = pygame.transform.scale(imagemSave, (80, 80))
rimagemSave = imagemSave.get_rect()
rimagemSave = rimagemSave.move((800,500))
imagemCaptura = pygame.image.load("capturaIco.png")
imagemCaptura = pygame.transform.scale(imagemCaptura, (80, 80))
rimagemCaptura = imagemCaptura.get_rect()
rimagemCaptura = rimagemCaptura.move((800,400))

rectangle_draging = False

myFont = pygame.font.SysFont('monaco', 72)

inputDelta = Entrada(TelaInicial,"delta",140,0)
inputN = Entrada(TelaInicial,"n",390,0)

lista_vetices = []

verticeSelecionado = None
campoSelecionado = None

tempoClickDuplo = pygame.time.get_ticks()
quantidadVerticeClickDuplo = 0
listaVerticesClickDuplo = [None,None]

excluirVertice = False

pygame.time.set_timer(pygame.USEREVENT, 50)#solucao 2 - nao ha muito ganho - 50%

while True:
	fpsController.tick(30)
	#time.sleep(0.1) # solucao 1 - deixa meio lento - 20%
	pygame.time.wait(10)# solucao 3 - 

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
			sys.exit()

		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_SPACE:
				pygame.quit()
				sys.exit()
			elif event.key == 306:# tecla control
				if excluirVertice:
					pygame.mouse.set_cursor(*pygame.cursors.arrow)
					excluirVertice = False
				else:
					pygame.mouse.set_cursor(*pygame.cursors.broken_x)
					excluirVertice = True
			if verticeSelecionado is not None:
				if event.key == 8:#backspace
					verticeSelecionado.removerUltimaLetraLabel()
				else:
					caracter = chr(event.key) if event.key>= 97 else ""
					verticeSelecionado.concatenarLabel( chr(event.key) )
			if campoSelecionado is not None:
				if event.key == 8:#backspace
					campoSelecionado.removerUltimaLetraLabel()
				else:
					caracter = chr(event.key) if event.key>= 97 else ""
					campoSelecionado.concatenarLabel( chr(event.key) )

		elif event.type == pygame.MOUSEBUTTONDOWN:
			if verticeSelecionado is not None:
				verticeSelecionado.setColoracao(blue)
			if event.button == 1:

				if rimagemSave.collidepoint(event.pos):
					salvarGrafo(lista_vetices,int(inputDelta.label),int(inputN.label))
				if rimagemCaptura.collidepoint(event.pos):
					pygame.image.save(TelaInicial,"fotografia.png")

				for i in lista_vetices:
					if i.retangulo.collidepoint(event.pos):
						if not excluirVertice:
							tempoAtual = pygame.time.get_ticks()
							if tempoAtual - tempoClickDuplo < 500 :
								listaVerticesClickDuplo[ quantidadVerticeClickDuplo ] = i
								quantidadVerticeClickDuplo += 1
							else:
								tempoClickDuplo = tempoAtual

							rectangle_draging = True
							mouse_x, mouse_y = event.pos
							offset_x = i.x - mouse_x
							offset_y = i.y - mouse_y
							i.setColoracao(red)
							verticeSelecionado = i
							campoSelecionado = None
							break
						else:
							lista_vetices.remove(i)
							i.excluirVertice()
					else:
						if verticeSelecionado is not None:
							verticeSelecionado.setColoracao(blue)
							verticeSelecionado = None

				if inputDelta.retangulo.collidepoint(event.pos):
					campoSelecionado = inputDelta
					verticeSelecionado = None
				elif inputN.retangulo.collidepoint(event.pos):
					campoSelecionado = inputN
					verticeSelecionado = None
				else:
					campoSelecionado = None


			else:
				lista_vetices.append( Vertice(TelaInicial, red, event.pos[0], event.pos[1]) )
				verticeSelecionado = lista_vetices[ len(lista_vetices)-1 ]
				campoSelecionado = None

		elif event.type == pygame.MOUSEBUTTONUP:
			if rectangle_draging:
				verticeSelecionado.atualizarPosicao()
				rectangle_draging = False
				#verticeSelecionado = None
				

		elif event.type == pygame.MOUSEMOTION:
			if rectangle_draging:
				mouse_x, mouse_y = event.pos
				verticeSelecionado.x = mouse_x + offset_x
				verticeSelecionado.y = mouse_y + offset_y

	if quantidadVerticeClickDuplo == 2:
		listaVerticesClickDuplo[0].adicionarVerticeAdj(listaVerticesClickDuplo[1])
		quantidadVerticeClickDuplo = 0
		listaVerticesClickDuplo[0] = None
		listaVerticesClickDuplo[1] = None

	TelaInicial.fill(bkg)

	for i in lista_vetices:
		for j in i.listaAdj:
			pygame.draw.aaline(TelaInicial,black,(i.x,i.y),(j.x,j.y))

	for i in lista_vetices:
		vertice_atual = pygame.draw.circle(TelaInicial, i.coloracao,(i.x, i.y),20)
		GOsurf = myFont.render(i.label, True, pygame.Color(0,100,255))
		TelaInicial.blit(GOsurf,vertice_atual)


	rectDelta = pygame.draw.rect(TelaInicial, bkg , pygame.Rect(5, 0, 120, 0) ,0)
	GOsurf = myFont.render("Delta:", True, pygame.Color(0,100,255))
	TelaInicial.blit(GOsurf,rectDelta)

	inputDelta.desenhar(TelaInicial)
	GOsurf = myFont.render(inputDelta.label, True, pygame.Color(0,100,255))
	TelaInicial.blit(GOsurf,inputDelta.retangulo)

	rectN = pygame.draw.rect(TelaInicial, bkg , pygame.Rect(280, 0, 120, 0) ,0)
	GOsurf = myFont.render("|Vq|:", True, pygame.Color(0,100,255))
	TelaInicial.blit(GOsurf,rectN)

	inputN.desenhar(TelaInicial)
	GOsurf = myFont.render(inputN.label, True, pygame.Color(0,100,255))
	TelaInicial.blit(GOsurf,inputN.retangulo)


	TelaInicial.blit(imagemSave, rimagemSave)
	TelaInicial.blit(imagemCaptura, rimagemCaptura)
	
	pygame.display.flip()
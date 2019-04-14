import pygame
import sys
import random
import threading
import time

class Vertice:
	def __init__(self,TelaInicial,cor_vertice,x,y):
		self.TelaInicial = TelaInicial
		self.x = x
		self.y = y
		self.retangulo = pygame.draw.circle(TelaInicial,cor_vertice, (x,y) ,20)
		self.label = str(random.randint(0,10))
		self.coloracao = cor_vertice
		self.listaAdj = []

	def setLabel(self,labelNova):
		self.label = labelNova

	def adicionarVerticeAdj(self,veticeAdj):
		self.listaAdj.append(veticeAdj)
		veticeAdj.listaAdj.append(self)

	def setColoracao(self,corNova):
		self.coloracao = corNova

	def atualizarPosicao(self):
		self.retangulo = pygame.draw.circle(self.TelaInicial, self.coloracao, (self.x, self.y), 20)

pygame.init()

red = pygame.Color(255,0,0)
green = pygame.Color(0,255,0)
blue = pygame.Color(0,0,255)
black = pygame.Color(0,0,0)
bkg = pygame.Color(255,240,200)

TelaInicial = pygame.display.set_mode((900,600))
TelaInicial.fill(bkg)

fpsController = pygame.time.Clock()
fpsController.tick(2)

pygame.display.flip()#atualiza a tela


rectangle_draging = False

myFont = pygame.font.SysFont('monaco', 72)

lista_vetices = []

verticeSelecionado = None

tempoClickDuplo = 0.0
quantidadVerticeClickDuplo = 0
listaVerticesClickDuplo = [None,None]

#pygame.time.set_timer(pygame.USEREVENT, 50)#solucao 2 - nao ha muito ganho - 50%

while True:
	#time.sleep(0.1) # solucao 1 - deixa meio lento - 20%
	pygame.time.wait(10)# solucao 3 - 
	TelaInicial.fill(bkg)

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			pygame.quit()
			sys.exit()

		if event.type == pygame.KEYDOWN:
			if event.key == pygame.K_SPACE:
				pygame.quit()
				sys.exit()

		elif event.type == pygame.MOUSEBUTTONDOWN:
			if verticeSelecionado is not None:
				verticeSelecionado.setColoracao(blue)
			if event.button == 1:
				for i in lista_vetices:
					if i.retangulo.collidepoint(event.pos):

						if tempoClickDuplo<0.5:
							listaVerticesClickDuplo[ quantidadVerticeClickDuplo ] = i
							quantidadVerticeClickDuplo += 1
						else:
							tempoClickDuplo = 0

						rectangle_draging = True
						mouse_x, mouse_y = event.pos
						offset_x = i.x - mouse_x
						offset_y = i.y - mouse_y
						i.setColoracao(red)
						verticeSelecionado = i
						break
			else:
				lista_vetices.append( Vertice(TelaInicial, red, event.pos[0], event.pos[1]) )
				verticeSelecionado = lista_vetices[ len(lista_vetices)-1 ]

		elif event.type == pygame.MOUSEBUTTONUP:
			if rectangle_draging:
				verticeSelecionado.atualizarPosicao()
				verticeSelecionado.setColoracao(blue)
				rectangle_draging = False
				verticeSelecionado = None
				

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


	for i in lista_vetices:
		for j in i.listaAdj:
			pygame.draw.line(TelaInicial,black,(i.x,i.y),(j.x,j.y))

	for i in lista_vetices:
		vertice_atual = pygame.draw.circle(TelaInicial, i.coloracao,(i.x, i.y),20)
		GOsurf = myFont.render(i.label, True, pygame.Color(0,100,255))
		TelaInicial.blit(GOsurf,vertice_atual)

	tempoClickDuplo+=0.01


	pygame.display.update()
	pygame.display.flip()
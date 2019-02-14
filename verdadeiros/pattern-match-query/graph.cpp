#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <climits>
#include "graph.h"

using namespace std;

Graph::Graph(int N) {
    this->N = N;
    this->adjL = new list<int>[N]; // Cria N listas de adjacências
    this->V = new Vertex[N];
    for (int i = 0; i < N; i++){
        this->V[i].setId(i);
    }
}

Graph::Graph() {}

void Graph::addEdge(int v1, int v2)
{
    // Adiciona vértice v2 à lista de vértices adjacentes de v1
    this->adjL[v1].push_back(v2);
    // Adiciona vértice v1 à lista de vértices adjacentes de v2
    this->adjL[v2].push_back(v1);

    this->M++; // Incrementa o número de arestas
}

// Implementação com lista de adjacências
int* Graph::bfs_adjL(int start) {

    int visited[this->N]; // Array para armazenar se o vértice foi visitado ou não
    int* dist = new int[this->N]; // Distância do vértice inicial

    for (int i = 0; i < this->N; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
    }

    visited[start] = true;
    dist[start] = 0;
    queue<int> Queue;
    Queue.push(start);

    while (! Queue.empty()) {
        int u = Queue.front(); // Pega o primeiro vértice da fila
        Queue.pop();

        list<int>::iterator it;        
        for(it = adjL[u].begin(); it != adjL[u].end(); it++) { // Para cada vértice na lista de adjacências de u
            if(visited[*it] == false) { // Se ele ainda não foi visitado
                visited[*it] = true;
                dist[*it] = dist[u] + 1; 
                Queue.push(*it); // Coloca vértice na fila
            }
        }
    }

    return dist;
}

int** Graph::distMatrix() {

    // Criando matriz de distancias
    int** dist = new int*[this->N];
    for (int i = 0; i <this-> N; i++){
        dist[i] = new int[N];
    }

    for (int i = 0; i < this->N; i++) {
        dist[i] = this->bfs_adjL(i);
    }

    return dist;
}

// RETORNO: VETOR de INTEIROS contendo ECENTRICIDADE dos vertices do grafo THIS
int* Graph::ecentricidadeVertices(){
    int** matrixDistanciasEntreVertices = this->distMatrix();
    int* listaEcentricidadeVertices = new int[this->N] ;

    for (int linha = 0; linha < N; linha++){
        listaEcentricidadeVertices[linha] = 0;
        for(int coluna = 0; coluna < N; coluna++){
            listaEcentricidadeVertices[linha] = max(listaEcentricidadeVertices[linha], matrixDistanciasEntreVertices[linha][coluna]);
        }
    }

    return listaEcentricidadeVertices;
}

// Retorna Ordem das labels e coloca a ecentricidade
// das respectivas labels na variavel ecentricidadeQ
string* Graph::ListaM(int* ecentricidadeQ) {

    int *ecc = ecentricidadeVertices();
    int *listaEcentricidadesOrdenadas = ecc;
    int *listaTrocas = new int[N];
    listaTrocas[0] = 0;
    int aux;
    int j;
    string* ordemLabels = new string[N];


    for (int i = 1; i < N; i++) {
        listaTrocas[i] = i;
        j = i;
        while ((listaEcentricidadesOrdenadas[j - 1] > listaEcentricidadesOrdenadas[i]) && (j != 0)) {
            j--;

            aux = listaEcentricidadesOrdenadas[j];
            listaEcentricidadesOrdenadas[j] = listaEcentricidadesOrdenadas[i];
            listaEcentricidadesOrdenadas[i] = aux;

            aux = listaTrocas[j];
            listaTrocas[j] = listaTrocas[i];
            listaTrocas[i] = aux;
        }

    }


    for (int k = 0; k < N; k++) {
        ordemLabels[k] = V[ listaTrocas[k] ].getLabel();
        ecentricidadeQ[k] = listaEcentricidadesOrdenadas[k];
    }


    return ordemLabels;
}

// Retorna BITMAP de todos os vertices que podem ser atingidos apartir do vertice 'start'
// respeitando uma distancia delta*ecentricidadeVerticeInicial
Bitmap Graph::bitmapDistanciaPermitida(int start, int delta, int ecentricidadeVerticeInicial){

    int visited[this->N]; // Array para armazenar se o vértice foi visitado ou não
    int* dist = new int[this->N]; // Distância do vértice inicial
    int distanciaMaximaLargura = delta * ecentricidadeVerticeInicial;
    vector<int> vetorVerticesAtingidosDistanciaPermitida;


    for (int i = 0; i < this->N; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
    }

    visited[start] = true;
    dist[start] = 0;
    queue<int> Queue;
    vetorVerticesAtingidosDistanciaPermitida.push_back(start);
    Queue.push(start);

    while (! Queue.empty()) {
        int u = Queue.front(); // Pega o primeiro vértice da fila
        Queue.pop();

        list<int>::iterator it;
        for(it = adjL[u].begin(); it != adjL[u].end(); it++) { // Para cada vértice na lista de adjacências de u
            if(visited[*it] == false) { // Se ele ainda não foi visitado
                visited[*it] = true;
                dist[*it] = dist[u] + 1;
                if(dist[*it] <= distanciaMaximaLargura) {
                    Queue.push(*it); // Coloca vértice na fila
                    vetorVerticesAtingidosDistanciaPermitida.push_back(*it);
                }
            }
        }
    }

    Bitmap FP(vetorVerticesAtingidosDistanciaPermitida);
    return FP;
}



int Graph::getN() {
    return this->N;
}

int Graph::getM() {
    return this->M;
}


list<int>* Graph::getAdjL() {
    return this->adjL;
}

Vertex* Graph::getV() {
    return this->V;
}

int Vertex::getId() {
    return this->id;
}

void Vertex::setId(int id) {
    this->id = id;
}

string Vertex::getLabel() {
    return this->label;
}

void Vertex::setLabel(string label) {
    this->label = label;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <list>
#include <map>
#include <deque>
#include <chrono>
#include <climits>
#include "graph.h"
#include "vertex.h"

using namespace std;

// Fator multiplicativo da ecentricidade
int DELTA = 2;

Graph Q(2); //Instancia grafo Q
Graph G(4); //Instancia grafo G

void Query(int interacaoI, GraphBitmap bitmapAreaBuscaMi, int* vetorEcentricidadeQ, string* ordemLabels);

int main(int argc, char const *argv[]) {

    // Adicao de vertices no grafo Q
    Q.getV()[0].setLabel("A");
    Q.getV()[1].setLabel("B");

    // Criacao aresta no grafo Q
    Q.addEdge(0, 1);

    // Adicao de vertices no grafo G
    G.getV()[0].setLabel("A");
    G.getV()[1].setLabel("B");
    G.getV()[2].setLabel("C");
    G.getV()[3].setLabel("D");

    // Criacao aresta no grafo G
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(2, 3);

    // Cria vetor que contera as ecentricidades dos vertices ja na ordem 'i'
    int* ecentricidadeQ = new int[Q.getN()];

    // Ordena as labels pela ecentricidade e coloca suas respectivas exentricidades no vertice ecentricidadeQ
    string* Ordemlabls = Q.ListaM(ecentricidadeQ);

    // Percorre todos os vertices do grafo G
    // em busca do primeiro m1 para executar busca sobre m1

    // Lista de vertices do grafo G
    Vertex* vetorVerticesG = G.getV();

    // Percorre todos os vestices de G
    for (int m1 = 0; m1 < G.getN(); m1++){
        // Verifica se o vertice 'm1' de G e do label m1
        if(vetorVerticesG[m1].getLabel() == Ordemlabls[0]){
            // Gera Bitmap dos vertices atringidos apartir de m1 a uma distancia DELTA*ecentricidade(m1)
            GraphBitmap BitmapF1 = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]) ;
            Query(2,BitmapF1,ecentricidadeQ,Ordemlabls);
        }
    }

    return 0;
}

void Query(int interacaoI, GraphBitmap bitmapAreaBuscaMi, int* vetorEcentricidadeQ, string* ordemLabels){
    // Bitmap contendo somente os vertices para a consulta
    vector<Vertex *> fi = bitmapAreaBuscaMi.getAllTrue();

    // Percorre todos os vertices que podem fazer match e
    // verifica se tem o mesmo label que mi

    bitmapAreaBuscaMi.show();

    // Percorre todos os Vetores de Possiveis de Busca
    for (int verticeBuscaAtual = 0; verticeBuscaAtual < fi.size(); verticeBuscaAtual++){
        // Verifica se determinado vertice tem o mesmo label de mi
        if(  G.getV()[ fi[verticeBuscaAtual]->getId() ].getLabel() == ordemLabels[interacaoI-1]){
            if(interacaoI == Q.getN()){
                cout<<"Query Encontrada";
            }else{
                GraphBitmap areaBuscaApartirMi = G.bitmapDistanciaPermitida( fi[verticeBuscaAtual]->getId(), DELTA, vetorEcentricidadeQ[interacaoI-1] );
                GraphBitmap proximaBitmapBusca = bitmapAreaBuscaMi.intersection( &areaBuscaApartirMi );
                Query(interacaoI+1, proximaBitmapBusca, vetorEcentricidadeQ, ordemLabels);
            }
        }
    }
}
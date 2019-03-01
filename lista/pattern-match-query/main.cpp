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

Graph Q(8); //Instancia grafo Q

Graph G("../../Datasets/YeastS.net"); //Instancia grafo G

int* caminhoVertices = new int[Q.getN()];

void Query(int interacaoI, GraphBitmap bitmapAreaBuscaMi, int* vetorEcentricidadeQ, string* ordemLabels);
void impirmirCaminhoVertices();

int main(int argc, char const *argv[]) {

    // Adicao de vertices no grafo Q
    Q.getV()[0].setLabel("\"YJR064W\"");
    Q.getV()[1].setLabel("\"YJR084W\"");
    Q.getV()[2].setLabel("\"YGR013W\"");
    Q.getV()[3].setLabel("\"YER006W\"");
    Q.getV()[4].setLabel("\"YGR245C\"");
    Q.getV()[5].setLabel("\"YDL051W\"");
    Q.getV()[6].setLabel("\"YIR003W\"");
    Q.getV()[7].setLabel("\"YKL012W\"");

    // Criacao aresta no grafo Q
    Q.addEdge(0, 1);
    Q.addEdge(1, 2);
    Q.addEdge(2, 3);
    Q.addEdge(3, 4);
    Q.addEdge(4, 5);
    Q.addEdge(5, 6);
    Q.addEdge(6, 7);

    auto inicio = std::chrono::high_resolution_clock::now();

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
            caminhoVertices[0] = m1;
            // Gera Bitmap dos vertices atringidos apartir de m1 a uma distancia DELTA*ecentricidade(m1)
            GraphBitmap BitmapF1 = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]);
            Query(2,BitmapF1,ecentricidadeQ,Ordemlabls);
        }
    }

    auto fim = std::chrono::high_resolution_clock::now() - inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fim).count();
    cout<<"tempo gasto = "<< microseconds<<endl;

    return 0;
}

void Query(int interacaoI, GraphBitmap bitmapAreaBuscaMi, int* vetorEcentricidadeQ, string* ordemLabels){
    // Bitmap contendo somente os vertices para a consulta
    vector<Vertex *> fi = bitmapAreaBuscaMi.getAllTrue();

    // Percorre todos os vertices que podem fazer match e
    // verifica se tem o mesmo label que mi

    // Percorre todos os Vetores de Possiveis de Busca
    for (int verticeBuscaAtual = 0; verticeBuscaAtual < fi.size(); verticeBuscaAtual++){
        // Verifica se determinado vertice tem o mesmo label de mi
        if(  G.getV()[ fi[verticeBuscaAtual]->getId() ].getLabel() == ordemLabels[interacaoI-1]){
            caminhoVertices[interacaoI-1] = fi[verticeBuscaAtual]->getId() ;
            if(interacaoI == Q.getN()){
                cout<<"Query Encontrada = ";
                impirmirCaminhoVertices();
                G.ImprimirVerticesQueCompoemCaminho(Q,caminhoVertices,DELTA,vetorEcentricidadeQ);
            }else{
                GraphBitmap areaBuscaApartirMi = G.bitmapDistanciaPermitida( fi[verticeBuscaAtual]->getId(), DELTA, vetorEcentricidadeQ[interacaoI-1] );
                GraphBitmap proximaBitmapBusca = bitmapAreaBuscaMi.intersection( &areaBuscaApartirMi );
                Query(interacaoI+1, proximaBitmapBusca, vetorEcentricidadeQ, ordemLabels);
            }
        }
    }
}

void impirmirCaminhoVertices(){
    cout<<"Os vertices G que compoẽm a query são : ";
    for(int i=0; i< Q.getN(); i++ ){
        cout<<caminhoVertices[i] <<", ";
    }
    cout<<endl;
}
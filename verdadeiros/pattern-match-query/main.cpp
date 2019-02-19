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
#include "bitmap.h"

using namespace std;

int DELTA = 4;

Graph Q(3);
Graph G("/home/megazzzmata/Área de Trabalho/git/grafo/verdadeiros/pattern-match-query/Datasets/YeastS.net");

void Query(int interacaoI,Bitmap FI,int* ecentricidadeQ, string* OrdemLabels);

int main(int argc, char const *argv[]) {
    auto inicio = std::chrono::high_resolution_clock::now();

    Q.getV()[0].setLabel("\"YBR236C\"");
    Q.getV()[1].setLabel("\"YOR151C\"");

    Q.addEdge(0, 1);


    int* ecentricidadeQ = new int[Q.getN()];
    // Ordena as labels pela ecentricidade e coloca suas respectivas exentricidades no vertice ecentricidadeQ
    string* Ordemlabls = Q.ListaM(ecentricidadeQ);
    cout<<ecentricidadeQ[0]<<endl;
    cout<<ecentricidadeQ[1]<<endl;

    Vertex* vetorVerticesG = G.getV();
    for (int m1 = 0; m1 < G.getN(); m1++){
        if(vetorVerticesG[m1].getLabel() == Ordemlabls[0]){
            Bitmap F1 = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]) ;
            Query(2,F1,ecentricidadeQ,Ordemlabls);
        }
    }

    auto fim = std::chrono::high_resolution_clock::now() - inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fim).count();
    cout<< microseconds;
    return 0;
}

void Query(int interacaoI, Bitmap FI, int* ecentricidadeQ,string* Ordemlabls){
    for (int mi = 0; mi < FI.getN(); mi++) {
        cout<<"---------------------"<<endl;
        cout<<FI.getN()<<endl;
        FI.show();
        if( (G.getV()[ FI.getPosition(mi) ].getLabel() == Ordemlabls[interacaoI-1]) ){
            if(interacaoI == Q.getN()){
                cout<<"Query"<<endl;
            }else{
                Bitmap areaBuscaApartirMi = G.bitmapDistanciaPermitida(mi,DELTA,ecentricidadeQ[interacaoI-1]) ;
                Bitmap proximaBitmapBusca = FI.intercecao( areaBuscaApartirMi );
                Query(interacaoI+1, proximaBitmapBusca ,ecentricidadeQ,Ordemlabls);
            }
        }
    }
}
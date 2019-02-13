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
Graph G(12);

void Query(int interacaoI,Bitmap FI,int* ecentricidadeQ, string* OrdemLabels);

int main(int argc, char const *argv[]) {

    Q.getV()[0].setLabel("A");
    Q.getV()[1].setLabel("B");
    Q.getV()[2].setLabel("C");

    Q.addEdge(0, 1);
    Q.addEdge(1, 2);

/*
    G.getV()[0].setLabel("A");
    G.getV()[1].setLabel("B");
    G.getV()[2].setLabel("C");

    G.addEdge(0, 1);
    G.addEdge(1, 2);
*/

    G.getV()[0].setLabel("A");
    G.getV()[1].setLabel("A");
    G.getV()[2].setLabel("B");
    G.getV()[3].setLabel("C");

    G.getV()[4].setLabel("D");
    G.getV()[5].setLabel("D");
    G.getV()[6].setLabel("D");
    G.getV()[7].setLabel("D");
    G.getV()[8].setLabel("D");
    G.getV()[9].setLabel("D");
    G.getV()[10].setLabel("D");
    G.getV()[11].setLabel("D");

    G.addEdge(4, 1);
    G.addEdge(4, 5);
    G.addEdge(5, 6);
    G.addEdge(6, 7);
    G.addEdge(6, 2);
    G.addEdge(7, 8);
    G.addEdge(8, 2);
    G.addEdge(8, 3);
    G.addEdge(8, 0);
    G.addEdge(0, 11);
    G.addEdge(11, 2);
    G.addEdge(11, 10);
    G.addEdge(10, 9);
    G.addEdge(9, 1);



    int* ecentricidadeQ = new int[Q.getN()];
    // Ordena as labels pela ecentricidade e coloca suas respectivas exentricidades no vertice ecentricidadeQ
    string* Ordemlabls = Q.ListaM(ecentricidadeQ);

    Vertex* vetorVerticesG = G.getV();
    for (int m1 = 0; m1 < G.getN(); m1++){
        if(vetorVerticesG[m1].getLabel() == Ordemlabls[0]){
            Bitmap F1 = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]) ;
            Query(2,F1,ecentricidadeQ,Ordemlabls);
        }
    }

    return 0;
}

void Query(int interacaoI, Bitmap FI, int* ecentricidadeQ,string* Ordemlabls){
    for (int mi = 0; mi < FI.getN(); mi++) {
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
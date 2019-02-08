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

using namespace std;

int DELTA = 1;

Graph Q(2);
Graph G(4);

void Query(int i,GraphBitmap FI,int* ecentricidadeQ, string* OrdemLabels);

int main(int argc, char const *argv[]) {

    Q.getV()[0].setLabel("A");
    Q.getV()[1].setLabel("B");

    Q.addEdge(0, 1);

//////////////////////////

    G.getV()[0].setLabel("A");
    G.getV()[1].setLabel("B");
    G.getV()[2].setLabel("C");
    G.getV()[3].setLabel("D");

    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(2, 3);

    int* ecentricidadeQ = new int[Q.getN()];
    string* Ordemlabls = Q.ListaM(ecentricidadeQ);

    for (int m1 = 0; m1 < G.getN(); m1++){
        if(G.getV()[m1].getLabel() == Ordemlabls[0]){
            cout<< Ordemlabls[m1] <<endl;
            GraphBitmap FI = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]) ;
            Query(2,FI,ecentricidadeQ,Ordemlabls);
        }
    }




    return 0;
}

void Query(int i, GraphBitmap FI, int* ecentricidadeQ,string* Ordemlabls){
    vector<Vertex *> f = FI.getAllTrue();
    for (int j = 0; j < f.size(); j++) {
        cout<< i << "   -   "<< j <<endl;
        if( f[j]->getLabel() == Ordemlabls[i-1]){
            if(i == Q.getN()){
                cout<<"Query";
            }else{
                GraphBitmap ff = FI.intersection( G.bitmapDistanciaPermitida(f[j]->getId(),DELTA,ecentricidadeQ[i-1]) );
                Query(i+1, ff ,ecentricidadeQ,Ordemlabls);
            }
        }
    }
}
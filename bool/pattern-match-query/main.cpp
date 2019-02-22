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

int DELTA = 5;

Graph Q(8);

Graph G("../../Datasets/YeastS.net");

int* caminhoVertices = new int[Q.getN()];

void Query(int interacaoI,Bitmap FI,int* ecentricidadeQ, string* OrdemLabels);
void impirmirCaminhoVertices();

int main(int argc, char const *argv[]) {

    Q.getV()[0].setLabel("\"YJR064W\"");
    Q.getV()[1].setLabel("\"YJR084W\"");
    Q.getV()[2].setLabel("\"YGR013W\"");
    Q.getV()[3].setLabel("\"YER006W\"");
    Q.getV()[4].setLabel("\"YGR245C\"");
    Q.getV()[5].setLabel("\"YDL051W\"");
    Q.getV()[6].setLabel("\"YIR003W\"");
    Q.getV()[7].setLabel("\"YKL012W\"");

    Q.addEdge(0, 1);
    Q.addEdge(1, 2);
    Q.addEdge(2, 3);
    Q.addEdge(3, 4);
    Q.addEdge(4, 5);
    Q.addEdge(5, 6);
    Q.addEdge(6, 7);

    auto inicio = std::chrono::high_resolution_clock::now();

    int* ecentricidadeQ = new int[Q.getN()];
    // Ordena as labels pela ecentricidade e coloca suas respectivas exentricidades no vertice ecentricidadeQ
    string* Ordemlabls = Q.ListaM(ecentricidadeQ);

    Vertex* vetorVerticesG = G.getV();
    for (int m1 = 0; m1 < G.getN(); m1++){
        if(vetorVerticesG[m1].getLabel() == Ordemlabls[0]){
            caminhoVertices[0] = m1;
            Bitmap F1 = G.bitmapDistanciaPermitida(m1,DELTA,ecentricidadeQ[0]) ;
            Query(2,F1,ecentricidadeQ,Ordemlabls);
        }
    }

    auto fim = std::chrono::high_resolution_clock::now() - inicio;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(fim).count();
    cout<<"tempo gasto = "<< microseconds<<endl;

    return 0;
}

void Query(int interacaoI, Bitmap FI, int* ecentricidadeQ,string* Ordemlabls){
    for (int mi = 0; mi < G.getN(); mi++) {
        if( (FI.getPosition(mi)) && (G.getV()[mi].getLabel() == Ordemlabls[interacaoI-1]) ){
            caminhoVertices[interacaoI-1] = mi ;
            if(interacaoI == Q.getN()){
                cout<<"Query"<<endl;
                impirmirCaminhoVertices();
            }else{
                Bitmap areaBuscaApartirMi = G.bitmapDistanciaPermitida(mi,DELTA,ecentricidadeQ[interacaoI-1]) ;
                Bitmap proximaBitmapBusca = FI.intercecao( areaBuscaApartirMi );
                Query(interacaoI+1, proximaBitmapBusca ,ecentricidadeQ,Ordemlabls);
            }
        }
    }
}

void impirmirCaminhoVertices(){
    for(int i=0; i< Q.getN(); i++ ){
        cout<<caminhoVertices[i] <<", ";
    }
    cout<<endl;
}
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include "graphbitmap.h"

using namespace std;

class Vertex {
private:
    int id;
    string label;
public:
    int getId();
    void setId(int id);
    string getLabel();
    void setLabel(string label);
};

class Graph {
private:
    int N; // Número de vértices
    int M; // Número de arestas
    list<int>* adjL; // Array contendo as listas de adjacências     
    Vertex* V; // Array contendo os vértices
public:    
    Graph(int N); // Construtor

    void addEdge(int v1, int v2);

    // Busca em largura com listas de adjacências
    // Retorna um array com as distâncias dos outros vértices ao vértice inicial
    int* bfs_adjL(int start);
    GraphBitmap bitmapDistanciaPermitida(int start, int delta, int ecentricidadeVerticeInicial);
    int** distMatrix(); // Retorna matriz de distâncias
    int getN();
    int getM();
    int** getAdjM();
    int* ecentricidadeVertices();
    list<int>* getAdjL();
    Vertex* getV();
    string* ListaM(int* ecentricidadeQ);
};


#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include "bitmap.h"

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
    Graph(); // Construtor
    Graph(int N); // Construtor
    Graph(string nomeArquivo);

    void addEdge(int v1, int v2);

    // Busca em largura com listas de adjacências
    // Retorna um array com as distâncias dos outros vértices ao vértice inicial
    int* bfs_adjL(int start);

    // Retorna BITMAP de todos os vertices que podem ser atingidos apartir do vertice 'start'
    // respeitando uma distancia delta*ecentricidadeVerticeInicial
    Bitmap bitmapDistanciaPermitida(int start, int delta, int ecentricidadeVerticeInicial);

    int** distMatrix(); // Retorna matriz de distâncias
    int getN();
    int getM();
    int** getAdjM();
    int* ecentricidadeVertices();
    list<int>* getAdjL();
    Vertex* getV();

    // Retorna Ordem das labels e coloca a ecentricidade
    // das respectivas labels na variavel ecentricidadeQ
    string* ListaM(int* ecentricidadeQ);

    void ImprimeListaAdjacencia(int i);
};


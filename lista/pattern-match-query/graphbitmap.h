#include <bits/stdc++.h>
#include "common.h"
#include "bitmap.h"

using namespace std;

class GraphBitmap {
private:
    int N; // N�mero de v�rtices
    vector<Bitmap*> bitMapList; // Lista contendo as vari�veis bitmap
    Vertex** V; // Array contendo os v�rtices
public:
    // Construtor
    GraphBitmap(vector<Bitmap*> bitmapList);

    //Recebe um v�rtice e retorna o valor do boolean do bitmap dele
    bool getValue(Vertex v);

    //Retorna todos os v�rtices que tem como valor de boolean True
    vector<Vertex*> getAllTrue();

    //Retorna o bitmap da intersec��o do objeto com o graphBitmap passado
    GraphBitmap intersection(GraphBitmap *other);

    //Retorna o bitmap da uni�o do objeto com o graphBitmap passado
    GraphBitmap join(GraphBitmap *other);

    void show();
};
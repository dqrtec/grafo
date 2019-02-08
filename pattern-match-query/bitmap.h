#include <bits/stdc++.h>
#include "common.h"
#include "vertex.h"

using namespace std;

class Bitmap {
private:
    Vertex* vertice;
    bool bit;
public:
    //Construtor
    Bitmap(Vertex* ver, bool value);
    //gets e sets
    void setBool(bool value);
    bool getBool();
    Vertex* getVertex();
};
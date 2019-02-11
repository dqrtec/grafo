#include "bitmap.h"

Bitmap::Bitmap(Vertex* ver, bool value){
    vertice = ver;
    bit = value;
}

void Bitmap::setBool(bool value){
    bit = value;
}

bool Bitmap::getBool(){
    return true;
}

Vertex* Bitmap::getVertex(){
    return vertice;
}

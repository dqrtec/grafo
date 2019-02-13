//
// Created by zzzmata on 05/02/19.
//

#include "bitmap.h"


Bitmap::Bitmap(){}

Bitmap::Bitmap(vector<int> bm) {
    this->BM = bm;
    this->ordenarVetor();
}

Bitmap Bitmap::intercecao(Bitmap outro) {
    vector<int> daniel;

    vector<int>::iterator interadorA = this->BM.begin();
    vector<int>::iterator interadorB = outro.BM.begin();

    while( (interadorA != this->BM.end()) && (interadorB != outro.BM.end()) ){
        if( *interadorA == *interadorB ){
            daniel.push_back(*interadorA);
        }else if( *interadorA > *interadorB ){
            interadorB++;
        }else{
            interadorA++;
        }
    }

    Bitmap inteception(daniel);
    return inteception;
}

int Bitmap::getPosition(int posicao) {
    return BM[posicao];
}

void Bitmap::ordenarVetor(){
    std::sort( this->BM.begin(), this->BM.end());
}

int Bitmap::getN(){
    return this->BM.size();
}
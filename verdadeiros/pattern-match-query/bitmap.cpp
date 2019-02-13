//
// Created by zzzmata on 05/02/19.
//

#include <iostream>
#include "bitmap.h"


Bitmap::Bitmap(){}

Bitmap::Bitmap(vector<int> bm) {
    this->BM = bm;
    this->ordenarVetor();
}

Bitmap Bitmap::intercecao(Bitmap outro) {
    vector<int> daniel;

    int interadorA = 0;
    int interadorB = 0;

    while( (interadorA < BM.size()) && ( interadorB < outro.BM.size()) ){
        if( BM[interadorA] == outro.BM[interadorB] ){
            daniel.push_back(BM[interadorA]);
            interadorA++;
            interadorB++;
        }else if( BM[interadorA] > outro.BM[interadorB] ){
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

void Bitmap::show(){
    for (int i = 0; i < getN(); ++i) {
        cout<<BM[i]<<"  ";
    }
    cout<<endl;
}
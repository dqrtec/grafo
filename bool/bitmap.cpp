//
// Created by zzzmata on 05/02/19.
//

#include "bitmap.h"


Bitmap::Bitmap(){}

Bitmap::Bitmap(int n) {
    this->N = n;
    this->BM = new bool[N];
    for (int i = 0; i < N; i++) {
        this->BM[i] = false;
    }
}

void Bitmap::setPosition(int posicao, bool valorBoleano) {
    BM[posicao] = valorBoleano;
}

Bitmap Bitmap::intercecao(Bitmap interceptado) {
    Bitmap inteception(N);

    for (int i = 0; i < N; ++i) {
        if( (this->BM[i]) && (interceptado.BM[i]) ) {
            inteception.BM[i] = true;
        }
    }
    return inteception;
}

bool Bitmap::getPosition(int posicao) {
    return BM[posicao];
}
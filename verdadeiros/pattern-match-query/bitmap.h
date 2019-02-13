//
// Created by zzzmata on 05/02/19.
//

#ifndef PATTERNMATCHING_Bitmap_H
#define PATTERNMATCHING_Bitmap_H

#include <vector>
#include <algorithm>

using namespace std;

class Bitmap{
public:
    Bitmap();
    Bitmap(vector<int> bm);

    int getN();

    int getPosition(int posicao);

    void ordenarVetor();

    Bitmap intercecao(Bitmap interceptado); // Retorna BITMAP da intersecao entre dois bitmaps

    void show();

private:
    vector<int> BM;
};

#endif //PATTERNMATCHING_Bitmap_H

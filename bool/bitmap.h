//
// Created by zzzmata on 05/02/19.
//

#ifndef PATTERNMATCHING_Bitmap_H
#define PATTERNMATCHING_Bitmap_H

class Bitmap{
public:
    Bitmap();
    Bitmap(int N);

    int getN();
    void setN();

    void setPosition(int posicao, bool valorBoleano);
    bool getPosition(int posicao);

    Bitmap intercecao(Bitmap interceptado); // Retorna BITMAP da intersecao entre dois bitmaps

    bool* BM;
private:
    int N;
};

#endif //PATTERNMATCHING_Bitmap_H

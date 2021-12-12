#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include "stdlib.h"
#include "time.h"
#include <QDebug>
#include <array>

using namespace std;

class Plateau
{
public:
    Plateau(unsigned long row, unsigned long column,int nb_bombe);
    Plateau();
    void initPlateau();
    void fillTableau();
    void unlockLockCell(unsigned long row,unsigned long column);
    bool Loose(unsigned long row,unsigned long column);
    bool Win();
    void showcell(unsigned long row,unsigned long column);
    void propagationCell(unsigned long row,unsigned long column);
    bool checkBomb(unsigned long row,unsigned long column);
    void changeDimension(unsigned long row, unsigned long column,int bombe);
    vector<vector<char> > getPlateau();

private:   
    unsigned long m_row,m_column;
    int m_nb_bombe = 0;
    vector<vector<char>> m_plateauData; //Contenue du demineur
    vector<vector<bool>> m_plateauState; //true pour afficher, false pour cacher
    vector<vector<bool>> m_plateauLockState; //true = drapeau, false = rien
};

#endif // PLATEAU_H

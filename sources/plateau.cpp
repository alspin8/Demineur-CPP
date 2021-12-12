#include "plateau.h"

Plateau::Plateau(unsigned long row, unsigned long column, int nb_bombe) : m_row(row+2), m_column(column+2), m_nb_bombe(nb_bombe)
{    
    m_plateauData.resize(m_row,vector<char>(m_column));
    m_plateauState.resize(m_row,vector<bool>(m_column));
    m_plateauLockState.resize(m_row,vector<bool>(m_column));
    srand((static_cast<unsigned int>(time(nullptr))));
}

Plateau::Plateau() : m_row(11), m_column(11), m_nb_bombe(10)
{
    m_plateauData.resize(m_row,vector<char>(m_column));
    m_plateauState.resize(m_row,vector<bool>(m_column));
    m_plateauLockState.resize(m_row,vector<bool>(m_column));
    srand((static_cast<unsigned int>(time(nullptr))));
}

void Plateau::initPlateau()
{
    for(unsigned long i =0 ; i < m_row ; i++){
        for(unsigned long j = 0; j < m_column; j++){
            m_plateauData[i][j] = '0';
            m_plateauState[i][j] = false;
            m_plateauLockState[i][j] = false;
        }
    }
    fillTableau();
}

void Plateau::fillTableau()
{
    unsigned long count = 0, x = 0,y = 0;
    while (count < static_cast<unsigned long>(m_nb_bombe)){
        x = static_cast<unsigned long>(rand()%(static_cast<int>(m_row)-3)+2);
        y = static_cast<unsigned long>(rand()%(static_cast<int>(m_column)-3)+2);
        if (m_plateauData[x][y] != 'X'){count++;
            m_plateauData[x][y] = 'X';
            for(unsigned long i = x-1; i < x+2 ;i++){
                for(unsigned long j = y-1; j < y+2 ;j++){
                    if(m_plateauData[i][j] != 'X')
                        m_plateauData[i][j]++;
                }
            }
        }
    }
}

void Plateau::unlockLockCell(unsigned long row, unsigned long column)
{
    if(m_plateauLockState[row+1][column+1] == false && m_plateauState[row+1][column+1] == false)
        m_plateauLockState[row+1][column+1] = true;
    else if(m_plateauState[row+1][column+1] == false)
        m_plateauLockState[row+1][column+1] = false;
}


bool Plateau::Loose(unsigned long row, unsigned long column)
{
    if (m_plateauData[row+1][column+1] == 'X'){
        for(unsigned long i =0 ; i < m_row ; i++){
            for(unsigned long j = 0; j < m_column; j++){
                m_plateauState[i][j] = true;
            }
        }
         return true;
    }
    else {return false;}
}

bool Plateau::Win()
{
    for(unsigned long i =1 ; i < m_row-1 ; i++){
        for(unsigned long j = 1; j < m_column-1; j++){
            if(m_plateauState[i][j] == false and m_plateauData[i][j] != 'X')
                return false;
        }
    }
    for(unsigned long i =0 ; i < m_row ; i++){
        for(unsigned long j = 0; j < m_column; j++){
            m_plateauState[i][j] = true;
        }
    }
    return true;
}

void Plateau::showcell(unsigned long row, unsigned long column)
{
    unsigned long x = row + 1, y = column + 1;
    //int count = 10;
    if(m_plateauLockState[x][y] == false){
            if(m_plateauLockState[x][y] == false){m_plateauState[x][y] = true;}
            if(checkBomb(x,y)){
                propagationCell(x+1,y);
                propagationCell(x-1,y);
                propagationCell(x,y+1);
                propagationCell(x,y-1);
            }
    }
}

void Plateau::propagationCell(unsigned long row, unsigned long column)
{
    if(row>0 && row<m_row-1 && column>0 && column<m_column-1){
        if(checkBomb(row,column) && m_plateauState[row][column] == false)
        {
            m_plateauState[row][column] = true;
            propagationCell(row,column+1);
            propagationCell(row,column-1);
            propagationCell(row+1,column);
            propagationCell(row-1,column);
        }
        return;
    }
}

bool Plateau::checkBomb(unsigned long row, unsigned long column)
{
    if(row>0 && row<m_row-1 && column>0 && column<m_column-1){
        if(m_plateauData[row+1][column] == 'X'){return  false;}
        else if(m_plateauData[row-1][column] == 'X'){return  false;}
        else if(m_plateauData[row][column+1] == 'X'){return  false;}
        else if(m_plateauData[row][column-1] == 'X'){return  false;}
        else return true;
    }
    return true;
}

void Plateau::changeDimension(unsigned long row, unsigned long column, int bombe)
{
    m_row = row + 2;
    m_column = column + 2;
    m_nb_bombe = bombe;
    m_plateauData.resize(m_row,vector<char>(m_column));
    m_plateauState.resize(m_row,vector<bool>(m_column));
    m_plateauLockState.resize(m_row,vector<bool>(m_column));
}

vector<vector<char> > Plateau::getPlateau()
{
    vector<vector<char>> tab;
    tab.resize(m_row,vector<char>(m_column));
    for(unsigned long i = 1 ; i < m_row - 1 ; i++){
        for(unsigned long j = 1; j < m_column-1; j++){
            if (m_plateauState[i][j] == true /*|| m_plateauData[i][j] == 'X'*/)
                tab[i-1][j-1] = m_plateauData[i][j];
            else if (m_plateauState[i][j] == false and m_plateauLockState[i][j] == true)
                tab[i-1][j-1] = 'L';
            else tab[i-1][j-1] = ' ';
        }
    }
    return tab;
}


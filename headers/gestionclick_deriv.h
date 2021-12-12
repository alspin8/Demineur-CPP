#ifndef GESTIONCLICK_DERIV_H
#define GESTIONCLICK_DERIV_H

#include "gestionClick.h"


class GestionClick_deriv : public GestionClick
{
    //Q_OBJECT
public:
    GestionClick_deriv();
    void mousePressEvent(QMouseEvent *event);
//signals :
//    void emit_click(QString,int,int);
};

#endif // GESTIONCLICK_DERIV_H

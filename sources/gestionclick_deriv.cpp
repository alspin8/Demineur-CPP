#include "gestionclick_deriv.h"

GestionClick_deriv::GestionClick_deriv()
{

}

void GestionClick_deriv::mousePressEvent(QMouseEvent *event)
{
    GestionClick::mousePressEvent(event);
}

void GestionClick::mousePressEvent(QMouseEvent *event)
{
    emit GestionClick::emit_click((QString::number(event->button())),(event->x()),(event->y()));
}

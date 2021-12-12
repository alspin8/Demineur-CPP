#include "gestionClick.h"

GestionClick::GestionClick(QWidget *parent) : QTableView(parent)
{

}

void GestionClick::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << QString::number(event->x());
    //qDebug() << QString::number(event->y());
    emit emit_click(QString::number(event->button()),event->x(),event->y());
}




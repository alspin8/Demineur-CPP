#ifndef GESTIONCLICK_H
#define GESTIONCLICK_H

#include <QTableView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDebug>


class GestionClick : public QTableView
{
    Q_OBJECT
public:
    GestionClick(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *event)override;
signals:
    void emit_click(QString bp,int x,int y);
};

#endif // GESTIONCLICK_H

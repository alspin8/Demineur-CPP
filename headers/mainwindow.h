#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "plateau.h"
#include <vector>
#include <QMessageBox>
#include <QDebug>
#include "gestionClick.h"
#include <QObject>
#include <QDesktopWidget>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void display(unsigned long row, unsigned long column);
public slots:
    void click(QString bouton,int x,int y);
private slots:
    void on_Play_clicked();

    void on_rowSlider_valueChanged(int value);

    void on_columnSlider_valueChanged(int value);

    void on_bombeSlider_valueChanged(int value);

    void on_BP_QUITTER_clicked();

private:
    Ui::MainWindow *ui;
    unsigned long m_row = 3, m_column = 3;
    int m_nb_bombe = 1, x_corner, y_corner,m_height,m_width;
    bool move_state = true;
    Plateau m_p;
    QIcon m_bombe,m_bombe_m,m_cacher,m_0,m_1,m_2,m_3,m_4,m_5,m_6,m_7,m_8;
    QDesktopWidget screen;
    QRect surface_bureau = screen.screenGeometry();
protected:
    virtual void resizeEvent(QResizeEvent *event);
};
#endif // MAINWINDOW_H

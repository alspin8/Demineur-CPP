#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
    connect(ui->Table,&GestionClick::emit_click,this,&MainWindow::click);
    ui->Table->verticalHeader()->setVisible(false);
    ui->Table->horizontalHeader()->setVisible(false);
    ui->Table->setShowGrid(false);
    m_bombe.addFile(":/case_bombe.png");
    m_bombe_m.addFile(":/case_bombe_marked.png");
    m_cacher.addFile(":/case_cache.png");
    m_0.addFile(":/case_check0.png");
    m_1.addFile(":/case_check1.png");
    m_2.addFile(":/case_check2.png");
    m_3.addFile(":/case_check3.png");
    m_4.addFile(":/case_check4.png");
    m_5.addFile(":/case_check5.png");
    m_6.addFile(":/case_check6.png");
    m_7.addFile(":/case_check7.png");
    m_8.addFile(":/case_check8.png");
    ui->multiPage->setCurrentIndex(0);
    ui->rowSlider->setValue(9);
    ui->rowSlider->setMaximum(30);
    ui->columnSlider->setValue(9);
    ui->columnSlider->setMaximum(30);
    ui->bombeSlider->setValue(10);
    ui->bombeSlider->setMaximum(200);
    ui->Titre->setAlignment(Qt::AlignCenter);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label_2->setAlignment(Qt::AlignCenter);
    ui->label_3->setAlignment(Qt::AlignCenter);
    ui->rowAffichage->setAlignment(Qt::AlignCenter);
    ui->columnAffichage->setAlignment(Qt::AlignCenter);
    ui->bombeAffichage->setAlignment(Qt::AlignCenter);
    ui->rowAffichage->setStyleSheet("color : white");
    ui->columnAffichage->setStyleSheet("color : white");
    ui->bombeAffichage->setStyleSheet("color : white");
    ui->BP_QUITTER->setStyleSheet("color : white");
    ui->Play->setStyleSheet("color : white");
    ui->Titre->setStyleSheet("color : white");
    ui->label->setStyleSheet("color : white");
    ui->label_2->setStyleSheet("color : white");
    ui->label_3->setStyleSheet("color : white");
    ui->Interface->setStyleSheet("background-color: rgb(16, 70, 115)");
    this->setStyleSheet("background-color: rgb(16, 70, 115)");
    x_corner = surface_bureau.width()/2 - width()/2;
    y_corner = surface_bureau.height()/2 - height()/2;
    move(x_corner,y_corner);
    setMinimumSize(800,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::click(QString bouton, int x, int y)
{
   int row = x/((width()-36)/m_column), column = y/((height()-60)/m_row);
   if(bouton == "1"){
       //qDebug() << QString::number(row);
       //qDebug() << QString::number(column);
       //qDebug() << QString::number(ui->multiPage->height());
       //qDebug() << QString::number(ui->multiPage->width());
       m_p.showcell(static_cast<unsigned int>(column),static_cast<unsigned int>(row));
       display(m_row,m_column);
       if(m_p.Loose(static_cast<unsigned int>(column),static_cast<unsigned int>(row))){
           display(m_row,m_column);
           QMessageBox::information(this,"Resultat :","Vous avez perdu");
           ui->multiPage->setCurrentIndex(0);
           setMinimumSize(800,600);
           resize(800,600);
           x_corner = surface_bureau.width()/2 - 800/2;
           y_corner = surface_bureau.height()/2 - 600/2;
           move(x_corner,y_corner);
           move_state = true;
       }
       else if(m_p.Win()){
           display(m_row,m_column);
           QMessageBox::information(this,"Resultat :","Vous avez gagné");
           ui->multiPage->setCurrentIndex(0);
           setMinimumSize(800,600);
           resize(800,600);
           x_corner = surface_bureau.width()/2 - 800/2;
           y_corner = surface_bureau.height()/2 - 600/2;
           move(x_corner,y_corner);
           move_state = true;
       }
   }
   else{
       m_p.unlockLockCell(static_cast<unsigned int>(column),static_cast<unsigned int>(row));
       display(m_row,m_column);
   }
}

void MainWindow::display(unsigned long row, unsigned long column)
{
    if(ui->multiPage->currentIndex() != 0){
        if((m_row > 19 || m_column > 19) && (m_row <= 24 || m_column <= 24)){m_width = 1000;m_height = 1000;}
        else if(m_row > 24 || m_column > 24){m_width = 1300;m_height = 1000;}
        else {m_width = 800;m_height = 800;}
    }
    else{m_width = 800;m_height = 600;}
    setMinimumSize(m_width,m_height);
    if(move_state && ui->multiPage->currentIndex() != 0){
        x_corner = surface_bureau.width()/2 - m_width/2;
        y_corner = surface_bureau.height()/2 - m_height/2;
        move(x_corner,y_corner);
        move_state = false;
    }
    vector<vector<char>> tab(row, vector<char>(column));
    QIcon image;
    tab = m_p.getPlateau();
    QStandardItemModel *model = new QStandardItemModel(static_cast<int>(row), static_cast<int>(column),this);
    for (int i =0; i < static_cast<int>(row); i++) {
        for (int j =0; j < static_cast<int>(column);j++) {
            QStandardItem *item = new QStandardItem;
            switch (tab[static_cast<unsigned long>(i)][static_cast<unsigned long>(j)]) {
                case 'X' : image= m_bombe;
                        break;
                case 'L' : image = m_bombe_m;
                        break;
                case ' ' : image = m_cacher;
                        break;
                case '0' : image = m_0;
                        break;
                case '1' : image = m_1;
                        break;
                case '2' : image = m_2;
                        break;
                case '3' : image = m_3;
                        break;
                case '4' : image = m_4;
                        break;
                case '5' : image = m_5;
                        break;
                case '6' : image = m_6;
                        break;
                case '7' : image = m_7;
                        break;
                case '8' : image = m_8;
                        break;
            }
            QPixmap image1 = image.pixmap(QSize(75,75));           
            image1 = image1.scaled(width()/column,height()/row);
            item->setBackground(image1);
            model->setItem(i,j,item);
        }
    }
    ui->Table->setModel(model);
    for (int i =0; i < static_cast<int>(row); i++) {
                ui->Table->setRowHeight(i,(height()-60)/row);
                ui->Table->setColumnWidth(i,(width()-36)/column);
            }
}

void MainWindow::on_Play_clicked()
{
    if(static_cast<unsigned long>(m_nb_bombe) >= (m_row*m_column)/2)
        QMessageBox::warning(this,"WARNING","Il y a trop de bombe");
    else{
        ui->multiPage->setCurrentIndex(1);
        m_p.changeDimension(m_row,m_column,m_nb_bombe);
        m_p.initPlateau();
        display(m_row,m_column);
    }
}

void MainWindow::on_rowSlider_valueChanged(int value)
{
    ui->rowAffichage->setText(QString::number(value));
    m_row = static_cast<unsigned long>(value);
    //qDebug() << QString::number(m_row);
}

void MainWindow::on_columnSlider_valueChanged(int value)
{
    ui->columnAffichage->setText(QString::number(value));
    m_column = static_cast<unsigned long>(value);
    //qDebug() << QString::number(m_column);
}

void MainWindow::on_bombeSlider_valueChanged(int value)
{
    ui->bombeAffichage->setText(QString::number(value));
    m_nb_bombe = value;
    //qDebug() << QString::number(m_nb_bombe);
}

void MainWindow::on_BP_QUITTER_clicked()
{
    close();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    display(m_row,m_column);
}

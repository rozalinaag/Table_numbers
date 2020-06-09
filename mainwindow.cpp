#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QMessageBox>
#include <QTimer>
#include <time.h>
#include <QDebug>

int kolvo_color=0; //для выбора цвета
int summa=0; //для подсчета суммы ячеек выделенных

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //подключение к таблице
    ui->tableWidget->setRowCount(10); //метод setRowCount устанавливалет количество строк
    ui->tableWidget->setColumnCount(10); //метод setColumnCount устаналивает количество столбцов

    //заполнение имен столбцов и строк Vertical это строку
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"a"<<"b"<<"c"<<"d"<<"e"<<"f"<<"g"<<"k"<<"l"<<"m"); //бинарный сдвиг влево
    //ui->tableWidget->setVerticalHeaderLabels(QStringList()<<"a"<<"b"<<"c"<<"d");

    //заполнение таблицы
    srand(time(NULL));

    for (int i=0;i<ui->tableWidget->rowCount();i++) //метод rowCount возвращает количество строк
        for (int j=0;j<ui->tableWidget->columnCount();j++) //columnCount возвращает количетво столбцов
        {
            //создали элемент
            QTableWidgetItem *itm= new QTableWidgetItem(tr("%1").arg(rand()%100)); //метод (tr("%1").arg(count)) пишет номер в ячейку


            //itm->setTextColor(Qt::white);

            ui->tableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Stretch); //делается под ширину окна
            ui->tableWidget->verticalHeader()->setSectionResizeMode(i,QHeaderView::Stretch); //делается под высоту окна
            //теперь его надо кинуть в таблицу
            ui->tableWidget->setItem(i,j,itm);
        }


    //вызываем таймер
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ActionTimer()));
    timer->start(1000);
}

//для Таймера
void MainWindow::ActionTimer()
{
    srand(time(NULL)); //для рандома, стандартная функция
    int i=rand()%(ui->tableWidget->rowCount()); //рандомное число
    int j=rand()%(ui->tableWidget->columnCount());

    QTableWidgetItem *itm= new QTableWidgetItem("0");

    //для разных цветов
    if (kolvo_color%2==0)
        itm->setBackground(Qt::green);
    else if (kolvo_color%3==0)
        itm->setBackground(Qt::red);
    else if (kolvo_color%5==0)
        itm->setBackground(Qt::yellow);
    else if (kolvo_color%7==0)
            itm->setBackground(Qt::blue);
    else
        itm->setBackground(Qt::gray);

    kolvo_color+=1;

    ui->tableWidget->setItem(i,j,itm); //установка нового значения
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QTableWidgetItem *itm= ui->tableWidget->currentItem();
    //QMessageBox::information(this,"Info",itm->text()); //возвращает текст ячейки на которую наводишь itm->text()
    QString strok= ui->tableWidget->model()->data(ui->tableWidget->currentIndex()).toString();
    bool ok;
    int numb = strok.toInt(&ok, 10);
    QString ball;
    if (numb%2==0)
    {
        summa+=numb;
        ball.setNum(summa);
        ui->statusBar->showMessage("Ваши баллы: "+ball);

        if (summa>300)
        {
            QMessageBox::information(this,"Info","Вы выиграли!\nБАЛЛЫ: " +ball);
        }

    }
    else
    {
        summa-=numb;
        ball.setNum(summa);
        ui->statusBar->showMessage("Ваши баллы: "+ball);
    }
}

void MainWindow::on_pushButton_itog_clicked()
{
    QTableWidgetItem *itm= ui->tableWidget->currentItem();

    QString strok= ui->tableWidget->model()->data(ui->tableWidget->currentIndex()).toString();
    bool ok;
    int numb = strok.toInt(&ok, 10);

    QString ball;
    if (numb%2!=0)
    {
        summa+=numb;
        ball.setNum(summa);
        ui->statusBar->showMessage("Ваши баллы: "+ball);

        if (summa>300)
        {
            QMessageBox::information(this,"Info","Вы выиграли!\nБАЛЛЫ: " +ball);
        }

    }
    else
    {
        summa-=numb;
        ball.setNum(summa);
        ui->statusBar->showMessage("Ваши баллы: "+ball);
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <math.h>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Draw_Cell()
{
    //graphicsViewにScene_を設定。
    ui->graphicsView->setScene(&Scene_);

    // get input
    const int dataAddr = 2;
    unsigned int inData[64+dataAddr] = {8,8};
    // input data dummy
    {
        for(int n=0;n<64; n++){
            inData[dataAddr+n] = (n)<<2;
            //inData[dataAddr+n] = (30- ui->horizontalSlider->value())*12;
        }
    }

    // set cell count
    int row = inData[0];
    int column = inData[1];

    // fix input
    {
        unsigned int tempData;
        unsigned int minLimit = ui->horizontalSlider->value()<<2;
        unsigned int maxLimit = minLimit + (30<<2);

        for(int n=0; n<(row*column); n++){
            tempData = inData[dataAddr+n];
            tempData = std::max(std::min(tempData , maxLimit) , minLimit);
            inData[dataAddr+n] = 240 -( (tempData - minLimit)<<1);
        }
    }


    // get drawBase size
    QRect baseRect(ui->graphicsView->rect());

    // create color cell
    {
        QColor col;
        QPoint cellPoint(0,0);
        QSize cellSize(baseRect.width()/column, baseRect.height()/row);
        QRect cellRect(cellPoint,cellSize);
        QPoint dataPos(0,0);

        for(int i=0;i<row; i++){
            // inside inData set Ypostion
            dataPos.setY(row*i);
            // fix draw YPosition
            cellPoint.setY(i * cellSize.height());

            for(int j=0;j<column; j++){
                // inside inData set Xpostion
                dataPos.setX(j);
                // fix draw XPosition
                cellPoint.setX(j * cellSize.width());
                // set draw Position
                cellRect.moveTopLeft(cellPoint);

                // inData Changed Color Data
                int colH = inData[dataAddr+dataPos.x() + dataPos.y()];
                // set ColorData
                col.setHsv(colH,255,255);

                //Scene add cell
                Scene_.addRect(cellRect, col, col);

            }
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    this->Draw_Cell();
}

void MainWindow::on_pushButton_2_clicked()
{

    static QTimer *timer = new QTimer(this);
    timer->stop();
    if(ui->pushButton_2->text() != "Timer Stop"){
        timer->setInterval(500);
        timer->setSingleShot(false);
        connect(timer,SIGNAL(timeout()),SLOT(Draw_Cell()));
        timer->start();

        ui->pushButton_2->setText("Timer Stop");
    }else{
        ui->pushButton_2->setText("Timer Start");
    }

}

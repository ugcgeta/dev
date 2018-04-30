#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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

void MainWindow::on_pushButton_clicked()
{
    cv::Mat src, dst;
    cv::VideoCapture cap(0);
    if(!cap.isOpened()){
        return;
    }
    cap >> src;
    cv::cvtColor(src, dst, CV_RGBA2BGR); //使用しているカメラは32bitだった！
    QImage img(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);

    //graphicsViewにScene_を設定。
    ui->graphicsView->setScene(&Scene_);
    //Scene_をクリア
    Scene_.clear();
    //Scene_に登録するpixmapを作成
    QPixmap pixmap=QPixmap::fromImage(img);
    //Scene_に画像を登録
    Scene_.addPixmap(pixmap);
}

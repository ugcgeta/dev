#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void Draw_Cell();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene Scene_;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<Filter.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include<QScreen>
#include <QImage>
#include "gaussion.h"
#include "tuxiang.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    char* file_copy();
    void big(int code);

private slots:
    void OpenImg();
    void Save();
    void Back();

    void GaussionImg();
    void Flipupdown();
    void Flipleftright();

    void lightup();
    void lightdown();
    void Cut();

    void rotate();
    void Cat();
    void warm();
    void cold();
    void smoothMedianRGB();



private:
    Ui::MainWindow *ui;
    Image operational_img;
    QString OpenFile;
    QString CopyFile;
};

#endif // MAINWINDOW_H

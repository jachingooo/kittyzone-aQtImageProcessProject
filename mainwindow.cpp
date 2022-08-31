#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Filter.h"
#include "gaussion.h"
#include "SharpenFilter.h"
#include <QDebug>
#include <iostream>
#include <cstring>
#include <QInputDialog>
#include <QFormLayout>
#include <QSpinBox>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionsave->setDisabled(true);
    ui->button_back->setVisible(false);

    connect(ui->actionopen, SIGNAL(triggered(bool)), this, SLOT(OpenImg()));
    connect(ui->actionsave, SIGNAL(triggered(bool)), this, SLOT(Save()));
    connect(ui->button_guassion, SIGNAL(clicked(bool)), this, SLOT(GaussionImg()));
    connect(ui->button_back, SIGNAL(clicked(bool)), this, SLOT(Back()));
    connect(ui->button_flipupdown, SIGNAL(clicked(bool)), this, SLOT(Flipupdown()));
    connect(ui->button_flipleftright, SIGNAL(clicked(bool)), this, SLOT(Flipleftright()));
    connect(ui->button_lightup, SIGNAL(clicked(bool)), this, SLOT(lightup()));
    connect(ui->button_lightdown, SIGNAL(clicked(bool)), this, SLOT(lightdown()));
    connect(ui->button_cut,SIGNAL(clicked(bool)),this,SLOT(Cut()));
    connect(ui->rotate,SIGNAL(clicked(bool)),this,SLOT(rotate()));
    connect(ui->button_cat,SIGNAL(clicked(bool)),this,SLOT(Cat()));
    connect(ui->button_warm,SIGNAL(clicked(bool)),this,SLOT(warm()));
    connect(ui->button_cold,SIGNAL(clicked(bool)),this,SLOT(cold()));
    connect(ui->button_big,SIGNAL(clicked(bool)),this,SLOT(big()));
    connect(ui->button_media,SIGNAL(clicked(bool)),this,SLOT(smoothMedianRGB()));
    ui->label->setFrameShape(QFrame::Box);
    ui->label_2->setFrameShape(QFrame::Box);
}

void MainWindow::OpenImg()
{
    //打开文件夹中的图片文件
    ui->button_back->setVisible(true);
    ui->actionsave->setDisabled(false);
    OpenFile = QFileDialog::getOpenFileName(this,
                                              tr("Choose Image"),
                                              "",
                                              "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    if( OpenFile != "" )
    {
        CopyFile = QCoreApplication::applicationDirPath()+"/kk/coypfile.bmp";
        operational_img.ReadBMP(OpenFile.toLocal8Bit().constData());

        QImage* img_seen = operational_img.toQImage(operational_img);
        ui->label->setPixmap(QPixmap::fromImage(*img_seen));
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label_2->setPixmap(QPixmap::fromImage(*img_seen));
        ui->label_2->setAlignment(Qt::AlignCenter);
     }

    //显示所示图片的路径
    /*
    QFileInfo OpenFileInfo;
    OpenFileInfo = QFileInfo(OpenFile);
    OpenFilePath = OpenFileInfo.filePath();
    */
}


void MainWindow::Save()
{
    //另存为
    QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    ui->label->pixmap()->toImage().save(filename);
}

void MainWindow::GaussionImg()
{
    Filter* filter = new Gaussion();
    operational_img = filter->FunctionFilter(operational_img);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::Back()
{
    operational_img.ReadBMP(OpenFile.toLocal8Bit().constData());

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::Flipupdown()
{
    operational_img.Flip(1);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::Flipleftright()
{
    operational_img.Flip(0);
    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lightup()
{
    operational_img.Add(50);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::lightdown()
{
    operational_img.Add(-50);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::Cut()
{

    QDialog dialog(this);
    dialog.setWindowTitle("print your size");
    dialog.resize(250,100);
    QFormLayout form(&dialog);

    QString _x1 = QString("x1: ");
    QSpinBox *spinbox1 = new QSpinBox(&dialog);
    spinbox1->setMaximum(1000);
    spinbox1->setMinimum(-1000);
    form.addRow(_x1, spinbox1);

    QString _y1 = QString("y1: ");
    QSpinBox *spinbox2 = new QSpinBox(&dialog);
    spinbox2->setMaximum(1000);
    spinbox2->setMinimum(-1000);
    form.addRow(_y1, spinbox2);

    QString _x2 = QString("x2: ");
    QSpinBox *spinbox3 = new QSpinBox(&dialog);
    spinbox3->setMaximum(1000);
    spinbox3->setMinimum(-1000);
    form.addRow(_x2, spinbox3);

    QString _y2 = QString("y2: ");
    QSpinBox *spinbox4 = new QSpinBox(&dialog);
    spinbox4->setMaximum(1000);
    spinbox4->setMinimum(-1000);
    form.addRow(_y2, spinbox4);

    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Process when OK button is clicked
    if (dialog.exec() == QDialog::Accepted) {
        // Do something here
        int x1 = spinbox1->text().toInt();
        int y1 = spinbox2->text().toInt();
        int x2 = spinbox3->text().toInt();
        int y2 = spinbox4->text().toInt();
        qDebug()<<x1;
        qDebug()<<x2;

        operational_img.Cut(x1,y1,x2,y2);

        //显示
        QImage* img_seen = operational_img.toQImage(operational_img);
        ui->label->setPixmap(QPixmap::fromImage(*img_seen));
        ui->label->setAlignment(Qt::AlignCenter);
    }
}

void MainWindow::rotate()
{
    QInputDialog* input = new QInputDialog(this);
    bool isOK;
    int degree = QInputDialog::getText(NULL, "rotate ankle",
                                         "90 integer multiiples",
                                         QLineEdit::Normal,
                                         "90",
                                         &isOK).toInt();
    operational_img.Rotate(degree);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}


void MainWindow::Cat()
{
    QString OpenFile2 = QFileDialog::getOpenFileName(this,
                                              tr("Choose splice Image"),
                                              "",
                                              "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
    Image n2;
    n2.ReadBMP(OpenFile2.toLocal8Bit().constData());
    operational_img.Cat(n2,1);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);

}

void MainWindow::warm()
{
    operational_img.Warm(15);

    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}

void MainWindow::cold()
{

    operational_img.Cold(15);
    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);

}

void MainWindow::smoothMedianRGB(){
   QImage* img_seen = operational_img.SmoothMedianRGB(operational_img);
   ui->label->setPixmap(QPixmap::fromImage(*img_seen));
   ui->label->setAlignment(Qt::AlignCenter);
}


void MainWindow::big(int code)
{
    operational_img.Big(0);
    //显示
    QImage* img_seen = operational_img.toQImage(operational_img);
    ui->label->setPixmap(QPixmap::fromImage(*img_seen));
    ui->label->setAlignment(Qt::AlignCenter);
}


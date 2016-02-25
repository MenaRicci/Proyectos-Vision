#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Acction=-1;

    cap = new VideoCapture(0);
    if(!cap->isOpened())
        cap = new VideoCapture(1);
    capture = true;
    showColorImage = false;
    winSelected = false;
    cap->set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT, 240);
    imgS = new QImage(320,240, QImage::Format_RGB888);
    visorS = new RCDraw(320,240, imgS, ui->imageFrameS);
    imgD = new QImage(320,240, QImage::Format_RGB888);
    visorD = new RCDraw(320,240, imgD, ui->imageFrameD);

    colorImage.create(240,320,CV_8UC3);
    grayImage.create(240,320,CV_8UC1);
    destColorImage.create(240,320,CV_8UC3);
    destGrayImage.create(240,320,CV_8UC1);
    gray2ColorImage.create(240,320,CV_8UC3);
    destGray2ColorImage.create(240,320,CV_8UC3);

    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    connect(ui->captureButton,SIGNAL(clicked(bool)),this,SLOT(start_stop_capture(bool)));
    connect(ui->colorButton,SIGNAL(clicked(bool)),this,SLOT(change_color_gray(bool)));
    connect(visorS,SIGNAL(windowSelected(QPointF, int, int)),this,SLOT(selectWindow(QPointF, int, int)));
    connect(visorS,SIGNAL(pressEvent()),this,SLOT(deselectWindow()));
    connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(load_Image()));
    connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(save_Image()));
    //Connect FilterDialog
    connect(ui->kernelButton,SIGNAL(clicked()),this,SLOT(abrir_Filter()));
    connect(ui_Filter.okButton,SIGNAL(clicked()),this,SLOT(ok_filter_cerrar()));
    //Connect PixelDialog
    connect(ui->pixelTButton,SIGNAL(clicked()),this,SLOT(abrirPixel()));
    connect(ui_pixel.okButton,SIGNAL(clicked()),this,SLOT(ok_pixel_cerrar()));
    //Connect OperDialog
    connect(ui->operOrderButton,SIGNAL(clicked()),this,SLOT(abrirOperOrder()));
    connect(ui_Oper.okButton,SIGNAL(clicked()),this,SLOT(ok_oper_cerrar()));

    connect(ui->operationComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(obtener_accion(int)));
    timer.start(60);


}


MainWindow::~MainWindow()
{
    delete ui;
    delete cap;
    delete visorS;
    delete visorD;
    delete imgS;
    delete imgD;

}


void MainWindow::compute()
{

    if(capture && cap->isOpened())
    {
        *cap >> colorImage;

        cvtColor(colorImage, grayImage, CV_BGR2GRAY);
        cvtColor(colorImage, colorImage, CV_BGR2RGB);

    }

    if(Acction==1){
        thresholding();
    }
    if(Acction==3){
        SuavizadoGaussiano();
    }
    if(Acction==4){
        SuavizadoMediana();
    }
    if(Acction==9){
        if(ui_Oper.firstOperCheckBox->isChecked()==true){
            qDebug()<<"esta bien";
        }

    }
    if(showColorImage)
    {
        memcpy(imgS->bits(), colorImage.data , 320*240*3*sizeof(uchar));
        memcpy(imgD->bits(), destColorImage.data , 320*240*3*sizeof(uchar));
    }
    else
    {
        cvtColor(grayImage,gray2ColorImage, CV_GRAY2RGB);
        cvtColor(destGrayImage,destGray2ColorImage, CV_GRAY2RGB);
        memcpy(imgS->bits(), gray2ColorImage.data , 320*240*3*sizeof(uchar));
        memcpy(imgD->bits(), destGray2ColorImage.data , 320*240*3*sizeof(uchar));

    }

    if(winSelected)
    {
        visorS->drawSquare(QPointF(imageWindow.x+imageWindow.width/2, imageWindow.y+imageWindow.height/2), imageWindow.width,imageWindow.height, Qt::green );
    }
    visorS->update();
    visorD->update();

}
void MainWindow::save_Image()
{
 savebool=true;
bool test=capture;
capture=false;
 //ui->textEdit->setText("Save Image");

 QString filename=QFileDialog::getSaveFileName(0,"Save file",QDir::currentPath(),
"JPG files (*.jpg);;BMP files (*.bmp);;PNG files (*.png);;All files (*.*)",
     new QString("Text files (*.txt)"));

 if(!filename.isEmpty()){

 if(showColorImage){
    cvtColor(colorImage, colorImage, CV_BGR2RGB); //
    imwrite(filename.toStdString(), colorImage);
 }
 else{
    imwrite(filename.toStdString(), grayImage);
 }
}
capture=test;

}
void MainWindow::load_Image()
{

loadbool=true;
//ui->textEdit->setText("Load Image");

QString filters("JPG files (*.jpg);;BMP files (*.bmp);;PNG files (*.png);;All files (*.*)");
QString defaultFilter("All files (*.*)");

QFileDialog fileDialog(0, "Open file", "/home/guille/Escritorio", filters);
fileDialog.selectNameFilter(defaultFilter);
QStringList fileNames;
if (fileDialog.exec())
    fileNames = fileDialog.selectedFiles();

QString File=fileNames.front();
fileNames.pop_front();
colorImage=imread(File.toStdString());

cv::resize(colorImage,colorImage, Size(320,240),0,0,INTER_LINEAR);

cvtColor(colorImage, grayImage, CV_BGR2GRAY);
cvtColor(colorImage,colorImage, CV_BGR2RGB);

start_stop_capture(false);
}
void MainWindow::start_stop_capture(bool start)
{
    if(start)
    {
        ui->captureButton->setText("Stop capture");
        capture = true;
    }
    else
    {
        ui->captureButton->setText("Start capture");
        capture = false;
    }
}
void MainWindow::change_color_gray(bool color)
{
    if(color)
    {
        ui->colorButton->setText("Gray image");
        showColorImage = true;
    }
    else
    {
        ui->colorButton->setText("Color image");
        showColorImage = false;
    }
}
void MainWindow::selectWindow(QPointF p, int w, int h)
{
    QPointF pEnd;
    if(w>0 && h>0)
    {
        imageWindow.x = p.x()-w/2;
        if(imageWindow.x<0)
            imageWindow.x = 0;
        imageWindow.y = p.y()-h/2;
        if(imageWindow.y<0)
            imageWindow.y = 0;
        pEnd.setX(p.x()+w/2);
        if(pEnd.x()>=320)
            pEnd.setX(319);
        pEnd.setY(p.y()+h/2);
        if(pEnd.y()>=240)
            pEnd.setY(239);
        imageWindow.width = pEnd.x()-imageWindow.x;
        imageWindow.height = pEnd.y()-imageWindow.y;

        winSelected = true;
    }
}
void MainWindow::deselectWindow()
{
    winSelected = false;
}

void MainWindow::abrir_Filter(){
ui_Filter.show();

}

void MainWindow::abrirOperOrder(){
ui_Oper.show();
}
void MainWindow::abrirPixel(){
ui_pixel.show();
}


void MainWindow::ok_filter_cerrar(){
    ui_Filter.close();
}

void MainWindow::ok_pixel_cerrar(){
    ui_pixel.close();
}

void MainWindow::ok_oper_cerrar(){
    ui_Oper.close();
}

void MainWindow::obtener_accion(int indice){
    Acction=indice;
}

void MainWindow::thresholding(){
    double p=(double)ui->thresholdSpinBox->value();

    threshold(grayImage,destGrayImage,p,255,THRESH_BINARY);
}



void MainWindow::SuavizadoGaussiano(){
    double w=(double)ui->gaussWidthBox->value();
    double sigX=w/5;

    GaussianBlur(grayImage,destGrayImage,Size(0,0),sigX);
}

void MainWindow::SuavizadoMediana(){

    medianBlur(grayImage,destGrayImage,9);
}





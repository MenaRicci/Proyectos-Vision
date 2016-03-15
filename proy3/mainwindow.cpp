#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numFoto=0;
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
    Black_Color_Image.create(240,320,CV_8UC3);
    Black_Gray_Image.create(240,320,CV_8UC1);

    destGrayImage.create(240,320,CV_8UC1);
    gray2ColorImage.create(240,320,CV_8UC3);
    destGray2ColorImage.create(240,320,CV_8UC3);
    conjuntoImagen1.insert(conjuntoImagen1.begin(),15,Black_Gray_Image);

    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    connect(ui->captureButton,SIGNAL(clicked(bool)),this,SLOT(start_stop_capture(bool)));
    connect(ui->colorButton,SIGNAL(clicked(bool)),this,SLOT(change_color_gray(bool)));
    connect(ui->AddObjIma,SIGNAL(clicked()),this,SLOT(set_Image()));
    connect(ui->DelObjIma,SIGNAL(clicked()),this,SLOT(deleteImageInSet()));
    connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),this,SLOT(changeImage()));
    connect(ui->SelectComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(changeImage()));

    connect(visorS,SIGNAL(windowSelected(QPointF, int, int)),this,SLOT(selectWindow(QPointF, int, int)));
    connect(visorS,SIGNAL(pressEvent()),this,SLOT(deselectWindow()));
    ListaObjetosImagenes.resize(3);
    //listaContadores.resize(3);
    listaContadores.insert(listaContadores.begin(),3,0);
    qDebug()<<listaContadores[2];
    timer.start(60);
    orb=ORB();

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
    changeImage();
    if(showColorImage)
    {
        memcpy(imgS->bits(), colorImage.data , 320*240*3*sizeof(uchar));
        memcpy(imgD->bits(), destColorImage.data , 320*240*3*sizeof(uchar));
    }
    else
    {
        cvtColor(grayImage,gray2ColorImage, CV_GRAY2RGB);
        cvtColor(destGrayImage,destGray2ColorImage, CV_GRAY2RGB);
        memcpy(imgS->bits(), gray2ColorImage.data , 320*240*3*sizeof(uchar)); //Pasa el contenido a VisorS
        memcpy(imgD->bits(), destGray2ColorImage.data , 320*240*3*sizeof(uchar));//Pasa el contenido a VisorD

    }
    if(winSelected)
    {
        visorS->drawSquare(QPointF(imageWindow.x+imageWindow.width/2, imageWindow.y+imageWindow.height/2), imageWindow.width,imageWindow.height, Qt::green );

    }
    visorS->update();
    visorD->update();

}
void MainWindow::start_stop_capture(bool start)
{
    if(start)
    {
        ui->captureButton->setText("Pulsar para Parar");
        capture=true;
            }
    else
    {
        ui->captureButton->setText("Pulsar Para Capturar");
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
void MainWindow::set_Image()
{
 if(winSelected){
    // ui->textEdit->setText("Hola");
//colorImage.copyTo();

   //  destColorImage.resize(colorImage.rowRange(imageWindow.x,imageWindow.width).colRange(imageWindow.y,imageWindow.height));


    int centro_wdt_image=imageWindow.width/2;
    int centro_hgt_image=imageWindow.height/2;

    int origen_x =160-centro_wdt_image;
    int origen_y =120-centro_hgt_image;


    int fin_x =origen_x+imageWindow.width;
    int fin_y =origen_y+imageWindow.height;


    destColorImage=Black_Color_Image.clone();
    destGrayImage=Black_Gray_Image.clone();

if(showColorImage){
    Mat cuadroImagen=colorImage.colRange(imageWindow.x,imageWindow.x+imageWindow.width).rowRange(imageWindow.y,imageWindow.y+imageWindow.height);

    cuadroImagen.copyTo(destColorImage.colRange(origen_x,fin_x).rowRange(origen_y,fin_y));
}
else{
    Mat cuadroImagen=grayImage.colRange(imageWindow.x,imageWindow.x+imageWindow.width).rowRange(imageWindow.y,imageWindow.y+imageWindow.height);

        cuadroImagen.copyTo(destGrayImage.colRange(origen_x,fin_x).rowRange(origen_y,fin_y));
}
   // cuadroImagen.copyTo(destGrayImage.colRange(origen_x,fin_x).rowRange(origen_y,fin_y));
 }

 else{
     destColorImage=colorImage.clone();
     destGrayImage=grayImage.clone();
 }
 saveImageInSet();
}
void MainWindow::saveImageInSet(){
    Mat Imagen;
    Imagen=destGrayImage.clone();
    int objeto=ui->SelectComboBox->currentIndex();
    int cont=listaContadores[objeto];
    if(cont<5 && winSelected){
        ListaObjetosImagenes[objeto].push_back(Imagen);
        listaContadores[objeto]++;
    }
}

void MainWindow::changeImage(){
     Mat Image;
     //qDebug()<<"Num"<<pos;
    int posicion= ui->horizontalSlider->value();
    int objeto = ui->SelectComboBox->currentIndex();
    int size_objeto=ListaObjetosImagenes[objeto].size();
    if(!ListaObjetosImagenes[objeto].empty() && posicion<=size_objeto){
        Image=ListaObjetosImagenes[objeto][posicion-1];
        destGrayImage=Image.clone();
    }else
        destGrayImage=Black_Gray_Image.clone();

}

void MainWindow::deleteImageInSet(){

    int objeto=ui->SelectComboBox->currentIndex();
    int posicion=ui->horizontalSlider->value();
    int cont=listaContadores[objeto];
    if(cont>0 && (posicion<=cont)){
      ListaObjetosImagenes[objeto].erase(ListaObjetosImagenes[objeto].begin()+posicion-1);
      listaContadores[objeto]--;

    }
}

void MainWindow::Match_ORB(){

    orb.detect(grayImage,ListaPuntosOrigen);
    orb.compute(grayImage,ListaPuntosOrigen,descritorOrigen);
    //Comprobar si se ha modificado la lista de imagenes de un objeto
    for (int i = 0; i < ui->SelectComboBox->count() ; ++i) {
        for (int j = 0; j < listaContadores[i] ; ++j) {
            std::vector<KeyPoint> puntos;
            orb.detect(ListaObjetosImagenes[i][j],puntos);
            ListaPuntosImagenes[i][j]=puntos;
            Mat descriptor;
            orb.compute(ListaObjetosImagenes[i][j],puntos,descriptor);
            listaDescriptores[i][j]=descriptor.clone();
        }
    }



}

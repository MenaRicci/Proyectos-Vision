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
    ImagenRegiones.create(240,320,CV_32SC1);
    ImagenBordes.create(240,320,CV_8UC1);


    ImagenRegiones.setTo(-1);


    destGrayImage.create(240,320,CV_8UC1);
    gray2ColorImage.create(240,320,CV_8UC3);
    destGray2ColorImage.create(240,320,CV_8UC3);

    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    connect(ui->captureButton,SIGNAL(clicked(bool)),this,SLOT(start_stop_capture(bool)));
    connect(ui->colorButton,SIGNAL(clicked(bool)),this,SLOT(change_color_gray(bool)));
    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(load_Image()));

    clicked=true;

    connect(visorS,SIGNAL(windowSelected(QPointF, int, int)),this,SLOT(selectWindow(QPointF, int, int)));
    connect(visorS,SIGNAL(pressEvent()),this,SLOT(deselectWindow()));
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



if(clicked){
    Canny(grayImage,ImagenBordes);
    Segmentacion();
    PuntosNegros();
    PintarSegmentado(destGrayImage);
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
void MainWindow::load_Image()
{
    clicked=false;
capture=false;
ui->captureButton->setText("Pulsar Para Capturar");
loadbool=true;
//ui->textEdit->setText("Load Image");

QString filters("JPG files (*.jpg);;BMP files (*.bmp);;PNG files (*.png);;All files (*.*)");
QString defaultFilter("All files (*.*)");

QFileDialog fileDialog(0, "Open file", "/home/guille/Escritorio", filters);
fileDialog.selectNameFilter(defaultFilter);
QStringList fileNames;
if (fileDialog.exec())
    fileNames = fileDialog.selectedFiles();


if(fileNames.size()>0){
    QString File=fileNames.front();
    fileNames.pop_front();
    colorImage=imread(File.toStdString());

    cv::resize(colorImage,colorImage, Size(320,240),0,0,INTER_LINEAR);

    cvtColor(colorImage, grayImage, CV_BGR2GRAY);
    cvtColor(colorImage,colorImage, CV_BGR2RGB);

    start_stop_capture(false);
    }
clicked=true;
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

void MainWindow::Canny(Mat Img_Source, Mat Img_Dest){

    cv::Canny(Img_Source,Img_Dest,30.0, 120.0);


}


/**
 * En la ImagenRegiones si el punto no ha visitado tendra el valor -1
 * Si ha sido visitado y no pertence a region, tendra el valor -2
 * Si ha sido visitado y pertenece a la region del punto inicial, obtendra el valor pasado como parametro (region)
 *
 *
 * @brief MainWindow::AnalisisRegion
 * @param pInicial
 * @param region
 */
void MainWindow::AnalisisRegion(Point pInicial,int region,STRegion &aux){

    std::vector<Point> Lista;
    Point Act, Nuevo;
    int i=0;

    int value_grey=grayImage.at<uchar>(pInicial.y,pInicial.x);
    int grey_act;

    Lista.push_back(pInicial);
    int size=Lista.size();
    while(i<size){
        Act=Lista[i];
        i++;
        if(Act.x>=0 && Act.x<320 && Act.y>=0 && Act.y < 240 && ImagenRegiones.at<int>(Act.y,Act.x)==-1){
                grey_act=grayImage.at<uchar>(Act.y,Act.x);
                if(abs(grey_act-value_grey)<20){
                    ImagenRegiones.at<int>(Act.y,Act.x)=region;
                    aux.numP++;
                    if(ImagenBordes.at<uchar>(Act.y,Act.y)==0){
                        Nuevo.x=Act.x;
                        Nuevo.y=Act.y-1;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x+1;
                        Nuevo.y=Act.y;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x;
                        Nuevo.y=Act.y+1;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x-1;
                        Nuevo.y=Act.y;
                        Lista.push_back(Nuevo);

                    }else{
                        aux.ListaFrontera.push_back(Act);
                    }
                }

        }
        size=Lista.size();
    }
    aux.numP--;
    Lista.clear();
}

void MainWindow::AnalisisRegionEstadistico(Point pInicial, int region, STRegion &aux){

    std::vector<Point> Lista;
    Point Act, Nuevo;
    int i=0;
    float media,varianza,mediaN,varianzaN;
    int value_grey=grayImage.at<uchar>(pInicial.y,pInicial.x);
    int grey_act;

    Lista.push_back(pInicial);

    media=value_grey;
    varianza=0;

    int size=Lista.size();
    while(i<size){
        Act=Lista[i];
        i++;
        if(Act.x>=0 && Act.x<320 && Act.y>=0 && Act.y < 240 && ImagenRegiones.at<int>(Act.y,Act.x)==-1){
            grey_act=grayImage.at<uchar>(Act.y,Act.x);
            mediaN=(aux.numP*media+grey_act)/(aux.numP+1);
            varianzaN=(aux.numP*varianza + (grey_act-media)*(grey_act-mediaN))/(aux.numP+1);
                if(varianzaN<1){//------------FIJAR UMBRAL-------------------------
                    media=mediaN;
                    varianza=varianzaN;
                    ImagenRegiones.at<int>(Act.y,Act.x)=region;
                    aux.numP++;
                    if(ImagenBordes.at<uchar>(Act.y,Act.y)==0){
                        Nuevo.x=Act.x;
                        Nuevo.y=Act.y-1;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x+1;
                        Nuevo.y=Act.y;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x;
                        Nuevo.y=Act.y+1;
                        Lista.push_back(Nuevo);

                        Nuevo.x=Act.x-1;
                        Nuevo.y=Act.y;
                        Lista.push_back(Nuevo);

                    }else{
                        aux.ListaFrontera.push_back(Act);
                    }
                }

        }
        size=Lista.size();
    }

    Lista.clear();
    aux.numP--;

}

void MainWindow::Segmentacion(){
    Point p;
    int contRegion=0;
    STRegion aux;
    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            if(ImagenRegiones.at<int>(i,j)==-1){
                aux.id=contRegion;
                p.x=j;
                p.y=i;
                aux.pOri=p;
                aux.numP=1;
                if(!ui->Check_Statistics->isChecked())
                    AnalisisRegion(p,contRegion,aux);
                else
                    AnalisisRegionEstadistico(p,contRegion,aux);
                aux.grey=grayImage.at<uchar>(p.y,p.x);
                ListaRegiones.push_back(aux);
                contRegion++;
            }
        }
    }
}

int MainWindow::RegionAfin(Point p){
    int grey_act,greyN,greyNE,greyE,greySE,greyS,greySO,greyO,greyNO;
    grey_act=grayImage.at<uchar>(p.y,p.x);
    int id=0,aux,menor=grey_act;
    if(p.y-1>=0){
        greyN=grayImage.at<uchar>(p.y-1,p.x);
        aux=abs(greyN-grey_act);
        if(aux<menor){
            menor=aux;
            id=8;
        }
    }

    if(p.y-1>=0 && p.x+1<320){
        greyNE=grayImage.at<uchar>(p.y-1,p.x+1);
        aux=abs(greyNE-grey_act);
        if(aux<menor){
            menor=aux;
            id=9;
        }
    }

    if(p.y-1>=0 && p.x-1>=0){
        greyNO=grayImage.at<uchar>(p.y-1,p.x-1);
        aux=abs(greyNO-grey_act);
        if(aux<menor){
            menor=aux;
            id=7;
        }
    }

    if( p.x+1<320){
        greyE=grayImage.at<uchar>(p.y,p.x+1);
        aux=abs(greyE-grey_act);
        if(aux<menor){
            menor=aux;
            id=6;
        }
    }

    if(p.y+1<240 && p.x+1<320){
        greySE=grayImage.at<uchar>(p.y+1,p.x+1);
        aux=abs(greySE-grey_act);
        if(aux<menor){
            menor=aux;
            id=3;
        }
    }

    if(p.y+1<240){
        greyS=grayImage.at<uchar>(p.y+1,p.x);
        aux=abs(greyS-grey_act);
        if(aux<menor){
            menor=aux;
            id=2;
        }
    }

    if(p.y+1<240 && p.x-1>=0){
        greySO=grayImage.at<uchar>(p.y+1,p.x-1);
        aux=abs(greySO-grey_act);
        if(aux<menor){
            menor=aux;
            id=1;
        }
    }

    if(p.x-1>=0){
        greyO=grayImage.at<uchar>(p.y,p.x-1);
        aux=abs(greyO-grey_act);
        if(aux<menor){
            menor=aux;
            id=1;
        }
    }
    return IdRegiones(id,p);
}

int MainWindow::IdRegiones(int id, Point ori){

    switch (id) {
    case 1:
        return ImagenRegiones.at<int>(ori.y+1,ori.x-1);
        break;
    case 2:
          return ImagenRegiones.at<int>(ori.y+1,ori.x);
        break;
    case 3:
          return ImagenRegiones.at<int>(ori.y+1,ori.x+1);
        break;
    case 4:
          return ImagenRegiones.at<int>(ori.y,ori.x-1);
        break;
    case 6:
          return ImagenRegiones.at<int>(ori.y,ori.x+1);
        break;
    case 7:
          return ImagenRegiones.at<int>(ori.y-1,ori.x-1);
        break;
    case 8:
          return ImagenRegiones.at<int>(ori.y-1,ori.x);
        break;
    case 9:
          return ImagenRegiones.at<int>(ori.y-1,ori.x+1);
        break;

    }

    return -1;
}

void MainWindow::PuntosNegros(){
    Point p;

    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            if(ImagenRegiones.at<int>(i,j)==-1){
                p.x=j;
                p.y=i;
                ImagenRegiones.at<int>(i,j)=RegionAfin(p);
            }
        }
    }
}

void MainWindow::PintarSegmentado(Mat Img_Dest){
    int region;
    uchar grey;

    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            region=ImagenRegiones.at<int>(i,j);
            grey=ListaRegiones[region].grey;
            Img_Dest.at<uchar>(i,j)=grey;
            ListaRegiones[region].ListaFrontera.clear();
             if(ImagenBordes.at<uchar>(i,j)!=0 && ui->Check_Border->isChecked()){
                Img_Dest.at<uchar>(i,j)=Qt::green;
            }
        }
    }

    ListaRegiones.clear();
    ImagenRegiones.setTo(-1);
}









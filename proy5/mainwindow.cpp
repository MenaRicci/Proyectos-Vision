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

    imgS_2 = new QImage(320,240, QImage::Format_RGB888);
    visorS_2 = new RCDraw(320,240, imgS_2, ui->imageFrameS_2);
    imgD_2 = new QImage(320,240, QImage::Format_RGB888);
    visorD_2 = new RCDraw(320,240, imgD_2, ui->imageFrameD_2);


    colorImage.create(240,320,CV_8UC3);
    grayImage.create(240,320,CV_8UC1);
    destColorImage.create(240,320,CV_8UC3);
    destGrayImage.create(240,320,CV_8UC1);


    colorImage2.create(240,320,CV_8UC3);
    grayImage2.create(240,320,CV_8UC1);
    destColorImage2.create(240,320,CV_8UC3);
    destGrayImage2.create(240,320,CV_8UC1);


    ImagenRegiones.create(240,320,CV_32SC1);
    ImagenBordes.create(240,320,CV_8UC1);
    ImagenVisitados.create(240,320,CV_32SC1);

    ImagenRegiones.setTo(-1);
    Fijos.setTo(0);
    ImagenVisitados.setTo(0);

    gray2ColorImage.create(240,320,CV_8UC3);
    destGray2ColorImage.create(240,320,CV_8UC3);


    gray2ColorImage2.create(240,320,CV_8UC3);
    destGray2ColorImage2.create(240,320,CV_8UC3);



    Disparidad.create(240,320,CV_32FC1);
    Fijos.create(240,320,CV_32SC1);



    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    connect(ui->colorButton,SIGNAL(clicked(bool)),this,SLOT(change_color_gray(bool)));
    connect(ui->LoadButton,SIGNAL(clicked()),this,SLOT(load_Image()));
    connect(ui->InitButton,SIGNAL(clicked()),this,SLOT(InitializeDisparity()));
    connect(ui->GroundButton,SIGNAL(clicked()),this,SLOT(LoadGroundTruth()));


   ListaVentanas.push_back(3);
   ListaVentanas.push_back(5);
   ListaVentanas.push_back(7);
   ListaVentanas.push_back(9);
   ListaVentanas.push_back(11);
   ListaVentanas.push_back(13);
   ListaVentanas.push_back(15);

   ListaRepeticiones.push_back(1);
   ListaRepeticiones.push_back(2);
   ListaRepeticiones.push_back(3);
   ListaRepeticiones.push_back(4);




    clicked=true;

    connect(visorS,SIGNAL(windowSelected(QPointF, int, int)),this,SLOT(selectWindow(QPointF, int, int)));
    connect(visorS,SIGNAL(pressEvent()),this,SLOT(deselectWindow()));
    connect(visorS_2,SIGNAL(windowSelected(QPointF,int,int)),this,SLOT(GetDisparity(QPointF)));
    timer.start(60);

    VentanaMaxima=13/2;
    load_Image();

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

    if(ui->Check_Corners->isChecked())
       PintarEsquinas();
    if(ui->PropaButton->isChecked())
        PropagateDisparity();

    if(showColorImage)
    {
        memcpy(imgS->bits(), colorImage.data , 320*240*3*sizeof(uchar));
        memcpy(imgD->bits(), destColorImage.data , 320*240*3*sizeof(uchar));
        memcpy(imgS_2->bits(), colorImage2.data , 320*240*3*sizeof(uchar));
        memcpy(imgD_2->bits(), destColorImage2.data , 320*240*3*sizeof(uchar));

    }
    else
    {
        cvtColor(grayImage,gray2ColorImage, CV_GRAY2RGB);
        cvtColor(destGrayImage,destGray2ColorImage, CV_GRAY2RGB);
        cvtColor(grayImage2,gray2ColorImage2, CV_GRAY2RGB);
        cvtColor(destGrayImage2,destGray2ColorImage2, CV_GRAY2RGB);

        memcpy(imgS->bits(), gray2ColorImage.data , 320*240*3*sizeof(uchar)); //Pasa el contenido a VisorS
        memcpy(imgD->bits(), destGray2ColorImage.data , 320*240*3*sizeof(uchar));//Pasa el contenido a VisorD
        memcpy(imgS_2->bits(), gray2ColorImage2.data , 320*240*3*sizeof(uchar)); //Pasa el contenido a VisorD_2
        memcpy(imgD_2->bits(), destGray2ColorImage2.data , 320*240*3*sizeof(uchar));//Pasa el contenido a VisorS_2

    }


    if(winSelected)
    {
        visorS->drawSquare(QPointF(imageWindow.x+imageWindow.width/2, imageWindow.y+imageWindow.height/2), imageWindow.width,imageWindow.height, Qt::green );

    }
    visorS->update();
    visorD->update();
    visorS_2->update();
    visorD_2->update();

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

void MainWindow::clear(){
    grayImage2.setTo(0);
    destGrayImage2.setTo(0);
    Disparidad.setTo(0);
    ImagenBordes.setTo(0);
    ImagenRegiones.setTo(-1);
    ImagenVisitados.setTo(0);
    Fijos.setTo(0);

    ListaEsquinas.clear();
    ListaRegiones.clear();

}

void MainWindow::load_Image()
{

    clear();


capture=false;
ui->captureButton->setText("Pulsar Para Capturar");
loadbool=true;

QString filters("JPG files (*.jpg);;BMP files (*.bmp);;PNG files (*.png);;All files (*.*)");
QString defaultFilter("All files (*.*)");
QFileDialog fileDialog(0, "Open file", "/home/guille/Escritorio/Images", filters);
fileDialog.selectNameFilter(defaultFilter);
fileDialog.setFileMode(QFileDialog::ExistingFiles);


QStringList fileNames;
if (fileDialog.exec())
    fileNames = fileDialog.selectedFiles();


if(fileNames.size()>1){
    QString File=fileNames.front();
    fileNames.pop_front();
    colorImage=imread(File.toStdString());
    AnchoImagOri=colorImage.cols;
    cv::resize(colorImage,colorImage, Size(320,240),0,0,INTER_LINEAR);

    cvtColor(colorImage,grayImage, CV_BGR2GRAY);
    cvtColor(colorImage,colorImage, CV_BGR2RGB);

    File=fileNames.front();
    fileNames.pop_front();
    destColorImage=imread(File.toStdString());

    cv::resize(destColorImage,destColorImage, Size(320,240),0,0,INTER_LINEAR);

    cvtColor(destColorImage,destGrayImage, CV_BGR2GRAY);
    cvtColor(destColorImage,destColorImage, CV_BGR2RGB);

    start_stop_capture(false);
}
else{
    start_stop_capture(true);
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

void MainWindow::AnalisisRegion(Point pInicial,int region,STRegion &aux){

    std::vector<Point> Lista;
    Point Act, Nuevo;
    int i=0;

    uchar value_grey=grayImage.at<uchar>(pInicial.y,pInicial.x);
    uchar grey_act;

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
                    if(ImagenBordes.at<uchar>(Act.y,Act.x)==0){
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
        if(Act.x>=0 && Act.x<320 && Act.y>=0 && Act.y < 240 && ImagenRegiones.at<int>(Act.y,Act.x)==-1 && Fijos.at<int>(Act.y,Act.x)!=1){
            grey_act=grayImage.at<uchar>(Act.y,Act.x);
            mediaN=(aux.numP*media+grey_act)/(aux.numP+1);
            varianzaN=(aux.numP*varianza + (grey_act-media)*(grey_act-mediaN))/(aux.numP+1);
                if(varianzaN<15){
                    media=mediaN;
                    varianza=varianzaN;
                    ImagenRegiones.at<int>(Act.y,Act.x)=region;
                    aux.numP++;
                    if(ImagenBordes.at<uchar>(Act.y,Act.x)==0){
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
                aux.disp=0;
                aux.nFijos=0;
                AnalisisRegion(p,contRegion,aux);
                aux.grey=grayImage.at<uchar>(p.y,p.x);
                ListaRegiones.push_back(aux);
                contRegion++;
            }
        }
    } PuntosNegros();

}

void MainWindow::PuntosFronteras(){
    Point p;
    int region;
    int size=ListaRegiones.size();
    for (int i = 0; i < size; ++i) {
        if(ListaRegiones[i].id!=-1){
        p=ListaRegiones[i].pOri;
        region=ListaRegiones[i].id;
        AnalisisFrontera(p, region, i);
        }
    }
}

void MainWindow::AnalisisFrontera(Point p, int region, int ind){

    std::vector<Point> Lista;
    Point Act, pO,pE,pN,pS;
    int i=0;

    Lista.push_back(p);

    int size=Lista.size();
    while(i<size){

        Act=Lista[i];
        i++;
        if(Act.x>=0 && Act.x<320 && Act.y>=0 && Act.y < 240 && ImagenRegiones.at<int>(Act.y,Act.x)==region && ImagenVisitados.at<int>(Act.y,Act.x)==0 ){

            ImagenVisitados.at<int>(Act.y,Act.x)=1;

            pN.x=Act.x;
            pN.y=Act.y-1;
            Lista.push_back(pN);

            pE.x=Act.x+1;
            pE.y=Act.y;
            Lista.push_back(pE);

            pS.x=Act.x;
            pS.y=Act.y+1;
            Lista.push_back(pS);



            pO.x=Act.x-1;
            pO.y=Act.y;
            Lista.push_back(pO);

            if((pO.x>=0 && ImagenRegiones.at<int>(pO.y,pO.x)!=region) || (pE.x<320 && ImagenRegiones.at<int>(pE.y,pE.x)!=region) || (pN.y>=0 && ImagenRegiones.at<int>(pN.y,pN.x)!=region) || (pS.y < 240 && ImagenRegiones.at<int>(pS.y,pS.x)!=region))
                ListaRegiones[ind].ListaFrontera.push_back(Act);

        }

    size=Lista.size();

    }

    Lista.clear();

}



int MainWindow::RegionAfin(Point p){
    int grey_act,greyN,greyE,greyS,greyO;

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

    if( p.x+1<320){
        greyE=grayImage.at<uchar>(p.y,p.x+1);
        aux=abs(greyE-grey_act);
        if(aux<menor){
            menor=aux;
            id=6;
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
    float disparidad,grey;
    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            disparidad=Disparidad.at<float>(i,j);
            grey=(3*disparidad*AnchoImagOri)/320;
            if(grey>255) grey=255;
            Img_Dest.at<uchar>(i,j)=grey;
        }
    }
}


void MainWindow::PintarFrontera(){

    Point aux;
    int size=ListaRegiones.size();
    int sizeFr;
    for (int i = 0; i < size ; ++i) {
        if(ListaRegiones[i].id!=-1){
            sizeFr=ListaRegiones[i].ListaFrontera.size();
            for (int j = 0; j < sizeFr; ++j) {
                aux=ListaRegiones[i].ListaFrontera[j];
                visorD->drawEllipse(QPoint(aux.x,aux.y),1,1,Qt::green);
            }
        }
    }
}


void MainWindow::Merge(){
    int size=ListaRegiones.size();

    for (int var = 0; var < size; ++var) {
        if(ListaRegiones[var].id !=-1){
            AnalisisMerge(var);
        }
    }
    PuntosFronteras();
}

int MainWindow::AnalisisMerge(int id){
    Point p;
    int region_local=ListaRegiones[id].id;
    int size=ListaRegiones[id].ListaFrontera.size();
    QMap<int, StructMap> mapa;
    for (int var = 0; var < size; ++var) {

        p=ListaRegiones[id].ListaFrontera[var];


        if(p.y-1>=0 && region_local!= ImagenRegiones.at<int>(p.y-1,p.x)){

            if(mapa.contains(ImagenRegiones.at<int>(p.y-1,p.x))){
                 mapa[ImagenRegiones.at<int>(p.y-1,p.x)].numFrontera++;
                if( ImagenBordes.at<uchar>(p.y-1,p.x)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y-1,p.x)].numCanny++;
            }else{
                mapa[ImagenRegiones.at<int>(p.y-1,p.x)].numFrontera=1;
                if( ImagenBordes.at<uchar>(p.y-1,p.x)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y-1,p.x)].numCanny=1;
            }

        }else if(p.x+1<320 && region_local!= ImagenRegiones.at<int>(p.y,p.x+1) ){




            if(mapa.contains(ImagenRegiones.at<int>(p.y,p.x+1))){
                 mapa[ImagenRegiones.at<int>(p.y,p.x+1)].numFrontera++;
                if( ImagenBordes.at<uchar>(p.y,p.x+1)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y,p.x+1)].numCanny++;
            }else{
                mapa[ImagenRegiones.at<int>(p.y,p.x+1)].numFrontera=1;
                if( ImagenBordes.at<uchar>(p.y,p.x+1)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y,p.x+1)].numCanny=1;
            }

        }else if(p.y+1<240 && region_local!= ImagenRegiones.at<int>(p.y+1,p.x)){



            if(mapa.contains(ImagenRegiones.at<int>(p.y+1,p.x))){
                 mapa[ImagenRegiones.at<int>(p.y+1,p.x)].numFrontera++;
                if( ImagenBordes.at<uchar>(p.y+1,p.x)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y+1,p.x)].numCanny++;
            }else{
                mapa[ImagenRegiones.at<int>(p.y+1,p.x)].numFrontera=1;
                if( ImagenBordes.at<uchar>(p.y+1,p.x)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y+1,p.x)].numCanny=1;
            }


        }else if(p.x-1>=0 && region_local!= ImagenRegiones.at<int>(p.y,p.x-1) ){

            if(mapa.contains(ImagenRegiones.at<int>(p.y,p.x-1))){
                 mapa[ImagenRegiones.at<int>(p.y,p.x-1)].numFrontera++;
                if( ImagenBordes.at<uchar>(p.y,p.x-1)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y,p.x-1)].numCanny++;
            }else{
                mapa[ImagenRegiones.at<int>(p.y,p.x-1)].numFrontera=1;
                if( ImagenBordes.at<uchar>(p.y,p.x-1)!=0 || ImagenBordes.at<uchar>(p.y,p.x)!=0)
                    mapa[ImagenRegiones.at<int>(p.y,p.x-1)].numCanny=1;
            }
        }
    }
        int Frontera,Canny, value,valor;

        QList<int> ListaKeys=mapa.uniqueKeys();

        for (int var = 0; var <mapa.size(); ++var){
            value=ListaKeys[var];
            Frontera=mapa[value].numFrontera;
            Canny=mapa[value].numCanny;
            if(Frontera>ListaRegiones[id].ListaFrontera.size()*0.2){
                valor=(Frontera-Canny)/Frontera;
                if(valor >= 0.8){
                   UnirRegiones(id,value);
                   ListaRegiones[value].id=-1;
                }
            }
        }
    return 0;
}

void MainWindow::UnirRegiones(int id, int id_aux){
    Point P;

    for (int i = 0; i < 320; ++i)
        for (int j = 0; j < 240; ++j)
            if(ImagenRegiones.at<int>(j,i)==id_aux){
                ImagenRegiones.at<int>(j,i)=id;
                ListaRegiones[id].numP++;
            }
 }


void MainWindow::Esquinas(){

    Mat dst;
    ListaEsquinas.clear();

    dst = Mat::zeros( grayImage.size(), CV_32FC1 );

      /// Detector parameters
      int blockSize = 2;
      int apertureSize = 3;
      double k = 0.04;
      StructEsquina aux;

      /// Detecting corners
      cornerHarris( grayImage, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

      /// Drawing a circle around corners
      for( int j = 0; j < dst.rows ; j++ )
         { for( int i = 0; i < dst.cols; i++ )
              {
                if(  dst.at<float>(j,i) > 0.000001 && ( j>=VentanaMaxima && j< dst.rows-VentanaMaxima) && (i>=VentanaMaxima && i < dst.cols - VentanaMaxima)  )//incluir que no se salga de la ventana de busqueda
                  {
                    aux.mCorner=dst.at<float>(j,i);
                    aux.P.setX(i);
                    aux.P.setY(j);
                    ListaEsquinas.push_back(aux);
                  }
              }
         }
      nonMaximaSuppression();
      matching();
}

void MainWindow::matching(){

    int size=ListaEsquinas.size(),id;
    Mat Origen,Origen2;
    Mat Fila,Fila2;
    Mat Destino,Destino2;
    QPoint P;
    double minVal,maxVal,minVal2,maxVal2;
    Point minLoc,maxLoc,minLoc2,maxLoc2;

    for (int i = 0; i < size; ++i) {
        P=ListaEsquinas[i].P;

        Origen = grayImage.colRange(P.x()-VentanaMaxima,P.x()+VentanaMaxima).rowRange(P.y()-VentanaMaxima,P.y()+VentanaMaxima);
        Fila   = destGrayImage.colRange(0,P.x()).rowRange(P.y()-VentanaMaxima,P.y()+VentanaMaxima); //AMPLIACION
        matchTemplate(Fila,Origen,Destino,CV_TM_CCOEFF_NORMED);
        minMaxLoc( Destino, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

        if(maxVal>=0.95){
           if(maxLoc.x >= 0 && maxLoc.x + 2*VentanaMaxima <320){
                Origen2 = destGrayImage.colRange(maxLoc.x,maxLoc.x+2*VentanaMaxima).rowRange(P.y()-VentanaMaxima,P.y()+VentanaMaxima);
                //Fila2   = grayImage.colRange(maxLoc.x+VentanaMaxima,320-(maxLoc.x+VentanaMaxima)).rowRange(P.y()-VentanaMaxima,P.y()+VentanaMaxima);
                Fila2   = grayImage.colRange(0,320).rowRange(P.y()-VentanaMaxima,P.y()+VentanaMaxima);

                matchTemplate(Fila2,Origen2,Destino2,CV_TM_CCOEFF_NORMED);
                minMaxLoc( Destino2, &minVal2, &maxVal2, &minLoc2, &maxLoc2, Mat() );

                if(abs(maxLoc2.x+VentanaMaxima - P.x()) <= 3  )
                {
                    ListaEsquinas[i].P2=maxLoc;
                    ListaEsquinas[i].P2.y=P.y();
                    ListaEsquinas[i].P2.x+=VentanaMaxima;
                    ListaEsquinas[i].homol=true;
                    Fijos.at<uchar>(P.y(),P.x())=1;
                    Disparidad.at<float>(P.y(),P.x())=P.x()-ListaEsquinas[i].P2.x;
                    id=ImagenRegiones.at<int>(P.y(),P.x());
                    ListaRegiones[id].disp+=Disparidad.at<float>(P.y(),P.x());
                    ListaRegiones[id].nFijos++;
                }

            }else{
                ListaEsquinas[i].P2=maxLoc;
                ListaEsquinas[i].P2.y=P.y();
                ListaEsquinas[i].P2.x+=VentanaMaxima;
                ListaEsquinas[i].homol=true;
                Fijos.at<uchar>(P.y(),P.x())=1;
                Disparidad.at<float>(P.y(),P.x())=P.x()-ListaEsquinas[i].P2.x;
                id=ImagenRegiones.at<int>(P.y(),P.x());
                ListaRegiones[id].disp+=Disparidad.at<float>(P.y(),P.x());
                ListaRegiones[id].nFijos++;
            }
        }else
            ListaEsquinas[i].homol=false;
    }


}

void MainWindow::InitializeDisparity(){
    Canny(grayImage,ImagenBordes);
    ListaRegiones.clear();
    Segmentacion();
    Merge();
    Merge();
    Merge();
    Merge();
    Esquinas();
    InitDisparity();
    PintarSegmentado(grayImage2);


}

void MainWindow::PropagateDisparity(){

    PropagateMaximo=ListaVentanas[ui->comboBox->currentIndex()];
    int region,region_aux;
    float disp1,total=0.0;
    int cont=0;
    bool fin=false;
    for (int i =0 ; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            if(Fijos.at<uchar>(i,j)!=1){
                region=ImagenRegiones.at<int>(i,j);
                cont=0;
                total=0.0;
                disp1=Disparidad.at<float>(i,j);
                for (int k = i-PropagateMaximo/2; k <= i+PropagateMaximo/2; ++k) {
                    for (int t = j-PropagateMaximo/2; t <= j+PropagateMaximo/2; ++t) {
                        if((k>=0 && k<240) && (t>=0 && t<320)){
                            region_aux=ImagenRegiones.at<int>(k,t);
                            if(region==region_aux){
                                cont++;
                                total+=Disparidad.at<float>(k,t);
                            }
                        }
                    }
                }
                Disparidad.at<float>(i,j)=total/cont;
                if(disp1!=Disparidad.at<float>(i,j))
                    fin=true;
            }
        }
    }
    ui->PropaButton->setChecked(fin);
    PintarSegmentado(grayImage2);
}

void MainWindow::LoadGroundTruth(){

    capture=false;
    loadbool=true;

    QString filters("JPG files (*.jpg);;BMP files (*.bmp);;PNG files (*.png);;All files (*.*)");
    QString defaultFilter("All files (*.*)");
    QFileDialog fileDialog(0, "Cargar Ground Truth", "/home/guille/Escritorio", filters);
    fileDialog.selectNameFilter(defaultFilter);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);


    QStringList fileNames;
    if (fileDialog.exec())
        fileNames = fileDialog.selectedFiles();


    if(fileNames.size()>0){
        QString File=fileNames.front();
        fileNames.pop_front();
        destColorImage2=imread(File.toStdString());

        cv::resize(destColorImage2,destColorImage2, Size(320,240),0,0,INTER_LINEAR);

        cvtColor(destColorImage2,destGrayImage2, CV_BGR2GRAY);
        cvtColor(destColorImage2,destColorImage2, CV_BGR2RGB);
    }
}

void MainWindow::PintarEsquinas(){
    int sizeI=ListaEsquinas.size();
QPoint P;
    for (int i = 0; i <sizeI; ++i) {
        if(ListaEsquinas[i].homol==true){
            P.setX(ListaEsquinas[i].P2.x);
            P.setY(ListaEsquinas[i].P2.y);
            visorS->drawEllipse(ListaEsquinas[i].P,2,2,Qt::green);
            visorD->drawEllipse(P,2,2,Qt::green);

        }else
            visorS->drawEllipse(ListaEsquinas[i].P,2,2,Qt::red);

    }
}

bool FuncionOrdenacion(StructEsquina i, StructEsquina j){
    return (i.mCorner>j.mCorner);
}

void MainWindow::nonMaximaSuppression(){
    int size=ListaEsquinas.size();
    QPoint p,aux;

    std::sort(ListaEsquinas.begin(),ListaEsquinas.end(),FuncionOrdenacion);

    float dist;
    for (int i = 0; i < size; ++i) {
        p=ListaEsquinas[i].P;
        for (int j = i+1; j < size; ++j) {
           aux=ListaEsquinas[j].P;
           dist=sqrt( pow(p.x()-aux.x(),2) + pow(p.y()-aux.y(),2) );
           if(dist<=5){
               ListaEsquinas.erase(ListaEsquinas.begin()+j);
               j--;
           }
           size=ListaEsquinas.size();
        }
    }    
}

void MainWindow::GetDisparity(QPointF P){
    uchar new_grey_value;
    uchar old_grey_value;

    new_grey_value=grayImage2.at<uchar>(P.y(),P.x());
    old_grey_value=destGrayImage2.at<uchar>(P.y(),P.x());

   ui->EstimatedLCD->display(new_grey_value);
   ui->TrueLCD->display(old_grey_value);

}

void MainWindow::InitDisparity(){

    int region;
    float disparidad;

    for (int i = 0; i < 240; ++i) {
        for (int j = 0; j < 320; ++j) {
            if(Fijos.at<uchar>(i,j)!=1){
                region=ImagenRegiones.at<int>(i,j);
                if(ListaRegiones[region].nFijos!=0){
                     disparidad=(ListaRegiones[region].disp/ListaRegiones[region].nFijos);
                }else{
                    disparidad=0;
                }
            }
            Disparidad.at<float>(i,j)=disparidad;
        }
    }
}

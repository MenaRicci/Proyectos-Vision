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

    connect(&timer,SIGNAL(timeout()),this,SLOT(compute()));
    connect(ui->captureButton,SIGNAL(clicked(bool)),this,SLOT(start_stop_capture(bool)));
    connect(ui->colorButton,SIGNAL(clicked(bool)),this,SLOT(change_color_gray(bool)));

    connect(visorS,SIGNAL(windowSelected(QPointF, int, int)),this,SLOT(selectWindow(QPointF, int, int)));
    connect(visorS,SIGNAL(pressEvent()),this,SLOT(deselectWindow()));
    timer.start(60);
    ContVideo=0;
    TamComp=320*240;
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

    if(ui->PlayButton->isChecked()){
        int size=Record.VectorCaptura.size();
        int value=(240*320*size/1000);

        ui->LCD_Normal->display(value);
        ui->LCD_Compressed->display(TamComp/1000);
        if (ContVideo< size){
            Play(ContVideo);
            ContVideo++;
        }else{
            ui->PlayButton->setChecked(false);
            ContVideo=0;
            Record.VectorCaptura.clear();
            Record.TamVentana=0;
            Record.Img_Referencia.setTo(0);
            ListaPuntos_Next.clear();
            ListaPuntos_Prev.clear();
            TamComp=320*240;
        }
    }
    if(ui->RecordButton->isChecked())
        Grabar();


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


void MainWindow::Play(int i){
int NumCambios;
Point2f Centro;
Mat Ventana;
int TamVentana=Record.TamVentana;
    if(i==0){
        destGrayImage=Record.Img_Referencia.clone();
    }else{
        NumCambios=Record.VectorCaptura[i].VectorCambio.size();
        for (int j = 0; j < NumCambios; j++) {
            Centro=Record.VectorCaptura[i].VectorCambio[j].Centro;
            Record.VectorCaptura[i].VectorCambio[j].Contenido.copyTo(Ventana);
            Ventana.copyTo(destGrayImage.rowRange(Centro.y-TamVentana/2,Centro.y+TamVentana/2+1).colRange(Centro.x-TamVentana/2,Centro.x+TamVentana/2+1));
        }
    }
}

void MainWindow::Grabar(){
    int size=Record.VectorCaptura.size();
    Captura C;
    if(size==0){
        GetPuntos();
        Record.Img_Referencia=grayImage.clone();
        C.NumCambios=0;
        Record.VectorCaptura.push_back(C);
        Img_Refer=grayImage.clone();
        Record.TamVentana=ui->Spin_Windows->value();
    }else
           CalculoOptico(Img_Refer,grayImage);
    destGrayImage=Img_Refer.clone();
}

void MainWindow::GetPuntos(){
    int TamVentana=ui->Spin_Windows->value();
    Point2f P;
        int i,j;
    for(i = TamVentana/2; i < 320-TamVentana/2 ; i+=TamVentana) {
        for(j = TamVentana/2; j < 240-TamVentana/2; j+=TamVentana) {
            P.x=i;
            P.y=j;
            ListaPuntos_Prev.push_back(P);
            ListaPuntos_Next.push_back(P);
        }
    }
    if(320 % TamVentana != 0){
        j=239-TamVentana/2 -1;

        for (i=319-TamVentana/2 -1; i >=TamVentana/2; i-=TamVentana) {
            P.x=i;
            P.y=j;
            ListaPuntos_Prev.push_back(P);
            ListaPuntos_Next.push_back(P);
        }

        i=TamVentana/2;
        P.x=i;
        P.y=j;
        ListaPuntos_Prev.push_back(P);
        ListaPuntos_Next.push_back(P);
    }

    if(240 % TamVentana != 0){
        i=319-TamVentana/2 -1;
        for (j =TamVentana/2;j< 240 -TamVentana/2; j+=TamVentana) {
            P.x=i;
            P.y=j;
            ListaPuntos_Prev.push_back(P);
            ListaPuntos_Next.push_back(P);
        }

        i=319-TamVentana/2 -1;
        j=239-TamVentana/2 -1;
        P.x=i;
        P.y=j;
        ListaPuntos_Prev.push_back(P);
        ListaPuntos_Next.push_back(P);
    }

}

void MainWindow::CalculoOptico(Mat Img_Pre, Mat Img_Next){
    std::vector<uchar> status;
    std::vector<float> err;
    Cambio C;
    C.Contenido.setTo(0);
    Captura Cap;
    QPoint A,B;
    int TamVentana = Record.TamVentana;
    float Flow =ui->Spin_Flow->value();
    calcOpticalFlowPyrLK(Img_Pre,Img_Next,ListaPuntos_Prev,ListaPuntos_Next,status,err,Size(TamVentana,TamVentana));
    int size= ListaPuntos_Prev.size();
    Point2f Centro, P2;
    float dist;
    Cap.NumCambios=0;
    Cap.VectorCambio.clear();
    for (int var = 0; var < size; ++var) {
        Centro=ListaPuntos_Prev[var];
        P2=ListaPuntos_Next[var];
        dist=sqrt(pow(Centro.x-P2.x,2)+pow(Centro.y-P2.y,2));
        if(dist>Flow){
            A.setX(Centro.x);
            A.setY(Centro.y);
            B.setX(P2.x);
            B.setY(P2.y);
            visorD->drawLine(QLine(A,B),Qt::red,0.5);
            Cap.NumCambios++;
            C.Centro=Centro;

            C.Contenido=Img_Next.rowRange(Centro.y-TamVentana/2,Centro.y+TamVentana/2+1).colRange(Centro.x-TamVentana/2,Centro.x+TamVentana/2 +1).clone();
            C.Contenido.copyTo(Img_Refer.rowRange(Centro.y-TamVentana/2,Centro.y+TamVentana/2+1).colRange(Centro.x-TamVentana/2,Centro.x+TamVentana/2 +1));
            Cap.VectorCambio.push_back(C);
        }
     }
     TamComp+=4+Cap.NumCambios*(8+TamVentana*TamVentana);
     if(Cap.NumCambios!=0){
        Record.VectorCaptura.push_back(Cap);
     }
}

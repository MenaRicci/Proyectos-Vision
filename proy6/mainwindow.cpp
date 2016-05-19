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
    //qDebug()<<"Hola";
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
    for (int i = TamVentana/2; i < 320-TamVentana/2 ; i+=TamVentana) {
        for (int j = TamVentana/2; j < 240-TamVentana/2; j+=TamVentana) {
            P.x=i;
            P.y=j;
            ListaPuntos_Prev.push_back(P);
            ListaPuntos_Next.push_back(P);
        }
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
        //    Img_Next.rowRange(Centro.y-TamVentana/2,Centro.y+TamVentana/2+1).colRange(Centro.x-TamVentana/2,Centro.x+TamVentana/2 +1).copyTo(C.Contenido);
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

void MainWindow::save_Image()
{
capture=false;
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

}
/*
void MainWindow::Programa()
{
//    if (argc != 4)
//    {
//        cout << "Not enough parameters" << endl;
//        return -1;
//    }

//    const string source      = argv[1];           // the source file name
//    const bool askOutputType = argv[3][0] =='Y';  // If false it will use the inputs codec type


    const QString filename=QFileDialog::getSaveFileName(0,"Save file",QDir::currentPath(),"JPG files (*.avi);;All files (*.*)",new QString("Text files (*.avi)"));

    String source=filename.toStdString();
    VideoCapture inputVideo(source);              // Open input

    string::size_type pAt = source.find_last_of('.');                  // Find extension point
    const string NAME = source.substr(0, pAt) + source + ".avi";   // Form the new name with container
    int ex = static_cast<int>(inputVideo.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form

    // Transform from int to char via Bitwise operators
    char EXT[] = {(char)(ex & 0XFF) , (char)((ex & 0XFF00) >> 8),(char)((ex & 0XFF0000) >> 16),(char)((ex & 0XFF000000) >> 24), 0};

    Size S = Size((int) inputVideo.set(CV_CAP_PROP_FRAME_WIDTH,320),    // Acquire input size
                  (int) inputVideo.set(CV_CAP_PROP_FRAME_HEIGHT,240));

    VideoWriter outputVideo;                                        // Open the output
    outputVideo.open(NAME, ex, inputVideo.get(CV_CAP_PROP_FPS), S, true);

    qDebug() << "Input frame resolution: Width=" << S.width << "  Height=" << S.height
         << " of nr#: " << inputVideo.get(CV_CAP_PROP_FRAME_COUNT);
    qDebug() << "Input codec type: " << EXT;

    int channel = 2; // Select the channel to save
    channel=1;
    Mat src, res;
    vector<Mat> ;

    for(;;) //Show the image captured in the window and repeat
    {
        inputVideo >> src;              // read
        if (src.empty()) break;         // check if at end

        split(src, spl);                // process - extract only the correct channel
        for (int i =0; i < 3; ++i)
            if (i != channel)
                spl[i] = Mat::zeros(S, spl[0].type());
       merge(spl, res);
       //outputVideo.write(res); //save or
       outputVideo << res;
    }
qDebug()<<"FINIsh";
}
*/


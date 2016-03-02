#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Action=0;

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
    Datos_K.matrix_kernel.create(3,3,CV_8SC1);

    TLUT.resize(256);

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

    connect(ui->Ori_checkHisogram, SIGNAL(clicked(bool)), this, SLOT(getOriHistogram(bool)));

    connect(ui->Dest_checkHistogram, SIGNAL(clicked(bool)), this, SLOT(getNewHistogram(bool)));
    connect(ui->operationComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(obtener_accion(int)));
    timer.start(60);

    OriHistogram=false;
    DestHistogram=false;

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
void MainWindow::obtener_accion(int indice){
    Action=indice;
}

//FUNCIONES DE PROGRAMA ORIGINAL
void MainWindow::compute()
{

    if(capture && cap->isOpened())
    {
        *cap >> colorImage;

        cvtColor(colorImage, grayImage, CV_BGR2GRAY);
        cvtColor(colorImage, colorImage, CV_BGR2RGB);

    }

   showHistogram(grayImage,"Histograma Original",0);

   showHistogram(destGrayImage,"Histograma Destino",1);


/*Elegir que accion ejecuta dependiendo del combo box*/
    chooseAction(Action,grayImage,destGrayImage);

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
//ABRIR FRAMES
void MainWindow::abrir_Filter(){
ui_Filter.show();

}
void MainWindow::abrirOperOrder(){
ui_Oper.show();
}
void MainWindow::abrirPixel(){
ui_pixel.show();
}
void MainWindow::saveDataFilter(){

    Datos_K.matrix_kernel.row(0).col(0)=ui_Filter.kernelBox11->value();
    Datos_K.matrix_kernel.row(0).col(1)=ui_Filter.kernelBox12->value();
    Datos_K.matrix_kernel.row(0).col(2)=ui_Filter.kernelBox13->value();

    Datos_K.matrix_kernel.row(1).col(0)=ui_Filter.kernelBox21->value();
    Datos_K.matrix_kernel.row(1).col(1)=ui_Filter.kernelBox22->value();
    Datos_K.matrix_kernel.row(1).col(2)=ui_Filter.kernelBox23->value();

    Datos_K.matrix_kernel.row(2).col(0)=ui_Filter.kernelBox31->value();
    Datos_K.matrix_kernel.row(2).col(1)=ui_Filter.kernelBox32->value();
    Datos_K.matrix_kernel.row(2).col(2)=ui_Filter.kernelBox33->value();
    Datos_K.value=ui_Filter.addedVBox->value();

}

//BOTONES OK

void MainWindow::ok_filter_cerrar(){
    saveDataFilter();
    ui_Filter.close();
}

void MainWindow::saveDataPixel(){
    Datos_Pixel.New_DataList[0]=ui_pixel.newPixelBox1->value();
    Datos_Pixel.New_DataList[1]=ui_pixel.newPixelBox2->value();
    Datos_Pixel.New_DataList[2]=ui_pixel.newPixelBox3->value();
    Datos_Pixel.New_DataList[3]=ui_pixel.newPixelBox4->value();

    Datos_Pixel.Ori_DataList[0]=ui_pixel.origPixelBox1->value();
    Datos_Pixel.Ori_DataList[1]=ui_pixel.origPixelBox2->value();
    Datos_Pixel.Ori_DataList[2]=ui_pixel.origPixelBox3->value();
    Datos_Pixel.Ori_DataList[3]=ui_pixel.origPixelBox4->value();
}

void MainWindow::ok_pixel_cerrar(){
    saveDataPixel();
    ui_pixel.close();
}

void MainWindow::ok_oper_cerrar(){
    ui_Oper.close();
}
//CHECKEO HISTOGRAMA

void MainWindow::getNewHistogram(bool start){
    DestHistogram=start;
}

void MainWindow::getOriHistogram(bool start){
    OriHistogram=start;
}

//SHOW HISTOGRAM

void MainWindow::showHistogram(Mat& img, char* name,int valor)
{

    int bins = 256;             // number of bins
    int nc = img.channels();    // number of channels
    vector<Mat> hist(nc);       // array for storing the histograms
    vector<Mat> canvas(nc);     // images for displaying the histogram
    int hmax[3] = {0,0,0};      // peak value for each histogram

    // The rest of the code will be placed here
for (int i = 0; i < hist.size(); i++)
    hist[i] = Mat::zeros(1, bins, CV_32SC1);
for (int i = 0; i < img.rows; i++)
{
    for (int j = 0; j < img.cols; j++)
    {
        for (int k = 0; k < nc; k++)
        {
            uchar val = nc == 1 ? img.at<uchar>(i,j) : img.at<Vec3b>(i,j)[k];
            hist[k].at<int>(val) += 1;
        }
    }
}

for (int i = 0; i < nc; i++)
{
    for (int j = 0; j < bins-1; j++)
        hmax[i] = hist[i].at<int>(j) > hmax[i] ? hist[i].at<int>(j) : hmax[i];
}

const char* wname[3] = { "blue", "green", "red" };
Scalar colors[3] = { Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255) };

for (int i = 0; i < nc; i++)
{
    canvas[i] = Mat::ones(125, bins, CV_8UC3);

    for (int j = 0, rows = canvas[i].rows; j < bins-1; j++)
    {
        line(
            canvas[i],
            Point(j, rows),
            Point(j, rows - (hist[i].at<int>(j) * rows/hmax[i])),
            nc == 1 ? Scalar(200,200,200) : colors[i],
            1, 8, 0
        );
    }
    if(valor == 0)
    {
        if(ui->Ori_checkHisogram->isChecked())
            imshow(nc == 1 ? name : wname[i], canvas[i]);
        else
            destroyWindow(name);
    }
    else if(valor==1){
        if(ui->Dest_checkHistogram->isChecked())
             imshow(nc == 1 ? name : wname[i], canvas[i]);
        else
            destroyWindow(name);
    }


}

}

//OPERACIONES A REALIZAR

void MainWindow::thresholding(Mat MatrizOrigen,Mat Imagen_Destino){
    double p=(double)ui->thresholdSpinBox->value();

    threshold(MatrizOrigen,Imagen_Destino,p,255,THRESH_BINARY);
}

void MainWindow::SuavizadoGaussiano(Mat MatrizOrigen,Mat ImagenDestino){
    double w=(double)ui->gaussWidthBox->value();
    double sigX=w/5;

    GaussianBlur(MatrizOrigen,ImagenDestino,Size(0,0),sigX);
}

void MainWindow::SuavizadoMediana(Mat MatrizOrigen,Mat ImagenDestino){

    medianBlur(MatrizOrigen,ImagenDestino,9);
}


void MainWindow::calculoLUT(){
    //tramos
    int tr1=ui_pixel.origPixelBox2->value();
    int tr2=ui_pixel.origPixelBox3->value();
    //int tr3=ui_pixel.origPixelBox4->value();

    //valores S
    int s0=ui_pixel.newPixelBox1->value();
    int s1=ui_pixel.newPixelBox2->value();
    int s2=ui_pixel.newPixelBox3->value();
    int s3=ui_pixel.newPixelBox4->value();

    int i;
    float denominadorS,denominadorR;

    denominadorS=s1-s0;
    denominadorR=tr1-0;
    for(i=0;i<tr1;i++){
        TLUT[i]=(i/denominadorR)*denominadorS+s0;
    }

    denominadorS=s2-s1;
    denominadorR=tr2-tr1;
    for(i=tr1;i<tr2;i++){
        TLUT[i]=((i-tr1)/denominadorR)*denominadorS+s1;
    }

    denominadorS=s3-s2;
    denominadorR=255-tr2;
    for(i=tr2;i<=255;i++){
        TLUT[i]=((i-tr2)/denominadorR)*denominadorS+s2;
    }

}

void MainWindow::transformPixel(Mat MatrizOrigen,Mat ImagenDestino){
    calculoLUT();
    cv::LUT(MatrizOrigen,TLUT,ImagenDestino);
}

void MainWindow::equalize(Mat MatrizOrigen,Mat ImagenDestino){
    equalizeHist(MatrizOrigen, ImagenDestino);
}

void MainWindow::LinearFilter(Mat MatrizOrigen,Mat ImagenDestino){
    saveDataFilter();


    filter2D(MatrizOrigen,ImagenDestino,0,Datos_K.matrix_kernel,Point(-1,-1),Datos_K.value);
}


void MainWindow::Dilatacion(Mat MatrizOrigen,Mat ImagenDestino){
    Mat Aux;
    Aux.create(240,320,CV_8UC1);
    thresholding(MatrizOrigen,Aux);

    dilate(Aux,ImagenDestino,Mat(), Point(-1,-1), 3);
}

void MainWindow::Erosion(Mat MatrizOrigen,Mat ImagenDestino){
    Mat Aux;
    Aux.create(240,320,CV_8UC1);
    thresholding(MatrizOrigen,Aux);

    erode(Aux,ImagenDestino,Mat(), Point(-1,-1), 3);

}

//OperOrder

void MainWindow::OperOrderFunction(Mat MatrizOrigen,Mat MatrizDestino){
//TODO
    Mat Aux1,Aux2,Aux3;
    Aux1.create(240,320,CV_8UC1);

    MatrizOrigen.copyTo(Aux1);

    if(ui_Oper.firstOperCheckBox->isChecked()){
        int pos1=ui_Oper.operationComboBox1->currentIndex();
        chooseAction(pos1,Aux1,Aux1);
    }
    if(ui_Oper.secondOperCheckBox->isChecked()){
        int pos2=ui_Oper.operationComboBox2->currentIndex();
        chooseAction(pos2,Aux1,Aux1);
    }
    if(ui_Oper.thirdOperCheckBox->isChecked()){
        int pos3=ui_Oper.operationComboBox3->currentIndex();
        chooseAction(pos3,Aux1,Aux1);
    }
    if(ui_Oper.fourthOperCheckBox->isChecked()){
        int pos4=ui_Oper.operationComboBox4->currentIndex();
        chooseAction(pos4,Aux1,Aux1);
    }
    Aux1.copyTo(MatrizDestino);
}

void MainWindow::chooseAction(int accion,Mat MatrizOrigen,Mat MatrizDestino){

    switch(accion){
    case 0:
        transformPixel(MatrizOrigen,MatrizDestino);
        break;
    case 1:
        thresholding(MatrizOrigen,MatrizDestino);
       break;
    case 2:
        equalize(MatrizOrigen,MatrizDestino);
        break;
    case 3:
        SuavizadoGaussiano(MatrizOrigen,MatrizDestino);
        break;
    case 4:
        SuavizadoMediana(MatrizOrigen,MatrizDestino);
        break;
    case 5:
        LinearFilter(MatrizOrigen,MatrizDestino);
        break;
    case 6:
         Dilatacion(MatrizOrigen,MatrizDestino);
        break;
    case 7:
         Erosion(MatrizOrigen,MatrizDestino);
        break;
    case 8:
         OperOrderFunction(MatrizOrigen,MatrizDestino);
        break;
    case 9:
        break;
    }
}







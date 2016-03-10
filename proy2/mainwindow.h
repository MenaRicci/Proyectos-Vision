#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <rcdraw.h>
#include <ui_pixelTForm.h>
#include <ui_operOrderForm.h>
#include <ui_lFilterForm.h>
#include <ui_StructElement.h>


using namespace cv;

namespace Ui {
    class MainWindow;

}

typedef struct {
    int a;
    int New_DataList[4];
    int Ori_DataList[4];
 }Datos_pixel;

typedef struct{
    Mat matrix_kernel;
    double value;
}Datos_Kernel;


class PixelTDialog: public QDialog, public Ui::PixelTForm
{
    Q_OBJECT

public:
    PixelTDialog(QDialog *parent=0): QDialog(parent){
        setupUi(this);
    }

};


class IFilterDialog: public QDialog, public Ui::LFilterForm
{
    Q_OBJECT

public: IFilterDialog(QDialog *parent=0): QDialog(parent){
        setupUi(this);
    }

};


class operOrderDialog: public QDialog, public Ui::OperOrderForm
{
    Q_OBJECT

public: operOrderDialog(QDialog *parent=0): QDialog(parent){
        setupUi(this);
    }
};

class StructElementDialog: public QDialog, public Ui::StructElement
{
    Q_OBJECT

public: StructElementDialog(QDialog *parent=0): QDialog(parent){
        setupUi(this);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    IFilterDialog ui_Filter;
    operOrderDialog ui_Oper;
    PixelTDialog ui_pixel;
    StructElementDialog ui_StrEle;

    QTimer timer;

    VideoCapture *cap;
    RCDraw *visorS, *visorD;
    QImage *imgS, *imgD;
    Mat element;
    Mat colorImage, grayImage, destColorImage, destGrayImage;
    Mat gray2ColorImage, destGray2ColorImage;
    bool capture, showColorImage, winSelected, loadbool,savebool;
    bool OriHistogram;
    bool DestHistogram;
    Rect imageWindow;

    Mat imgHistograma;
    CvHistogram* hist;

    std::vector<uchar> TLUT;

    int Action;
    Datos_pixel Datos_Pixel;
    Datos_Kernel Datos_K;


public:
    void thresholding(Mat MatrizOrigen,Mat Imagen_Destino);
    void SuavizadoGaussiano(Mat MatrizOrigen,Mat Imagen_Destino);
    void SuavizadoMediana(Mat MatrizOrigen,Mat Imagen_Destino);
    void transformPixel(Mat MatrizOrigen,Mat Imagen_Destino);
    void equalize(Mat MatrizOrigen,Mat Imagen_Destino);
    void LinearFilter(Mat MatrizOrigen,Mat Imagen_Destino);
    void getElement();
    void Erosion(Mat MatrizOrigen,Mat Imagen_Destino);
    void Dilatacion(Mat MatrizOrigen,Mat Imagen_Destino);
    void Apertura(Mat MatrizOrigen,Mat Imagen_Destino);
    void Cierre(Mat MatrizOrigen,Mat Imagen_Destino);
    void Gradiente(Mat MatrizOrigen,Mat Imagen_Destino);
    void BlackHat(Mat MatrizOrigen,Mat Imagen_Destino);
    void Logarithm();
    void Potencia();

public slots:
    void compute();
    void start_stop_capture(bool start);
    void change_color_gray(bool color);
    void selectWindow(QPointF p, int w, int h);
    void deselectWindow();
    void load_Image();
    void save_Image();

    void abrir_Filter();
    void abrirOperOrder();
    void abrirPixel();
    void abrirElement();

    void ok_filter_cerrar();
    void ok_pixel_cerrar();
    void ok_oper_cerrar();
    void ok_strEle_cerrar();
    void saveDataFilter();
    void saveDataPixel();
    void calculoLUT();
    int setOptionLUT();
    void hiddenValue(bool state);

    void obtener_accion(int indice);
    void OperOrderFunction(Mat MatrizOrigen, Mat MatrizDestino);
    void chooseAction(int accion,Mat MatrizOrigen, Mat MatrizDestino);

    void getOriHistogram(bool start);
    void getNewHistogram(bool start);

    void showHistogram(Mat& img, String name, int valor);


};


#endif // MAINWINDOW_H

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

using namespace cv;

namespace Ui {
    class MainWindow;

}


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

    QTimer timer;

    VideoCapture *cap;
    RCDraw *visorS, *visorD;
    QImage *imgS, *imgD;
    Mat colorImage, grayImage, destColorImage, destGrayImage;
    Mat gray2ColorImage, destGray2ColorImage;
    bool capture, showColorImage, winSelected, loadbool,savebool;
    Rect imageWindow;

    int Acction;

public:
    void thresholding();
    void SuavizadoGaussiano();
    void SuavizadoMediana();


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

    void ok_filter_cerrar();
    void ok_pixel_cerrar();
    void ok_oper_cerrar();

    void obtener_accion(int indice);


};


#endif // MAINWINDOW_H

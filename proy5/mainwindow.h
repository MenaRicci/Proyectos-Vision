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



using namespace cv;

namespace Ui {
    class MainWindow;
}

typedef struct{
    int id;
    Point pOri;
    int numP;
    uchar grey;
    std::vector<Point> ListaFrontera;

}STRegion;

typedef struct{
    int numFrontera;
    int numCanny;

}StructMap;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int numFoto;
    QTimer timer;

    VideoCapture *cap;
    RCDraw *visorS, *visorD;
    QImage *imgS, *imgD;
    Mat colorImage, grayImage, destColorImage, destGrayImage, Black_Color_Image, Black_Gray_Image;
    Mat gray2ColorImage, destGray2ColorImage;
    bool capture, showColorImage, winSelected,clicked;
    bool loadbool;
    Rect imageWindow;

    std::vector<STRegion> ListaRegiones;
    Mat ImagenRegiones;
    Mat ImagenBordes;
    Mat ImagenVisitados;



public slots:
    void compute();
    void start_stop_capture(bool start);
    void change_color_gray(bool color);
    void load_Image();

    void selectWindow(QPointF p, int w, int h);
    void deselectWindow();

    void Canny(Mat Img_Source, Mat Img_Dest);
    void AnalisisRegion(Point pInicial,int region, STRegion &aux);
    void AnalisisRegionEstadistico(Point pInicial,int region, STRegion &aux);
    void Segmentacion();
    void PuntosNegros();
    void PuntosFronteras();
    void AnalisisFrontera(Point p, int region, int ind);
    int RegionAfin(Point p);
    void PintarSegmentado(Mat Img_Dest);
    void PintarFrontera();
    int IdRegiones(int id, Point ori);
    void Merge();
    int AnalisisMerge(int id);
    void UnirRegiones(int id, int id_aux);
    void Practica4();
};


#endif // MAINWINDOW_H

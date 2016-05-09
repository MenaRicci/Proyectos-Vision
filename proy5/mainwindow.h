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
    float disp;
    int nFijos;

}STRegion;

typedef struct{
    int numFrontera;
    int numCanny;

}StructMap;

typedef struct{
    QPoint P;
    Point P2;
    bool homol;
    float mCorner;

}StructEsquina;

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
    int VentanaMaxima,PropagateMaximo;
    int AnchoImagOri;
    Mat Fijos, Disparidad;

    VideoCapture *cap;
    RCDraw *visorS, *visorD,*visorS_2, *visorD_2 ;
    QImage *imgS, *imgD,*imgS_2, *imgD_2;
    Mat colorImage, grayImage, destColorImage, destGrayImage;
    Mat colorImage2,grayImage2,destColorImage2,destGrayImage2;
    Mat gray2ColorImage, destGray2ColorImage;
    Mat gray2ColorImage2, destGray2ColorImage2;

    bool capture, showColorImage, winSelected,clicked;
    bool loadbool;
    Rect imageWindow;

    std::vector<STRegion> ListaRegiones;
    std::vector<StructEsquina> ListaEsquinas;
    std::vector<int> ListaVentanas;
    Mat ImagenRegiones;
    Mat ImagenBordes;
    Mat ImagenVisitados;

public:

    void load_Image(Mat greyImage,Mat colorImage);
    void PintarEsquinas();
    void Esquinas();
    void nonMaximaSuppression();
    void GetSubMat();
    void matching();
    void InitDisparity();
    void clear();

public slots:
    void compute();
    void start_stop_capture(bool start);
    void change_color_gray(bool color);
    void load_Image();

    void selectWindow(QPointF p, int w, int h);
    void deselectWindow();
    void GetDisparity(QPointF P);


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
   // void Practica4();
    void InitializeDisparity();
    void PropagateDisparity();
    void LoadGroundTruth();
};


#endif // MAINWINDOW_H

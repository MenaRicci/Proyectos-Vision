#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <rcdraw.h>



using namespace cv;

typedef struct {
    float distancia;
    Point2f P;
}Pcaracteristicos;

bool FuncionOrdenacion(Pcaracteristicos i,Pcaracteristicos j);

namespace Ui {
    class MainWindow;
}

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

    ORB orb;
    BFMatcher bfm;

    VideoCapture *cap;
    RCDraw *visorS, *visorD;
    QImage *imgS, *imgD;
    Mat colorImage, grayImage, destColorImage, destGrayImage, Black_Color_Image, Black_Gray_Image;
    Mat gray2ColorImage, destGray2ColorImage;
    bool capture, showColorImage, winSelected,warpeded, clicked;
    bool click, savebool, loadbool,resizebool,enlargebool;
    Rect imageWindow;
    std::vector<Mat> conjuntoImagen1 ;

    std::vector<std::vector<Mat> > ListaObjetosImagenes;
    std::vector<std::vector<std::vector<KeyPoint> > > ListaPuntosImagenes;
    std::vector<KeyPoint> ListaPuntosOrigen;
    Mat descritorOrigen;
    std::vector<std::vector<Mat> > listaDescriptores;
    std::vector<Mat> coleccion;
    std::vector<std::vector<Point2f> > LpFinal;
    std::vector<DMatch> matches;
    std::vector<int> listaContadores;

    std::vector<QColor> Colores;

    //---------------------AMPLIACIONES--------------------------
    std::vector<std::vector<Pcaracteristicos> > listaDistancias;
    std::vector<std::vector<Point2f> > LpFinalAmpliacion;

    double MaxDistance;


public slots:
    void compute();
    void start_stop_capture(bool start);
    void change_color_gray(bool color);
    void set_Image();
    void saveImageInSet();
    void selectWindow(QPointF p, int w, int h);
    void deselectWindow();
    void changeImage();
    void deleteImageInSet();
    void Match_ORB();
    void Match_BFM();
    int IndiceObjeto(int id);
    void BorrarLista();
    void PintarRect();
    void DispersionPuntos(int i);
    bool ComparacionAreas(int i);


};


#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <QWidget>
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsView>
#include <QBrush>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

        void limpiarCampos();

private slots:
    void on_insert_id_textChanged(const QString &arg1);

    void on_insert_voltaje_textChanged(const QString &arg1);

    void on_pos_x_valueChanged(int arg1);

    void on_pos_y_valueChanged(int arg1);

    void on_set_red_valueChanged(int value);

    void on_set_green_valueChanged(int value);

    void on_set_blue_valueChanged(int value);


    void on_agregarInicio_clicked();

    void on_AgregarFinal_clicked();

    void on_mostrar_clicked();

    void on_Tabla_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_buscarNeurona_clicked();

    void on_pushButton_clicked();

    void on_Guardarlista_clicked();

    void on_Leerlista_clicked();

    void on_Dibujar_clicked();

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_OrdID_clicked();

    void on_OrdenarVolt_clicked();

    void on_mostrarOcultarLineas_clicked();

    void dibujarLineasFuerzaBruta();

    void on_Dibujar_2_clicked();

private:
    Ui::MainWindow *ui;
     QGraphicsScene *scene;
    bool lineasVisibles;
};



class Neurona{
public:
    int id,posicion_x,posicion_y;
    int red,green,blue;
    float voltaje;

    Neurona *sig;
    Neurona();
    Neurona(int,float,int,int,int,int,int,Neurona*);
    void print()const{
        std::cout<<"Neurona_"<<id<<":\nVoltaje: "<<voltaje<<std::endl;
    }
};



class Admin{
private:
public:
    Neurona *h;
    Admin (){
        h=nullptr;
    }
    Admin (Neurona*ptr){
        h=ptr;
    }
    void agregar_inicio(int,float,int,int,int,int,int);
    void agregar_final(int,float,int,int,int,int,int);
    void mostrar();
    void ordenarVoltaje();
    void ordenarId();
    Neurona* buscar(int id)
    {
        Neurona* aux = h;
        while (aux != nullptr) {
            if (aux->id == id) {
                return aux;
            }
            aux = aux->sig;
        }
        return nullptr;  // Si no se encuentra la neurona
    }

};
class Grafo {
public:
    void agregarNodo(int id, float x, float y);
    void agregarArista(int idNodoInicio, int idNodoFin, float peso);
    void mostrarGrafo();
    void mostrarAristasEnEscena(QGraphicsScene* scene);

private:
    struct Nodo {
        float coordenada_x;
        float coordenada_y;
    };

    std::unordered_map<int, Nodo> nodos;
    std::unordered_map<int, std::vector<std::pair<int, float>>> aristas;
};
class NodoItem : public QGraphicsEllipseItem {
public:
    NodoItem(int id, QPointF posicion) : QGraphicsEllipseItem(posicion.x(), posicion.y(), 30, 30), id(id) {
        setFlag(QGraphicsItem::ItemIsMovable);
        setBrush(QBrush(Qt::white));
    }

private:
    int id;
};

// Clase para representar aristas
class AristaItem : public QGraphicsLineItem {
public:
    AristaItem(QPointF inicio, QPointF fin, qreal peso) : QGraphicsLineItem(inicio.x(), inicio.y(), fin.x(), fin.y()), peso(peso) {
        setPen(QPen(Qt::black, 2));
    }

private:
    qreal peso;
};


#endif // MAINWINDOW_H

#ifndef _GUI_h
#define _GUI_h

#include <QMainWindow>

#include "ui_GUI4.h"
#include <rbtree.h>
#include <Lista.h>
#include <arbolbb.h>
#include <Fheap.h>
#include <NodoF.h>
#include <AVL.h>
#include <QStandardItemModel>
#include <searchstructure.h>
#include <BinomialHeap.h>


class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

enum Estructuras {List, Cola, Pila, BST, Avl, RedBlack, BinomialHeap, FibonacciHeap};

class GUI4 : public QMainWindow, public Ui::GUI
{
  Q_OBJECT
public:
  GUI4();
  ~GUI4();
  QStandardItemModel *model = new QStandardItemModel();

public slots:
  void updateCoords(vtkObject*);
  void popup(vtkObject * obj, unsigned long,
             void * client_data, void *,
             vtkCommand * command);
  void color1(QAction*);
  void graficarHeap(std::list<NodoF<int>*>, double, double, double, bool, int);
  void graficarbHeap(std::list<NodoBHeap<int>*>, double, double, double, bool, int);
  void cargarDatosaEstructura(QString _rutaArchivo);
  //void color2(QAction*);


protected:
  Lista<Palabra> *lista;
  RBTree<Palabra> *arbol;
  AVL<Palabra> * avl;
  Fheap<int> *fheap = new Fheap<int>();
  Bheap<int> *bheap = new Bheap<int>();
  Estructuras estructuraSeleccionada;
  SearchStructure* estructura;
  vtkRenderer* Renderizador;
  //vtkRenderer* Ren2;
  vtkEventQtSlotConnect* Connections;
private slots:
  void on_pushButton_clicked();
  void on_cbTipoEd_currentIndexChanged(int index);
  void on_btnSeleccionarArchivo_clicked();
  void on_btnCargar_clicked();
  void on_btnBuscar_clicked();
};

#endif // _GUI_h


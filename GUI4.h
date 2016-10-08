#ifndef _GUI_h
#define _GUI_h

#include <QMainWindow>
#include "ui_GUI4.h"
#include <rbnode.h>
#include <rbtree.h>
#include <Fheap.h>
#include <QStandardItemModel>

class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

class GUI4 : public QMainWindow, public Ui::GUI
{
  Q_OBJECT
public:
  GUI4();
  ~GUI4();

public slots:
  void updateCoords(vtkObject*);
  void popup(vtkObject * obj, unsigned long,
             void * client_data, void *,
             vtkCommand * command);
  void color1(QAction*);
  void cargarDatos(QString _rutaArchivo);
  void cargarDatosHeap(QString _rutaArchivo);
  //void color2(QAction*);

protected:
  vtkRenderer* Renderizador;
  QStandardItemModel *model = new QStandardItemModel();
  //vtkRenderer* Ren2;
  vtkEventQtSlotConnect* Connections;
private slots:
  void on_pushButton_clicked();
  void on_cbTipoEd_currentIndexChanged(int index);
  void on_btnSeleccionarArchivo_clicked();
};

#endif // _GUI_h


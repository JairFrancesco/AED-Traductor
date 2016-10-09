#include "GUI4.h"
#include <QMenu>
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkCommand.h"
#include "vtkEventQtSlotConnect.h"
#include "vtkConeSource.h"
#include "vtkSphereSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkInteractorStyle.h"
#include "vtkTDxInteractorStyleCamera.h"
#include "vtkTDxInteractorStyleSettings.h"
#include "QVTKInteractor.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <fstream>
#include <iostream>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QStandardItem>
#include <palabra.h>

using namespace std;

GUI4::GUI4()
{
  this->setupUi(this);

  //Table View
  model->setHorizontalHeaderItem(0, new QStandardItem(QString("Idioma 1")));
  model->setHorizontalHeaderItem(1, new QStandardItem(QString("Idioma 2")));
  tblDiccionario->setModel(this->model);

  // create a window to make it stereo capable and give it to QVTKWidget
  vtkRenderWindow* renwin = vtkRenderWindow::New();
  renwin->StereoCapableWindowOn();

  // Activate 3DConnexion device only on the left render window.
  qVTKGrafico->SetUseTDx(true);
  qVTKGrafico->SetRenderWindow(renwin);
  renwin->Delete();

  const double angleSensitivity=0.02;
  const double translationSensitivity=0.001;

  QVTKInteractor *iren=qVTKGrafico->GetInteractor();
  vtkInteractorStyle *s=
    static_cast<vtkInteractorStyle *>(iren->GetInteractorStyle());
  vtkTDxInteractorStyleCamera *t=
    static_cast<vtkTDxInteractorStyleCamera *>(s->GetTDxStyle());

  t->GetSettings()->SetAngleSensitivity(angleSensitivity);
  t->GetSettings()->SetTranslationXSensitivity(translationSensitivity);
  t->GetSettings()->SetTranslationYSensitivity(translationSensitivity);
  t->GetSettings()->SetTranslationZSensitivity(translationSensitivity);



  // add a renderer
  Renderizador = vtkRenderer::New();
  qVTKGrafico->GetRenderWindow()->AddRenderer(Renderizador);

  // add a popup menu for the window and connect it to our slot
  QMenu* popup1 = new QMenu(qVTKGrafico);
  popup1->addAction("Background White");
  popup1->addAction("Background Black");
  popup1->addAction("Stereo Rendering");
  connect(popup1, SIGNAL(triggered(QAction*)), this, SLOT(color1(QAction*)));

  /*
  // put cone in one window
  vtkConeSource* cone = vtkConeSource::New();
  vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(cone->GetOutputPort());
  vtkActor* actor = vtkActor::New();
  actor->SetMapper(mapper);
  Renderizador->AddViewProp(actor);
  actor->Delete();
  mapper->Delete();
  cone->Delete();
  */

  // put sphere in the window
  vtkSphereSource* sphere = vtkSphereSource::New();
  vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
  mapper = vtkPolyDataMapper::New();
  mapper->SetInputConnection(sphere->GetOutputPort());
  vtkActor* actor = vtkActor::New();
  actor->SetMapper(mapper);
  Renderizador->AddViewProp(actor);
  actor->Delete();
  mapper->Delete();
  sphere->Delete();


  Connections = vtkEventQtSlotConnect::New();

  // get right mouse pressed with high priority
  Connections->Connect(qVTKGrafico->GetRenderWindow()->GetInteractor(),
                       vtkCommand::RightButtonPressEvent,
                       this,
                       SLOT(popup( vtkObject*, unsigned long, void*, void*, vtkCommand*)),
                       popup1, 1.0);
  /*
  // get right mouse pressed with high priority
  Connections->Connect(qVTK2->GetRenderWindow()->GetInteractor(),
                       vtkCommand::RightButtonPressEvent,
                       this,
                       SLOT(popup( vtkObject*, unsigned long, void*, void*, vtkCommand*)),
                       popup2, 1.0);
  */

  /*
  // connect window enter event to radio button slot
  Connections->Connect(qVTK1->GetRenderWindow()->GetInteractor(),
                       vtkCommand::EnterEvent,
                       radio1,
                       SLOT(animateClick()));

  // connect window enter event to radio button slot
  Connections->Connect(qVTK2->GetRenderWindow()->GetInteractor(),
                       vtkCommand::EnterEvent,
                       radio2,
                       SLOT(animateClick()));

  */
  // update coords as we move through the window
  Connections->Connect(qVTKGrafico->GetRenderWindow()->GetInteractor(),
                       vtkCommand::MouseMoveEvent,
                       this,
                       SLOT(updateCoords(vtkObject*)));

  /*
  // update coords as we move through the window
  Connections->Connect(qVTK2->GetRenderWindow()->GetInteractor(),
                       vtkCommand::MouseMoveEvent,
                       this,
                       SLOT(updateCoords(vtkObject*)));
  */
  Connections->PrintSelf(cout, vtkIndent());
}

GUI4::~GUI4()
{
  Renderizador->Delete();
  //Ren2->Delete();

  Connections->Delete();
}


void GUI4::updateCoords(vtkObject* obj)
{
  // get interactor
  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
  // get event position
  int event_pos[2];
  iren->GetEventPosition(event_pos);
  // update label
  QString str;
  str.sprintf("x=%d : y=%d", event_pos[0], event_pos[1]);
  coord->setText(str);
}

void GUI4::popup(vtkObject * obj, unsigned long,
           void * client_data, void *,
           vtkCommand * command)
{
  // A note about context menus in Qt and the QVTKWidget
  // You may find it easy to just do context menus on right button up,
  // due to the event proxy mechanism in place.

  // That usually works, except in some cases.
  // One case is where you capture context menu events that
  // child windows don't process.  You could end up with a second
  // context menu after the first one.

  // See QVTKWidget::ContextMenuEvent enum which was added after the
  // writing of this example.

  // get interactor
  vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);
  // consume event so the interactor style doesn't get it
  command->AbortFlagOn();
  // get popup menu
  QMenu* popupMenu = static_cast<QMenu*>(client_data);
  // get event location
  int* sz = iren->GetSize();
  int* position = iren->GetEventPosition();
  // remember to flip y
  QPoint pt = QPoint(position[0], sz[1]-position[1]);
  // map to global
  QPoint global_pt = popupMenu->parentWidget()->mapToGlobal(pt);
  // show popup menu at global point
  popupMenu->popup(global_pt);
}

void GUI4::color1(QAction* color)
{
  if(color->text() == "Background White")
    Renderizador->SetBackground(1,1,1);
  else if(color->text() == "Background Black")
    Renderizador->SetBackground(0,0,0);
  else if(color->text() == "Stereo Rendering")
  {
    Renderizador->GetRenderWindow()->SetStereoRender(!Renderizador->GetRenderWindow()->GetStereoRender());
  }
  qVTKGrafico->update();
}

/*
void GUI4::color2(QAction* color)
{
  if(color->text() == "Background White")
    this->Ren2->SetBackground(1,1,1);
  else if(color->text() == "Background Black")
    this->Ren2->SetBackground(0,0,0);
  else if(color->text() == "Stereo Rendering")
  {
    this->Ren2->GetRenderWindow()->SetStereoRender(!this->Ren2->GetRenderWindow()->GetStereoRender());
  }
  qVTK2->update();
}
*/


void GUI4::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "Quit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
      } else {
        qDebug() << "Yes was *not* clicked";
      }
}

void GUI4::on_cbTipoEd_currentIndexChanged(int index)
{
    QMessageBox* msgBox;
    msgBox  = new QMessageBox();
    msgBox->setWindowTitle("Mensaje de prueba");
    if (index==0)
    {
        msgBox->setText("Ha Seleccionado Red-Black");
        msgBox->show();
    } else if (index==1)
    {
        msgBox->setText("Ha Seleccionado AVL");
        msgBox->show();
    } else
    {
        msgBox->setText("Ha Seleccionado otros");
        msgBox->show();
    }
}

void GUI4::on_btnSeleccionarArchivo_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir diccionario"), ".", tr("Archivos de texto (*.txt)"));
    if (!fileName.isEmpty())
    {
        txtRutaArchivo->setText(fileName);
        //Cargar palabras al arbol y calcular tiempo de carga
        //cargarDatos(fileName);

        //Cargar palabras al fib heap y calcular tiempo de carga
        cargarDatosHeap(fileName);
    }
    else
    {
        QMessageBox m; m.setText("No se ha seleccionado un diccionario"); m.exec();
    }
}

//Para fibonacci Heap
void GUI4::cargarDatosHeap(QString _rutaArchivo)
{
    string rutaArchivo = _rutaArchivo.toUtf8().constData();
    std::string line;
    //RBTree<Palabra> *arbol = new RBTree<Palabra>();
    Fheap<Palabra>* fibHeap = new Fheap<Palabra>();
    ifstream myfile (rutaArchivo.c_str());

    QTime myTimer;
    myTimer.start();
    string idioma1;
    string idioma2;

    string::size_type pos;
    int rowCount = 0;
    if (myfile.is_open())
    {
      while (getline (myfile,line))
      {
          if (line.substr(0,1)!="#") //Evitar las lineas comentadas
          {
              pos=line.find("\t", 0);
              if (pos>0) //Si es menor, entonces no hay tabs
              {
                  idioma1 = line.substr(0,pos);
                  idioma2 = line.substr(pos+1);

                  // Esta parte es para agregar los elementos a la tabla
                  QString item1 = QString::fromStdString(idioma1);
                  QString item2 = QString::fromStdString(idioma2);
                  model->setItem(rowCount,0, new QStandardItem(item1));
                  model->setItem(rowCount,1, new QStandardItem(item2));

                  cout<<"Idioma1:"<<idioma1<<"Idioma2:"<<idioma2<<endl;
                  Palabra p(idioma1, idioma2);
                  fibHeap->insertar(p);
                  //this->model->setRowCount(this->model->rowCount()+1);
              }
              rowCount++;
          }
      }
      myfile.close();
    }
    else QMessageBox::information(0, "error, No se pudo abrir el archivo", QString("Error"));
    int nMilliseconds = myTimer.elapsed();
    QString s = QString::number(nMilliseconds);
    txtTiempoCarga->setText(s);
    tblDiccionario->setModel(this->model);
}



//Por el momento funciona solo con Red-Black Tree
void GUI4::cargarDatos(QString _rutaArchivo)
{
  string rutaArchivo = _rutaArchivo.toUtf8().constData();
  std::string line;
  RBTree<Palabra> *arbol = new RBTree<Palabra>();
  ifstream myfile (rutaArchivo.c_str());

  QTime myTimer;
  myTimer.start();
  string idioma1;
  string idioma2;

  string::size_type pos;
  int rowCount = 0;
  if (myfile.is_open())
  {
    while (getline (myfile,line))
    {
        if (line.substr(0,1)!="#") //Evitar las lineas comentadas
        {
            pos=line.find("\t", 0);
            if (pos>0) //Si es menor, entonces no hay tabs
            {
                idioma1 = line.substr(0,pos);
                idioma2 = line.substr(pos+1);

                QString item1 = QString::fromStdString(idioma1);
                QString item2 = QString::fromStdString(idioma2);
                model->setItem(rowCount,0, new QStandardItem(item1));
                model->setItem(rowCount,1, new QStandardItem(item2));
                cout<<"Idioma1:"<<idioma1<<"Idioma2:"<<idioma2<<endl;
                Palabra p(idioma1, idioma2);
                arbol->insertar(p);
                //this->model->setRowCount(this->model->rowCount()+1);
            }
            rowCount++;
        }
    }
    myfile.close();
  }
  else QMessageBox::information(0, "error, No se pudo abrir el archivo", QString("Error"));
  int nMilliseconds = myTimer.elapsed();
  QString s = QString::number(nMilliseconds);
  txtTiempoCarga->setText(s);
  tblDiccionario->setModel(this->model);
}

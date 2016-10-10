#include "GUI4.h"
#include <QMenu>
#include <vtkTransform.h>
#include <vtkVectorText.h>
#include <vtkTransformFilter.h>
#include <vtkPoints.h>
#include <vtkPolyLine.h>
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
#include "vtkProperty.h"
#include "vtkLight.h"
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
#include <levenshtein.h>
#include <vtkInteractorStyleRubberBandZoom.h>

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

  Connections = vtkEventQtSlotConnect::New();

  // get right mouse pressed with high priority
  Connections->Connect(qVTKGrafico->GetRenderWindow()->GetInteractor(),
                       vtkCommand::RightButtonPressEvent,
                       this,
                       SLOT(popup( vtkObject*, unsigned long, void*, void*, vtkCommand*)),
                       popup1, 1.0);

  // update coords as we move through the window
  Connections->Connect(qVTKGrafico->GetRenderWindow()->GetInteractor(),
                       vtkCommand::MouseMoveEvent,
                       this,
                       SLOT(updateCoords(vtkObject*)));


  Connections->PrintSelf(cout, vtkIndent());

  //Set up the lighting
  vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    light->SetFocalPoint(1.875,0.6125,0);
    light->SetPosition(0.875,1.6125,1);
    Renderizador->AddLight(light);


    //Esto es para probar el fibonacci heap
    fheap = new Fheap<int>();
    fheap->insertar(15);
    fheap->insertar(5);
    fheap->insertar(9);
    fheap->insertar(2);
    fheap->insertar(12);
    fheap->insertar(6);
    fheap->insertar(8);
    fheap->insertar(4);
    fheap->insertar(13);
    fheap->insertar(24);

    //fheap->mostrar();
    this->lista=0;
    this->arbol=0;
    this->avl=0;
    estructuraSeleccionada =List;
   this->lista=new Lista<Palabra>;
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


void GUI4::on_pushButton_clicked()
{
    Renderizador->ResetCamera();
    /*
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Test", "Quit?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        QApplication::quit();
      } else {
        qDebug() << "Yes was *not* clicked";
      }

      */
}

void GUI4::on_cbTipoEd_currentIndexChanged(int index)
{
    QMessageBox* msgBox;
    msgBox  = new QMessageBox();
    msgBox->setWindowTitle("Mensaje de prueba");
    this->lista=0;
    this->arbol=0;
    this->avl=0;
    
    if (index==0)
    {
        msgBox->setText("Ha Seleccionado Lista");
        msgBox->show();
        estructuraSeleccionada = List;
        this->lista=new Lista<Palabra>;

    } else if (index==1)
    {
        msgBox->setText("Arbol Binario sin Balancear");
        msgBox->show();
        estructuraSeleccionada = BST;
        //this->estructura=new Tree<Palabra>;
    } else if (index==2)
    {
        msgBox->setText("Ha Seleccionado AVL");
        msgBox->show();
        estructuraSeleccionada = Avl;
        this->avl=new AVL<Palabra>;
    } else if (index==3)
    {
        msgBox->setText("Ha Seleccionado Red-Black");
        msgBox->show();
        estructuraSeleccionada = RedBlack;
        this->arbol= new RBTree<Palabra>;
    } else if (index==4)
    {
        msgBox->setText("Ha Seleccionado Binomial Heap");
        msgBox->show();
        estructuraSeleccionada = BinomialHeap;
    } else if (index==5)
    {
        msgBox->setText("Ha Seleccionado Fibonacci Heap");
        msgBox->show();
        estructuraSeleccionada = FibonacciHeap;
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
    }
    else
    {
        QMessageBox m; m.setText("No se ha seleccionado un diccionario"); m.exec();
    }
}


//Por el momento funciona solo con Red-Black Tree
void GUI4::cargarDatosaEstructura(QString _rutaArchivo)
{
  string rutaArchivo = _rutaArchivo.toUtf8().constData();
  std::string line;

  ifstream myfile (rutaArchivo.c_str());

  QTime myTimer;
  myTimer.start();
  string idioma1;
  string idioma2;
  string::size_type pos;
  string pala;
  std::vector<string> v;
  int rowCount = 0;
 
  if (myfile.is_open())
  {
    getline(myfile,line);
    pos=line.find("\t",0);
    idioma1=line.substr(0,pos);
    pala=idioma1;
    while (idioma1!="")
    {
        if (line.substr(0,1)!="#") //Evitar las lineas comentadas
        {
          while(idioma1==pala) 
          {
          
              if (pos>0) //Si es menor, entonces no hay tabs
              {

                  idioma2 = line.substr(pos+1);
                  

                  //Esto es para agregar las palabras a la tabla
                  QString item1 = QString::fromStdString(idioma1);
                  QString item2 = QString::fromStdString(idioma2);
                  model->setItem(rowCount,0, new QStandardItem(item1));
                  model->setItem(rowCount,1, new QStandardItem(item2));
                  //cout<<"Idioma1:"<<idioma1<<"Idioma2:"<<idioma2<<endl;

                  v.push_back(idioma2);
                  pala=idioma1;
                  getline(myfile,line);
                  pos=line.find("\t",0);
                  idioma1=line.substr(0,pos);
              }

              rowCount++;
          }
          Palabra p(pala, v);
          //Se inserta segun la estructura
          
          if (estructuraSeleccionada == List)
          {
              lista->insertar(p);
          }
          else if (estructuraSeleccionada == RedBlack)
          {
              arbol->insertar(p);
          }
          pala=idioma1;
          v.clear();

        }
        else 
        {
          getline(myfile,line);
          pos=line.find("\t",0);
          idioma1=line.substr(0,pos);
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

void GUI4::graficarHeap(std::list<NodoF<int>*> listaNodos,double xpos = 0.0, double ypos = 0.0, double zpos = 0.0, bool esHijo = false)
{
    double radioEsfera = 0.5;
    int grosorArista = 2;
    vtkSmartPointer<vtkSphereSource> sphere = vtkSmartPointer<vtkSphereSource>::New();
    sphere->SetThetaResolution(100);
    sphere->SetPhiResolution(50);
    sphere->SetRadius(radioEsfera);
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    sphereMapper->SetInputConnection(sphere->GetOutputPort());

    //double xpos, ypos,zpos = 0.0;
    //Imprimir las raices
    //fheap->ver_raices();
    double puntoOrigen[3] = {xpos, ypos, zpos};
    double puntoDestino[3] = {xpos, ypos, zpos};
    if (esHijo)
    {
        puntoDestino[0] = xpos;
        puntoDestino[1] = ypos-radioEsfera*4;
        puntoDestino[2] = zpos;
    }

    //std::list<NodoF<int>* > raices = fheap->getRaices();
    for (std::list<NodoF<int>*>::const_iterator iterator = listaNodos.begin(), end = listaNodos.end(); iterator != end; ++iterator) {
        //Esto es para imprimir las raices
        std::cout << (*iterator)->valor;

        //Esto es para graficar las raices con VTK;
        vtkSmartPointer<vtkActor> nodoEsfera = vtkSmartPointer<vtkActor>::New();
          nodoEsfera->SetMapper(sphereMapper);
          nodoEsfera->GetProperty()->SetColor(1,0,0);
          nodoEsfera->GetProperty()->SetAmbient(0.3);
          nodoEsfera->GetProperty()->SetDiffuse(0.875);
          nodoEsfera->GetProperty()->SetSpecular(0.0);
          nodoEsfera->GetProperty()->SetOpacity(0.5);
          nodoEsfera->AddPosition(xpos,ypos,zpos);
        // Create text
        QString nodoTextoTmp = QString::number((*iterator)->valor);
        std::string nodoTexto = nodoTextoTmp.toUtf8().constData();
        vtkSmartPointer<vtkVectorText> textSource = vtkSmartPointer<vtkVectorText>::New();
        textSource->SetText(nodoTexto.c_str());
        textSource->Update();
        cout<<"Texto a mostrar en nodo:"<<nodoTexto.c_str()<<endl;

        vtkSmartPointer<vtkTransform> transform =
            vtkSmartPointer<vtkTransform>::New();
          //transform->PostMultiply(); //this is the key line
          transform->Scale(radioEsfera/(radioEsfera*5),radioEsfera/(radioEsfera*5),radioEsfera/(radioEsfera*5));

          vtkSmartPointer<vtkTransformFilter> transformFilter =
            vtkSmartPointer<vtkTransformFilter>::New();
          transformFilter->SetInputConnection(textSource->GetOutputPort());
          transformFilter->SetTransform(transform);

        // Create a mapper and actor for the text
        vtkSmartPointer<vtkPolyDataMapper> textMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        textMapper->SetInputConnection(transformFilter->GetOutputPort());

        vtkSmartPointer<vtkActor> actorVT = vtkSmartPointer<vtkActor>::New();
        actorVT->SetMapper(textMapper);
        actorVT->GetProperty()->SetColor(255, 255, 255);
        actorVT->AddPosition(xpos-radioEsfera/2,ypos,zpos+radioEsfera/3);

        //Lo siguiente es para agregar las aristas entre nodos
        vtkSmartPointer<vtkPoints> points =vtkSmartPointer<vtkPoints>::New();
        points->InsertNextPoint(puntoOrigen);
        points->InsertNextPoint(puntoDestino);

        //Polylineas
        vtkSmartPointer<vtkPolyLine> polyLine = vtkSmartPointer<vtkPolyLine>::New();
        polyLine->GetPointIds()->SetNumberOfIds(2);
        for(unsigned int i = 0; i < 2; i++)
        {
            polyLine->GetPointIds()->SetId(i,i);
        }

        // Create a cell array to store the lines in and add the lines to it
        vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
        cells->InsertNextCell(polyLine);

        // Create a polydata to store everything in
        vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();

        // Add the points to the dataset
        polyData->SetPoints(points);

        // Add the lines to the dataset
        polyData->SetLines(cells);

        // Setup actor and mapper
        vtkSmartPointer<vtkPolyDataMapper> linesMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

        #if VTK_MAJOR_VERSION <= 5
          linesMapper->SetInput(polyData);
        #else
          linesMapper->SetInputData(polyData);
        #endif


        vtkSmartPointer<vtkActor> linesActor = vtkSmartPointer<vtkActor>::New();
        linesActor->GetProperty()->SetColor(255, 255, 255);
        linesActor->SetMapper(linesMapper);
        linesActor->GetProperty()->SetLineWidth(grosorArista);


        //Agregamos los actores al renderizador
        Renderizador->AddActor(nodoEsfera);
        Renderizador->AddActor(linesActor);
        Renderizador->AddActor(actorVT);

        //Graficamos los hijos del nodo;
        if ((*iterator)->get_grado()>0)
        {
            graficarHeap((*iterator)->hijos, xpos, ypos, zpos, true);
        }
        puntoOrigen[0] = xpos+radioEsfera;
        puntoOrigen[1] = ypos;
        puntoOrigen[2] = zpos;
        puntoDestino[0] = xpos+(radioEsfera*3)*((*iterator)->get_grado()>0 ? (*iterator)->get_grado():1); //Agregamos mas espacio segun la cantidad de hijos
        puntoDestino[1] = ypos;
        puntoDestino[2] = zpos;
        xpos += radioEsfera*4*((*iterator)->get_grado()>0 ? (*iterator)->get_grado():1);
    }
    //Renderizador->GetActiveCamera()->SetFocalPoint(0,0,0);
    //Renderizador->GetActiveCamera()->SetPosition(0,0,1);
    //Renderizador->GetActiveCamera()->SetViewUp(0,1,0);
    //Renderizador->GetActiveCamera()->ParallelProjectionOn();
    Renderizador->ResetCamera();
    //Renderizador->GetActiveCamera()->SetParallelScale(1.5);
}

void GUI4::on_btnCargar_clicked()
{
    //Cargar palabras al arbol y calcular tiempo de carga
    //cargarDatos(fileName);

    //Cargar palabras al fib heap y calcular tiempo de carga
    QString fileName = txtRutaArchivo->text();
    cargarDatosaEstructura(fileName);
    //graficarHeap(fheap->getRaices());
}

void GUI4::on_btnBuscar_clicked()
{
    model->clear();
    //Esto es para la busqueda
    lista->begin();
    int rowCount = 0;
    // Either this if you use UTF-8 anywhere
    std::string palabra = (txtPalabra->text()).toUtf8().constData();
    cout<<"Palabra:"<<palabra<<endl;
    int radio = spbRadio->value();
    cout<<"Radio de busqueda:"<<radio<<endl;

    QTime tiempoBusqueda;
    tiempoBusqueda.start();
    cout<<"bp"<<endl<<"   "<<lista->terminate()<<endl;
    bool paso=false;
    int nMilliseconds;
    for (;!lista->terminate();lista->next())
    {
        //cout<<"IMPL:"<<lista->getData().idioma1<<endl;
        if (paso==false)
        {
          if (lista->getData().idioma1==palabra)
            paso=true;
            nMilliseconds=tiempoBusqueda.elapsed();
        }
        if (distanciaLevenshtein(lista->getData().idioma1, palabra) <= radio)
            //|| distanciaLevenshtein(lista->getData().idioma2.at(0), palabra) <= radio)
        {
            //Estoes para agregarlos a la tabla

            string idioma1 = lista->getData().idioma1;
            vector<string> id2=lista->getData().idioma2;
            for (std::vector<string>::iterator i=id2.begin();i!=id2.end();i++)
            {
              string idioma2 = (*i);

              //Esto es para agregar las palabras a la tabla
              QString item1 = QString::fromStdString(idioma1);
              QString item2 = QString::fromStdString(idioma2);
              model->setItem(rowCount,0, new QStandardItem(item1));
              model->setItem(rowCount,1, new QStandardItem(item2));
              rowCount++;              
            }

        }

    }



    

    //int nMilliseconds = tiempoBusqueda.elapsed();
    QString s = QString::number(nMilliseconds);
    txtTiempoBusqueda->setText(s);
    tblDiccionario->setModel(this->model);
}

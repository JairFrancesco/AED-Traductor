#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <rbnode.h>
#include <rbtree.h>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void cargarDatos(QString _rutaArchivo);

private slots: 


    void on_btnOpenFile_clicked();

    void on_cbTiposEDs_currentIndexChanged(int index);

    void on_txtPalabra_returnPressed();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model = new QStandardItemModel();

};

#endif // MAINWINDOW_H

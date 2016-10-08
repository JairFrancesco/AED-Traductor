/********************************************************************************
** Form generated from reading UI file 'GUI4.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI4_H
#define UI_GUI4_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QAction *actionExit;
    QAction *actionE_xit;
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QRadioButton *radio1;
    QRadioButton *radio2;
    QHBoxLayout *hboxLayout1;
    QVTKWidget *qVTK1;
    QVTKWidget *qVTK2;
    QLabel *coord;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(627, 316);
        actionExit = new QAction(GUI);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionE_xit = new QAction(GUI);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        centralwidget = new QWidget(GUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        radio1 = new QRadioButton(centralwidget);
        radio1->setObjectName(QString::fromUtf8("radio1"));

        hboxLayout->addWidget(radio1);

        radio2 = new QRadioButton(centralwidget);
        radio2->setObjectName(QString::fromUtf8("radio2"));

        hboxLayout->addWidget(radio2);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        qVTK1 = new QVTKWidget(centralwidget);
        qVTK1->setObjectName(QString::fromUtf8("qVTK1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qVTK1->sizePolicy().hasHeightForWidth());
        qVTK1->setSizePolicy(sizePolicy);

        hboxLayout1->addWidget(qVTK1);

        qVTK2 = new QVTKWidget(centralwidget);
        qVTK2->setObjectName(QString::fromUtf8("qVTK2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(qVTK2->sizePolicy().hasHeightForWidth());
        qVTK2->setSizePolicy(sizePolicy1);

        hboxLayout1->addWidget(qVTK2);


        vboxLayout->addLayout(hboxLayout1);

        coord = new QLabel(centralwidget);
        coord->setObjectName(QString::fromUtf8("coord"));
        coord->setAlignment(Qt::AlignCenter);

        vboxLayout->addWidget(coord);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        vboxLayout->addWidget(pushButton);

        GUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GUI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 627, 25));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        GUI->setMenuBar(menubar);
        statusbar = new QStatusBar(GUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GUI->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(actionE_xit);

        retranslateUi(GUI);
        QObject::connect(actionE_xit, SIGNAL(triggered()), GUI, SLOT(close()));

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QMainWindow *GUI)
    {
        GUI->setWindowTitle(QApplication::translate("GUI", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("GUI", "Exit", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("GUI", "E&xit", 0, QApplication::UnicodeUTF8));
        radio1->setText(QApplication::translate("GUI", "Mouse in Window 1", 0, QApplication::UnicodeUTF8));
        radio2->setText(QApplication::translate("GUI", "Mouse in Window 2", 0, QApplication::UnicodeUTF8));
        coord->setText(QApplication::translate("GUI", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("GUI", "PushButton", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("GUI", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI4_H

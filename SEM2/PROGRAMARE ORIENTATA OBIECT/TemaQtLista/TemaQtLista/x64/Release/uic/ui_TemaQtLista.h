/********************************************************************************
** Form generated from reading UI file 'TemaQtLista.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMAQTLISTA_H
#define UI_TEMAQTLISTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemaQtListaClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TemaQtListaClass)
    {
        if (TemaQtListaClass->objectName().isEmpty())
            TemaQtListaClass->setObjectName(QString::fromUtf8("TemaQtListaClass"));
        TemaQtListaClass->resize(600, 400);
        menuBar = new QMenuBar(TemaQtListaClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TemaQtListaClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TemaQtListaClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TemaQtListaClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TemaQtListaClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TemaQtListaClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TemaQtListaClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TemaQtListaClass->setStatusBar(statusBar);

        retranslateUi(TemaQtListaClass);

        QMetaObject::connectSlotsByName(TemaQtListaClass);
    } // setupUi

    void retranslateUi(QMainWindow *TemaQtListaClass)
    {
        TemaQtListaClass->setWindowTitle(QCoreApplication::translate("TemaQtListaClass", "TemaQtLista", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TemaQtListaClass: public Ui_TemaQtListaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMAQTLISTA_H

/********************************************************************************
** Form generated from reading UI file 'TemaQt.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMAQT_H
#define UI_TEMAQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TemaQtClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TemaQtClass)
    {
        if (TemaQtClass->objectName().isEmpty())
            TemaQtClass->setObjectName(QString::fromUtf8("TemaQtClass"));
        TemaQtClass->resize(600, 400);
        menuBar = new QMenuBar(TemaQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        TemaQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TemaQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TemaQtClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(TemaQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        TemaQtClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TemaQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TemaQtClass->setStatusBar(statusBar);

        retranslateUi(TemaQtClass);

        QMetaObject::connectSlotsByName(TemaQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *TemaQtClass)
    {
        TemaQtClass->setWindowTitle(QCoreApplication::translate("TemaQtClass", "TemaQt", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TemaQtClass: public Ui_TemaQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMAQT_H

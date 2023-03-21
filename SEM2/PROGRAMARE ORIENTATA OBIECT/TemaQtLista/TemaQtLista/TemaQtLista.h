#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TemaQtLista.h"

class TemaQtLista : public QMainWindow
{
    Q_OBJECT

public:
    TemaQtLista(QWidget *parent = Q_NULLPTR);

private:
    Ui::TemaQtListaClass ui;
};

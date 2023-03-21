#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TemaQt.h"

class TemaQt : public QMainWindow
{
    Q_OBJECT

public:
    TemaQt(QWidget *parent = Q_NULLPTR);

private:
    Ui::TemaQtClass ui;
};

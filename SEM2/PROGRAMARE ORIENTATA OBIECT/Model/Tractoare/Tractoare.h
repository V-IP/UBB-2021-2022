#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tractoare.h"

class Tractoare : public QMainWindow
{
    Q_OBJECT

public:
    Tractoare(QWidget *parent = nullptr);
    ~Tractoare();

private:
    Ui::TractoareClass ui;
};

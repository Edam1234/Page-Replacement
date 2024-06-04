#pragma once

#include <QtWidgets/QWidget>
#include "ui_EX_3.h"
#include<QTableWidget>
#include<vector>
#include<random>
#include <algorithm>
#include<qdebug.h>
#include<qpushbutton.h>
#include<qqueue.h>
class EX_3 : public QWidget
{
    Q_OBJECT

public:
    EX_3(QWidget *parent = nullptr);
    ~EX_3();
    void FIFO();
    void LRU();
    void LFU();
    void OPT();
    void table(); 
    void  RandomSequence();

private:
    Ui::EX_3Class ui;
    int Length;
    std::vector<int> sequence;
};

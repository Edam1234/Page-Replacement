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
#include<unordered_map>
#include <unordered_map>
#include <list>
#include <queue>
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
    void Begin();
private:
    Ui::EX_3Class ui;
    int Length;std::vector<int> sequence;

    
};

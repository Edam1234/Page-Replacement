#include "EX_3.h"

EX_3::EX_3(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    resize(1600, 1000);
    table();
    connect(ui.pushButton_3, &QPushButton::clicked, this, &EX_3::RandomSequence);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &EX_3::FIFO);
}

EX_3::~EX_3()
{}

void EX_3::FIFO()
{
    int count = 0;
    //for (int i = 1; i < Length + 1; i++) {
    //      QString text = QString::number(sequence[i]);
    //    if (i == 1) {
    //        ui.tableWidget->setItem(i, i - 1, new QTableWidgetItem(text));
    //        ui.tableWidget->setItem(i, 4, new QTableWidgetItem("Page Fault"));
    //        count++;
    //    }
    //    if (i > 1) {

    //    }
    //}
    QQueue<QPair<int, int>> insertionQueue;

    for (int i = 1; i < Length + 1; i++) {
        QString text1 = QString::number(sequence[i - 1]);
        bool found = false;
        if (i == 1) {
            ui.tableWidget->setItem(i, i - 1, new QTableWidgetItem(text1));
            ui.tableWidget->setItem(i, 4, new QTableWidgetItem("Page Fault"));
            count++;
        }
        int value = 0;
        int clu = 0;
        if (1 > 1) {
            
            for (int j = 0; j < 3; j++) {
                if (ui.tableWidget->item(i, j)->text() != NULL) {
                    if (ui.tableWidget->item(i, j)->text() == text1) {
                        value++;
                        clu = j;
                    }
                } 
            }
            if (value > 0||i>3) {

            }
            if (value > 0 || i < 3) {
            }
        }

    }
}

void EX_3::LRU()
{
}

void EX_3::LFU()
{
}

void EX_3::OPT()
{
}

void EX_3::table()
{
 
    ui.tableWidget->setFixedSize(750, 400);
    ui.tableWidget_3->setFixedSize(750, 400);
    ui.tableWidget_2->setFixedSize(750, 400);
    ui.tableWidget_4->setFixedSize(750, 400);
    ui.tableWidget->setGeometry(0, 0, 400, 300);
    ui.tableWidget_2->setGeometry(770, 0, 400, 300);
    ui.tableWidget_4->setGeometry(770, 420, 400, 300);
    ui.tableWidget_3->setGeometry(0, 420, 400, 300);
    ui.tableWidget_5->setFixedSize(800, 125);
    ui.tableWidget_5->setGeometry(770, 840, 400, 300);


    for (int i = 0; i < 3; i++) {
        ui.tableWidget->setColumnWidth(i, 105);
        ui.tableWidget_2->setColumnWidth(i, 105);
        ui.tableWidget_3->setColumnWidth(i, 105);
        ui.tableWidget_4->setColumnWidth(i, 105);


    }
    for (int i = 3; i < 5; i++) {
        ui.tableWidget->setColumnWidth(i, 120);
        ui.tableWidget_2->setColumnWidth(i, 120);
        ui.tableWidget_3->setColumnWidth(i, 120);
        ui.tableWidget_4->setColumnWidth(i, 120);

    }


}

void EX_3::RandomSequence()
{
    int length = 7;
    Length = length;
    std::vector<int> inputNumbers = { 1, 2, 3, 4 };
    sequence = inputNumbers;
    // 随机数生成器
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dis(0, sequence.size());

    // 随机插入数字直到达到指定长度
    while (sequence.size() < length) {
        for (int num : inputNumbers) {
            if (sequence.size() >= length) break;
            // 生成一个随机位置
            int pos = dis(rng);
            // 在随机位置插入数字
            sequence.insert(sequence.begin() + pos, num);
            // 更新分布范围
            dis = std::uniform_int_distribution<>(0, sequence.size());
        }
    }

    // 如果长度超过指定长度，截断到指定长度
    sequence.resize(length);

    // 使用固定种子打乱序列
    int seed = 1000;
    std::mt19937 shuffle_rng(seed);
    std::shuffle(sequence.begin(), sequence.end(), shuffle_rng);

    // 打印结果
    for (int num : sequence) {
        qDebug() << num << " ";
    }

    // 插入新行并设置行头
    for (int i = 0; i < length; i++) {
        ui.tableWidget->insertRow( i + 1);
        ui.tableWidget_2->insertRow(i + 1);
        ui.tableWidget_3->insertRow( i + 1);
        ui.tableWidget_4->insertRow( i + 1);

        QString text = QString::number(sequence[i]);
        ui.tableWidget->setVerticalHeaderItem( i + 1, new QTableWidgetItem(text));
        ui.tableWidget_2->setVerticalHeaderItem( i + 1, new QTableWidgetItem(text));
        ui.tableWidget_3->setVerticalHeaderItem( i + 1, new QTableWidgetItem(text));
        ui.tableWidget_4->setVerticalHeaderItem( i + 1, new QTableWidgetItem(text));
    }
}


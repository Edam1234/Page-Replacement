#include "EX_3.h"

EX_3::EX_3(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    resize(1600, 1000);

    table();
    connect(ui.pushButton_3, &QPushButton::clicked, this, &EX_3::RandomSequence);
    connect(ui.pushButton_4, &QPushButton::clicked, this, &EX_3::Begin);
}

EX_3::~EX_3()
{}

/*void EX_3::FIFO()
{
    int count = 0;
    int cun = 0;    
    for (int i = 1; i < Length + 1; i++) {
        QString text1 = QString::number(sequence[i - 1]);
        if (i == 1) {
            ui.tableWidget->setItem(i, cun, new QTableWidgetItem(text1));
            ui.tableWidget->setItem(i, 4, new QTableWidgetItem("Page Fault"));
            count++;
            cun++;
        }
        int Equal = 0;
        if (i > 1) {


            for (int j = 0; j < 3; j++) {
                if (ui.tableWidget->item(i - 1, j) != NULL) {
                    if (ui.tableWidget->item(i - 1, j)->text() == text1) {
                        Equal++;

                    }
                }
            }
            for (int k = 0; k < 3; k++) {
                QTableWidgetItem* item = ui.tableWidget->item(i - 1, k);
                if (item != NULL) {
                    QString tex = item->text();
                    qDebug() << tex;
                    ui.tableWidget->setItem(i, k, new QTableWidgetItem(tex));
                }
            }
            if (Equal > 0) {
                ui.tableWidget->setItem(i, 4, new QTableWidgetItem("Page Not Fault"));
            }
            else {
                if (cun < 3) {
                    ui.tableWidget->setItem(i, cun, new QTableWidgetItem(text1));
                    ui.tableWidget->setItem(i, 4, new QTableWidgetItem("Page  Fault"));
                    cun++;
                }
                
            }

        }
        if (cun == 3) {
            cun = 0;
        }

    }

}
   */ 
void EX_3::FIFO() {
    int count = 0;
    int frameSize = 3;

    std::vector<int> frames(frameSize, -1); // ��ʼ��ҳ���ܣ�-1��ʾ��
    int nextReplaceIndex = 0; // ��һ��Ҫ�滻�Ŀ������

    for (int i = 1; i <= Length; i++) {
        QString text1 = QString::number(sequence[i - 1]);
        bool pageFault = true;

        // ���ҳ���Ƿ��Ѿ��ڿ����
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == sequence[i - 1]) {
                pageFault = false;
                break;
            }
        }

        if (pageFault) {
            // �滻ҳ��
            frames[nextReplaceIndex] = sequence[i - 1];
            nextReplaceIndex = (nextReplaceIndex + 1) % frameSize;
            count++;
        }

        // ����UI���������
        for (int j = 0; j < frameSize; j++) {
            QString frameText = frames[j] != -1 ? QString::number(frames[j]) : " ";
            ui.tableWidget->setItem(i, j, new QTableWidgetItem(frameText));
        }

        // ���µ����У���ʾ�Ƿ���ҳ�����
        ui.tableWidget->setItem(i, 4, new QTableWidgetItem(pageFault ? "Page Fault" : "Page Not Fault"));
    }
    
    
    double pageFaultRate = static_cast<double>(count) / Length*100;
    QString text = QString::number(pageFaultRate)+'%';
    ui.tableWidget_5->setItem(0, 0, new QTableWidgetItem(text));
    qDebug() << "Total Page Faults: " << count;
}
void EX_3::LRU() {
    int count = 0;
    int frameSize = 3;

    std::vector<int> frames(frameSize, -1); // ��ʼ��ҳ���ܣ�-1��ʾ��
    std::list<int> lruList; // ���ڸ���ҳ���ʹ�����
    std::unordered_map<int, std::list<int>::iterator> pageMap; // ���ڿ��ٷ���ҳ���������е�λ��

    for (int i = 1; i <= Length; i++) {
        int currentPage = sequence[i - 1];
        QString text1 = QString::number(currentPage);
        bool pageFault = true;

        // ���ҳ���Ƿ��Ѿ��ڿ����
        if (pageMap.find(currentPage) != pageMap.end()) {
            // ҳ���ڿ���У�����LRU����
            lruList.erase(pageMap[currentPage]);
            lruList.push_front(currentPage);
            pageMap[currentPage] = lruList.begin();
            pageFault = false;
        }
        else {
            // ҳ�治�ڿ���У�����ȱҳ
            if (lruList.size() < frameSize) {
                // ���δ����ֱ�Ӳ�����ҳ��
                lruList.push_front(currentPage);
                frames[lruList.size() - 1] = currentPage;
            }
            else {
                // ����������滻���δʹ�õ�ҳ��
                int lruPage = lruList.back();
                lruList.pop_back();
                pageMap.erase(lruPage);

                for (int j = 0; j < frameSize; j++) {
                    if (frames[j] == lruPage) {
                        frames[j] = currentPage;
                        break;
                    }
                }

                lruList.push_front(currentPage);
            }

            pageMap[currentPage] = lruList.begin();
            count++;
        }

        // ����UI���������
        for (int j = 0; j < frameSize; j++) {
            QString frameText = frames[j] != -1 ? QString::number(frames[j]) : " ";
            ui.tableWidget_2->setItem(i, j, new QTableWidgetItem(frameText));
        }

        // ���µ����У���ʾ�Ƿ���ҳ�����
        ui.tableWidget_2->setItem(i, 4, new QTableWidgetItem(pageFault ? "Page Fault" : "Page Not Fault"));
    }
    double pageFaultRate = static_cast<double>(count) / Length * 100;
    QString text = QString::number(pageFaultRate) + '%';
    ui.tableWidget_5->setItem(0, 1, new QTableWidgetItem(text));
    qDebug() << "Total Page Faults: " << count;
}

void EX_3::LFU() {
    int count = 0;
    int frameSize = 3;

    std::vector<int> frames(frameSize, -1); // ��ʼ��ҳ���ܣ�-1��ʾ��
    std::unordered_map<int, int> freqMap; // ���ڸ���ҳ��ķ���Ƶ��
    std::unordered_map<int, int> posMap; // ���ڸ���ҳ���ڿ���е�λ��
    auto cmp = [&freqMap](int a, int b) { return freqMap[a] > freqMap[b]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> minHeap(cmp); // ��С�������ҵ�����Ƶ����͵�ҳ��

    for (int i = 1; i <= Length; i++) {
        int currentPage = sequence[i - 1];
        QString text1 = QString::number(currentPage);
        bool pageFault = true;

        // ���ҳ���Ƿ��Ѿ��ڿ����
        if (freqMap.find(currentPage) != freqMap.end()) {
            // ҳ���ڿ���У����ӷ���Ƶ��
            freqMap[currentPage]++;
            pageFault = false;
        }
        else {
            // ҳ�治�ڿ���У�����ȱҳ
            if (minHeap.size() < frameSize) {
                // ���δ����ֱ�Ӳ�����ҳ��
                frames[minHeap.size()] = currentPage;
                posMap[currentPage] = minHeap.size();
            }
            else {
                // ����������滻����Ƶ����͵�ҳ��
                while (!minHeap.empty() && posMap[minHeap.top()] == -1) {
                    minHeap.pop();
                }

                if (!minHeap.empty()) {
                    int lfuPage = minHeap.top();
                    minHeap.pop();
                    int replaceIndex = posMap[lfuPage];
                    frames[replaceIndex] = currentPage;
                    posMap.erase(lfuPage);
                    posMap[currentPage] = replaceIndex;
                }
            }

            freqMap[currentPage] = 1;
            minHeap.push(currentPage);
            count++;
        }

        // ����UI���������
        for (int j = 0; j < frameSize; j++) {
            QString frameText = frames[j] != -1 ? QString::number(frames[j]) : " ";
            ui.tableWidget_3->setItem(i, j, new QTableWidgetItem(frameText));
        }

        // ���µ����У���ʾ�Ƿ���ҳ�����
        ui.tableWidget_3->setItem(i, 4, new QTableWidgetItem(pageFault ? "Page Fault" : "Page Not Fault"));
    }
    double pageFaultRate = static_cast<double>(count) / Length * 100;
    QString text = QString::number(pageFaultRate) + '%';
    ui.tableWidget_5->setItem(0, 2, new QTableWidgetItem(text));
    qDebug() << "Total Page Faults: " << count;
}
void EX_3::OPT() {
    int count = 0;
    int frameSize = 3;

    std::vector<int> frames(frameSize, -1); // ��ʼ��ҳ���ܣ�-1��ʾ��
    int cun = 0; // ��ǰҳ��������ʹ�õ�ҳ����

    for (int i = 1; i <= Length; i++) {
        QString text1 = QString::number(sequence[i - 1]);
        bool pageFault = true;

        // ���ҳ���Ƿ��Ѿ��ڿ����
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == sequence[i - 1]) {
                pageFault = false;
                break;
            }
        }

        if (pageFault) {
            if (cun < frameSize) {
                // ���ҳ����δ����ֱ�Ӳ�����ҳ��
                frames[cun] = sequence[i - 1];
                cun++;
            }
            else {
                // ҳ����������ѡ��δ����ò��ٱ����ʵ�ҳ������滻
                std::vector<int> futureUse(frameSize, Length + 1); // ��ʼ��Ϊһ���ϴ��ֵ����ʾδ�������ٱ�����
                for (int j = 0; j < frameSize; j++) {
                    for (int k = i; k < Length; k++) {
                        if (frames[j] == sequence[k]) {
                            futureUse[j] = k;
                            break;
                        }
                    }
                }

                // �ҳ�δ����ò��ٱ����ʵ�ҳ��
                int replaceIndex = 0;
                int maxFutureUse = futureUse[0];
                for (int j = 1; j < frameSize; j++) {
                    if (futureUse[j] > maxFutureUse) {
                        maxFutureUse = futureUse[j];
                        replaceIndex = j;
                    }
                }

                frames[replaceIndex] = sequence[i - 1];
            }
            count++;
        }

        // ����UI���������
        for (int j = 0; j < frameSize; j++) {
            QString frameText = frames[j] != -1 ? QString::number(frames[j]) : " ";
            ui.tableWidget_4->setItem(i, j, new QTableWidgetItem(frameText));
        }

        // ���µ����У���ʾ�Ƿ���ҳ�����
        ui.tableWidget_4->setItem(i, 4, new QTableWidgetItem(pageFault ? "Page Fault" : "Page Not Fault"));
    }
    double pageFaultRate = static_cast<double>(count) / Length * 100;
    QString text = QString::number(pageFaultRate) + '%';
    ui.tableWidget_5->setItem(0, 3, new QTableWidgetItem(text));
    qDebug() << "Total Page Faults: " << count;
}

void EX_3::table()
{
    int frameSize = 3;
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
    int length = 8;
    
    Length = length;
    std::vector<int> inputNumbers = { 1, 2, 3, 4,5,6 };
    sequence = inputNumbers;
    // �����������
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dis(0, sequence.size());

    // �����������ֱ���ﵽָ������
    while (sequence.size() < length) {
        for (int num : inputNumbers) {
            if (sequence.size() >= length) break;
            // ����һ�����λ��
            int pos = dis(rng);
            // �����λ�ò�������
            sequence.insert(sequence.begin() + pos, num);
            // ���·ֲ���Χ
            dis = std::uniform_int_distribution<>(0, sequence.size());
        }
    }

    // ������ȳ���ָ�����ȣ��ضϵ�ָ������
    sequence.resize(length);

    // ʹ�ù̶����Ӵ�������
    int seed = 1000;
    std::mt19937 shuffle_rng(seed);
    std::shuffle(sequence.begin(), sequence.end(), shuffle_rng);

    // ��ӡ���
    //for (int num : sequence) {
    //    qDebug() << num << " ";
    //}

    // �������в�������ͷ
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

void EX_3::Begin()
{
    FIFO();
    LRU();
    LFU();
    OPT();
}


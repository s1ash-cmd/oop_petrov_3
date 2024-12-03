#ifndef PETROV_WIDGET_H
#define PETROV_WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QPainter>
#include <QScrollArea>
#include <fstream>
#include <vector>
#include <memory>

#include "petrov_item.h"
#include "petrov_used_item.h"
#include "petrov_header.h"

using namespace std;

class petrov_widget : public QWidget {
    Q_OBJECT

    vector<shared_ptr<item>> items; // Вектор умных указателей на элементы

public:
    explicit petrov_widget(QWidget *parent = nullptr);

    void loadFromFile(); // Метод для загрузки данных из файла
    void saveToFile(); // Метод для сохранения данных в файл
    void clearItems(); // Метод для очистки списка элементов

    const vector<shared_ptr<item>>& getItems() const {
        return items;
    }

protected:
    void paintEvent(QPaintEvent *event) override; // Переопределение метода для отрисовки

private:
    static void drawRow(const shared_ptr<item>& itemPtr, QPainter& painter, QVector<int>& columnWidths, int row, int rowHeight, int startX, int startY);
};





#endif // PETROV_WIDGET_H

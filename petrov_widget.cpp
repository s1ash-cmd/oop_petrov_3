#include "petrov_widget.h"
#include "petrov_header.h"

#include <algorithm>
#include <sstream>
#include <QFontMetrics>
#include <functional>
#include <vector>

using namespace std;

petrov_widget::petrov_widget(QWidget *parent) : QWidget(parent) {

}

void petrov_widget::loadFromFile() {
    QString filename = QFileDialog::getOpenFileName(nullptr, "Открыть файл", "", "Text Files (*.txt);;Все Файлы (*)");
    if (filename.isEmpty()) {
        return;
    }

    ifstream fin(filename.toStdString());
    if (!fin) {
        QMessageBox::critical(nullptr, "Ошибка", "Невозможно открыть файл");
        return;
    }

    try {
        boost::archive::text_iarchive ia(fin);
        ia >> items;
        fin.close();
        QMessageBox::information(nullptr, "Успех", "Товары успешно загружены из файла.");

        update();

    } catch (const exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", QString("Ошибка чтения из файла: %1").arg(e.what()));
        fin.close();
    }
}

void petrov_widget::saveToFile() {
    if (items.empty()) {
        QMessageBox::warning(nullptr, "Предупреждение", "Список товаров пуст. Сохранение невозможно.");
        return;
    }

    QString filename = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", "", "Text Files (*.txt);;Все Файлы (*)");
    if (filename.isEmpty()) {
        return;
    }

    ofstream fout(filename.toStdString());
    if (!fout) {
        QMessageBox::critical(nullptr, "Ошибка", "Невозможно открыть файл для записи");
        return;
    }

    try {
        boost::archive::text_oarchive oa(fout);
        oa << items;
        fout.close();
        QMessageBox::information(nullptr, "Успех", "Товары успешно сохранены в файл.");
    } catch (const exception &e) {
        QMessageBox::critical(nullptr, "Ошибка", QString("Ошибка записи в файл: %1").arg(e.what()));
        fout.close();
    }
}

void petrov_widget::clearItems(){
    items.clear();
    setMinimumSize(0, 0);
    update();
}

void updateColumnWidths(const shared_ptr<item>& itemPtr, QVector<int>& columnWidths, const QFontMetrics& metrics) {
    columnWidths[0] = max(columnWidths[0], metrics.horizontalAdvance(QString::fromStdString(itemPtr->name)) + 20);
    columnWidths[1] = max(columnWidths[1], metrics.horizontalAdvance(QString::number(itemPtr->weight)) + 20);
    columnWidths[2] = max(columnWidths[2], metrics.horizontalAdvance(QString::number(itemPtr->width)) + 20);
    columnWidths[3] = max(columnWidths[3], metrics.horizontalAdvance(QString::number(itemPtr->height)) + 20);
    columnWidths[4] = max(columnWidths[4], metrics.horizontalAdvance(QString::number(itemPtr->price)) + 20);
    columnWidths[5] = max(columnWidths[5], metrics.horizontalAdvance(itemPtr->stock ? "Да" : "Нет") + 20);

    auto usedItemPtr = dynamic_pointer_cast<used_item>(itemPtr);
    if (usedItemPtr) {
        columnWidths[6] = max(columnWidths[6], metrics.horizontalAdvance(QString::number(usedItemPtr->age)) + 20);
        columnWidths[7] = max(columnWidths[7], metrics.horizontalAdvance(QString::number(usedItemPtr->condition)) + 20);
        columnWidths[8] = max(columnWidths[8], metrics.horizontalAdvance(QString::fromStdString(usedItemPtr->description)) + 10);
    }
}

void petrov_widget::drawRow(const shared_ptr<item>& itemPtr, QPainter& painter, QVector<int>& columnWidths, int row, int rowHeight, int startX, int startY) {
    int yPosition = startY + row * rowHeight + rowHeight / 2;
    int xPosition = startX;

    painter.drawText(xPosition, yPosition, QString::fromStdString(itemPtr->name));
    xPosition += columnWidths[0];

    painter.drawText(xPosition, yPosition, QString::number(itemPtr->weight));
    xPosition += columnWidths[1];

    painter.drawText(xPosition, yPosition, QString::number(itemPtr->width));
    xPosition += columnWidths[2];

    painter.drawText(xPosition, yPosition, QString::number(itemPtr->height));
    xPosition += columnWidths[3];

    painter.drawText(xPosition, yPosition, QString::number(itemPtr->price));
    xPosition += columnWidths[4];

    painter.drawText(xPosition, yPosition, itemPtr->stock ? "Да" : "Нет");
    xPosition += columnWidths[5];

    auto usedItemPtr = dynamic_pointer_cast<used_item>(itemPtr);
    if (usedItemPtr) {
        painter.drawText(xPosition, yPosition, QString::number(usedItemPtr->age));
        xPosition += columnWidths[6];

        painter.drawText(xPosition, yPosition, QString::number(usedItemPtr->condition));
        xPosition += columnWidths[7];

        painter.drawText(xPosition, yPosition, QString::fromStdString(usedItemPtr->description));
    }
}

void petrov_widget::paintEvent(QPaintEvent *event) {
    if (items.empty()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setPointSize(11);
    painter.setFont(font);

    int rowHeight = 30;
    int startX = 10;
    int startY = 10;

    QStringList headers = {"Название", "Вес", "Ширина", "Высота", "Цена", "В наличии", "Возраст", "Состояние", "Описание"};
    QVector<int> columnWidths(headers.size(), 0);
    QFontMetrics metrics(painter.font());

    for (int i = 0; i < headers.size(); ++i) {
        columnWidths[i] = metrics.horizontalAdvance(headers[i]) + 10;
    }

    for_each(items.begin(), items.end(), [&](const shared_ptr<item>& itemPtr) {
        updateColumnWidths(itemPtr, columnWidths, metrics);
    });

    int totalWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0) + 20;
    int totalHeight = (items.size() + 1) * rowHeight + 20;
    setMinimumSize(totalWidth, totalHeight);

    for (int i = 0; i < headers.size(); ++i) {
        painter.drawText(startX + accumulate(columnWidths.begin(), columnWidths.begin() + i, 0),startY + rowHeight / 2, headers[i]);
    }

    int row = 1;
    for_each(items.begin(), items.end(), [&](const shared_ptr<item>& itemPtr) {
        drawRow(itemPtr, painter, columnWidths, row, rowHeight, startX, startY);
        row++;
    });
}

void petrov_widget::update() {
    repaint();
}

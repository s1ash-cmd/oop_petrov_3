#include "petrov_widget.h"
#include "petrov_header.h"

#include <algorithm>
#include <sstream>
#include <QFontMetrics>
#include <sstream>
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
    update();
}

void petrov_widget::paintEvent(QPaintEvent *event) {
    if (items.empty()) {
        return;
    }

    QPainter painter(this);
    int y = 40;
    QVector<int> columnWidths(8, 0);

    painter.setFont(QFont("Arial", 10, QFont::Bold));

    QStringList headers = {"Вес", "Ширина", "Высота", "Цена", "В наличии",
                           "Возраст", "Состояние", "Описание"};

    QVector<QVector<QString>> rows;
    for (const auto& it : items) {
        ostringstream oss;
        it->output(oss);
        QString itemInfo = QString::fromStdString(oss.str());
        QStringList lines = itemInfo.split("\n");

        QString weight, width, height, price, availability, age, condition, description;
        for (const QString& line : lines) {
            if (line.contains("Вес:")) weight = line.split(":")[1].trimmed();
            else if (line.contains("Ширина:")) width = line.split(":")[1].trimmed();
            else if (line.contains("Высота:")) height = line.split(":")[1].trimmed();
            else if (line.contains("Цена:")) price = line.split(":")[1].trimmed();
            else if (line.contains("В наличии:")) availability = line.split(":")[1].trimmed();
            else if (line.contains("Возраст:")) age = line.split(":")[1].trimmed();
            else if (line.contains("Состояние:")) condition = line.split(":")[1].trimmed();
            else if (line.contains("Описание:")) description = line.split(":")[1].trimmed();
        }

        rows.append({weight, width, height, price, availability, age, condition, description});
    }

    for (int col = 0; col < headers.size(); ++col) {
        int maxWidth = painter.fontMetrics().horizontalAdvance(headers[col]);
        for (const auto& row : rows) {
            maxWidth = max(maxWidth, painter.fontMetrics().horizontalAdvance(row[col]));
        }
        columnWidths[col] = maxWidth + 20;
    }

    int x = 10;
    for (int col = 0; col < headers.size(); ++col) {
        painter.drawText(x, y, headers[col]);
        x += columnWidths[col];
    }

    painter.setFont(QFont("Arial", 10));
    for (const auto& row : rows) {
        y += 30;
        x = 10;
        for (int col = 0; col < row.size(); ++col) {
            painter.drawText(x, y, row[col]);
            x += columnWidths[col];
        }
    }
}

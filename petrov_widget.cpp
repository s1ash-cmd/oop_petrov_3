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
    setMinimumSize(0, 0);
    update();

}

void petrov_widget::paintEvent(QPaintEvent *event) {
    if (items.empty()) {
        return;
    }

    QPainter painter(this);
    int y = 40;
    QVector<int> columnWidths(8, 0);

    QFontMetrics metrics(painter.font());

    QStringList headers = {"Вес", "Ширина", "Высота", "Цена", "В наличии", "Возраст", "Состояние", "Описание"};

    // Установка ширины для заголовков
    std::for_each(headers.begin(), headers.end(),
                  [&metrics, &columnWidths, index = 0](const QString &header) mutable {
                      columnWidths[index++] = metrics.horizontalAdvance(header);
                  });

    // Подсчёт ширины колонок для элементов
    std::for_each(items.begin(), items.end(),
                  std::bind([&metrics, &columnWidths](const std::shared_ptr<item>& itemPtr) {
                      auto usedItemPtr = std::dynamic_pointer_cast<used_item>(itemPtr);
                      if (!usedItemPtr) return;

                      columnWidths[0] = std::max(columnWidths[0], metrics.horizontalAdvance(QString::number(usedItemPtr->weight)));
                      columnWidths[1] = std::max(columnWidths[1], metrics.horizontalAdvance(QString::number(usedItemPtr->width)));
                      columnWidths[2] = std::max(columnWidths[2], metrics.horizontalAdvance(QString::number(usedItemPtr->height)));
                      columnWidths[3] = std::max(columnWidths[3], metrics.horizontalAdvance(QString::number(usedItemPtr->price)));
                      columnWidths[4] = std::max(columnWidths[4], metrics.horizontalAdvance(usedItemPtr->stock ? "Да" : "Нет"));
                      columnWidths[5] = std::max(columnWidths[5], metrics.horizontalAdvance(QString::number(usedItemPtr->age)));
                      columnWidths[6] = std::max(columnWidths[6], metrics.horizontalAdvance(QString::number(usedItemPtr->condition)));
                      columnWidths[7] = std::max(columnWidths[7], metrics.horizontalAdvance(QString::fromStdString(usedItemPtr->description)));
                  }, std::placeholders::_1));

    // Увеличиваем пространство для столбца "Описание"
    columnWidths[7] += 100;  // Дополнительные отступы для "Описание", если оно слишком длинное

    // Рисование заголовков
    int x = 10;
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    std::for_each(headers.begin(), headers.end(), [&painter, &x, y, &columnWidths, index = 0](const QString &header) mutable {
        painter.drawText(x, y, header);
        x += columnWidths[index++] + 20;  // Отступы между колонками
    });

    y += 30;

    // Рисование значений элементов
    painter.setFont(QFont("Arial", 10, QFont::Normal));

    std::for_each(items.begin(), items.end(),
                  std::bind([&painter, &y, &columnWidths](const std::shared_ptr<item>& itemPtr) {
                      auto usedItemPtr = std::dynamic_pointer_cast<used_item>(itemPtr);
                      if (!usedItemPtr) return;

                      int x = 10;  // Сброс x для каждой новой строки
                      painter.drawText(x, y, QString::number(usedItemPtr->weight));
                      x += columnWidths[0] + 20;

                      painter.drawText(x, y, QString::number(usedItemPtr->width));
                      x += columnWidths[1] + 20;

                      painter.drawText(x, y, QString::number(usedItemPtr->height));
                      x += columnWidths[2] + 20;

                      painter.drawText(x, y, QString::number(usedItemPtr->price));
                      x += columnWidths[3] + 20;

                      painter.drawText(x, y, usedItemPtr->stock ? "Да" : "Нет");
                      x += columnWidths[4] + 20;

                      painter.drawText(x, y, QString::number(usedItemPtr->age));
                      x += columnWidths[5] + 20;

                      painter.drawText(x, y, QString::number(usedItemPtr->condition));
                      x += columnWidths[6] + 20;

                      painter.drawText(x, y, QString::fromStdString(usedItemPtr->description));
                      y += 30;
                  }, std::placeholders::_1));

    // Рассчитываем общую ширину с учетом отступов и ширины столбцов
    int totalWidth = 0;
    for (int width : columnWidths) {
        totalWidth += width + 20;  // Отступы между колонками
    }
    totalWidth += 30;  // Дополнительный отступ по бокам

    int totalHeight = y + 30;

    // Устанавливаем минимальный размер
    setMinimumSize(totalWidth, totalHeight);

    // Устанавливаем геометрию виджета
    setGeometry(geometry().x(), geometry().y(), totalWidth, totalHeight);
}

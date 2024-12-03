#include "petrov_dialog.h"
#include "ui_petrov_dialog.h"

#include <QDebug>

petrov_dialog::petrov_dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::petrov_dialog) {
    ui->setupUi(this);
    ui->checkBox_stock->setGeometry(590, 211, 30, 30);
    ui->checkBox_stock->setStyleSheet("QCheckBox::indicator { width: 30px; height: 30px; }");
}

petrov_dialog::~petrov_dialog() {
    delete ui;
}

void petrov_dialog::updateListWidget(const vector<shared_ptr<item>>& items) {
    ui->listWidget->clear(); // Очистка списка перед обновлением

    for (const auto& item : items) {
        QString itemText = QString::fromStdString(item->name) +
                           "\nВес: " + QString::number(item->weight) +
                           "\nШирина: " + QString::number(item->width) +
                           "\nВысота: " + QString::number(item->height) +
                           "\nЦена: " + QString::number(item->price) +
                           "\nВ наличии: " + (item->stock ? "Да" : "Нет");

        if (auto usedItem = dynamic_pointer_cast<used_item>(item)) {
            itemText += "\nВозраст: " + QString::number(usedItem->age) +
                        "\nСостояние: " + QString::number(usedItem->condition) +
                        "\nОписание: " + QString::fromStdString(usedItem->description);
        }

        ui->listWidget->addItem(new QListWidgetItem(itemText));
    }
}

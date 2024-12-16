#include "petrov_dialog.h"
#include "ui_petrov_dialog.h"
#include "petrov_widget.h"

#include <QDebug>
#include <QCloseEvent>

petrov_dialog::petrov_dialog(vector<shared_ptr<item>>& itemsRef, QWidget *parent)
    : QDialog(parent), ui(new Ui::petrov_dialog), items(itemsRef), changeditems(itemsRef) {
    ui->setupUi(this);

    ui->checkBox_stock->setGeometry(590, 211, 30, 30);
    ui->checkBox_stock->setStyleSheet("QCheckBox::indicator { width: 30px; height: 30px; }");

    connect(ui->listWidget, &QListWidget::itemClicked, this, &petrov_dialog::onItemClicked);
    connect(ui->pushButton_delete, &QPushButton::clicked, this, &petrov_dialog::on_pushButton_delete_clicked);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, &petrov_dialog::on_pushButton_exit_clicked);
    connect(ui->pushButton_change, &QPushButton::clicked, this, &petrov_dialog::on_pushButton_change_clicked);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &petrov_dialog::on_pushButton_add_clicked);

    changeditems = items;
}

petrov_dialog::~petrov_dialog() {
    delete ui;
}

void petrov_dialog::closeEvent(QCloseEvent *event) {
    items = changeditems;
    emit dataChanged(items);
    event->accept();
}

void petrov_dialog::on_pushButton_exit_clicked() {
    close();
}

void petrov_dialog::updateListWidget() {
    ui->listWidget->clear();
    for (const auto& item : changeditems) {
        QString itemText = QString::fromStdString(item->name);
        ui->listWidget->addItem(new QListWidgetItem(itemText));
    }

    if (!changeditems.empty()) {
        int selectedRow = changeditems.size() - 1;
        ui->listWidget->setCurrentRow(selectedRow);
        emit ui->listWidget->itemClicked(ui->listWidget->item(selectedRow));
    }

    toViewMode();
}

void petrov_dialog::onItemClicked(QListWidgetItem *selectedItem) {
    if (!selectedItem) return;

    int selectedRow = ui->listWidget->row(selectedItem);
    if (selectedRow < 0 || selectedRow >= changeditems.size()) return;

    auto selectedObject = changeditems[selectedRow];

    ui->textEdit_name->setText(QString::fromStdString(selectedObject->name));
    ui->textEdit_weight->setText(QString::number(selectedObject->weight));
    ui->textEdit_height->setText(QString::number(selectedObject->height));
    ui->textEdit_width->setText(QString::number(selectedObject->width));
    ui->textEdit_price->setText(QString::number(selectedObject->price));
    ui->checkBox_stock->setChecked(selectedObject->stock);

    auto usedItem = dynamic_pointer_cast<used_item>(selectedObject);
    if (usedItem) {
        ui->textEdit_age->setText(QString::number(usedItem->age));
        ui->doubleSpinBox_condition->setValue(usedItem->condition);
        ui->textEdit_description->setText(QString::fromStdString(usedItem->description));

        ui->doubleSpinBox_condition->show();
        ui->textEdit_age->show();
        ui->textEdit_description->show();
        ui->label_7->show();
        ui->label_8->show();
        ui->label_9->show();
    } else {
        ui->doubleSpinBox_condition->hide();
        ui->textEdit_age->hide();
        ui->textEdit_description->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->label_9->hide();
    }
    setFieldsDisabled(true);
}


void petrov_dialog::setFieldsDisabled(bool disabledState) {
    ui->textEdit_name->setReadOnly(disabledState);
    ui->textEdit_weight->setReadOnly(disabledState);
    ui->textEdit_height->setReadOnly(disabledState);
    ui->textEdit_width->setReadOnly(disabledState);
    ui->textEdit_price->setReadOnly(disabledState);
    ui->textEdit_description->setReadOnly(disabledState);
    ui->textEdit_age->setReadOnly(disabledState);
    ui->checkBox_stock->setDisabled(disabledState);
    ui->doubleSpinBox_condition->setReadOnly(disabledState);
}

void petrov_dialog::toViewMode() {
    setFieldsDisabled(true);
    ui->listWidget->setDisabled(false);
    ui->pushButton_save->setVisible(false);
    ui->pushButton_cancel->setVisible(false);

    ui->pushButton_change->setDisabled(false);
    ui->pushButton_add->setDisabled(false);
    ui->pushButton_delete->setDisabled(false);
}

void petrov_dialog::toAddMode() {
    clearFields();
    setFieldsDisabled(false);
    ui->listWidget->setDisabled(true);
    ui->pushButton_save->setVisible(true);
    ui->pushButton_cancel->setVisible(true);

    ui->pushButton_change->setDisabled(true);
    ui->pushButton_add->setDisabled(true);
    ui->pushButton_delete->setDisabled(true);
}

void petrov_dialog::toChangeMode() {
    setFieldsDisabled(false);
    ui->listWidget->setDisabled(true);
    ui->pushButton_save->setVisible(true);
    ui->pushButton_cancel->setVisible(true);

    ui->pushButton_change->setDisabled(true);
    ui->pushButton_add->setDisabled(true);
    ui->pushButton_delete->setDisabled(true);
}

void petrov_dialog::clearFields() {
    ui->textEdit_name->clear();
    ui->textEdit_weight->clear();
    ui->textEdit_height->clear();
    ui->textEdit_width->clear();
    ui->textEdit_price->clear();
    ui->textEdit_age->clear();
    ui->textEdit_description->clear();
    ui->doubleSpinBox_condition->setValue(0.0);
    ui->checkBox_stock->setCheckState(Qt::CheckState(false));
}

bool petrov_dialog::validateItemInputs(shared_ptr<item> selectedItem) {
    bool isValid = true;

    if (ui->textEdit_name->toPlainText().isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Имя товара не может быть пустым.");
        isValid = false;
    }

    bool weightOk;
    double weight = ui->textEdit_weight->toPlainText().toDouble(&weightOk);
    if (!weightOk || weight <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Вес должен быть числом больше нуля.");
        isValid = false;
    }

    bool heightOk;
    double height = ui->textEdit_height->toPlainText().toDouble(&heightOk);
    if (!heightOk || height <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Высота должна быть числом больше нуля.");
        isValid = false;
    }

    bool widthOk;
    double width = ui->textEdit_width->toPlainText().toDouble(&widthOk);
    if (!widthOk || width <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Ширина должна быть числом больше нуля.");
        isValid = false;
    }

    bool priceOk;
    double price = ui->textEdit_price->toPlainText().toDouble(&priceOk);
    if (!priceOk || price <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Цена должна быть числом больше нуля.");
        isValid = false;
    }

    if (auto usedItem = dynamic_pointer_cast<used_item>(selectedItem)) {
        bool ageOk;
        int age = ui->textEdit_age->toPlainText().toInt(&ageOk);
        if (!ageOk || age < 0) {
            QMessageBox::warning(nullptr, "Ошибка", "Возраст должен быть числом больше или равным нулю.");
            isValid = false;
        }

        if (ui->doubleSpinBox_condition->value() < 0 || ui->doubleSpinBox_condition->value() > 10) {
            QMessageBox::warning(nullptr, "Ошибка", "Состояние должно быть в диапазоне от 0 до 10.");
            isValid = false;
        }

        if (ui->textEdit_description->toPlainText().isEmpty()) {
            QMessageBox::warning(nullptr, "Ошибка", "Описание не может быть пустым.");
            isValid = false;
        }
    }

    return isValid;
}

void petrov_dialog::on_pushButton_delete_clicked() {
    int currentRow = ui->listWidget->currentRow();

    if (currentRow < 0) {
        QMessageBox::information(this, "Нет товаров", "У вас нет товаров для удаления");
        return;
    }

    QMessageBox msgBox;
    msgBox.setText("Вы уверены?");
    msgBox.addButton("Нет", QMessageBox::NoRole);
    msgBox.addButton("Да", QMessageBox::YesRole);
    auto reply = msgBox.exec();

    if (reply == 1) {
        if (currentRow >= 0 && currentRow < static_cast<int>(changeditems.size())) {
            changeditems.erase(changeditems.begin() + currentRow);
        }

        delete ui->listWidget->takeItem(currentRow);
        clearFields();

        if (changeditems.empty()) {
            toViewMode();
        }
        else{
            int newRow = (currentRow == changeditems.size()) ? currentRow - 1 : currentRow;
            ui->listWidget->setCurrentRow(newRow);
            emit ui->listWidget->itemClicked(ui->listWidget->item(newRow));
        }
    }
}

void petrov_dialog::on_pushButton_add_clicked() {
    QMessageBox msgBox;
    msgBox.setText("Какой товар добавить?");
    QPushButton* usedButton = msgBox.addButton("Б/У", QMessageBox::NoRole);
    QPushButton* newButton = msgBox.addButton("Новый", QMessageBox::YesRole);
    msgBox.exec();

    shared_ptr<item> newItem;

    clearFields();
    ui->doubleSpinBox_condition->hide();
    ui->textEdit_age->hide();
    ui->textEdit_description->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();

    if (msgBox.clickedButton() == newButton) {
        newItem = make_shared<item>();
    } else if (msgBox.clickedButton() == usedButton) {
        ui->doubleSpinBox_condition->show();
        ui->textEdit_age->show();
        ui->textEdit_description->show();
        ui->label_7->show();
        ui->label_8->show();
        ui->label_9->show();

        newItem = make_shared<used_item>();
    } else {
        return;
    }

    toAddMode();

    disconnect(ui->pushButton_save, &QPushButton::clicked, this, nullptr);
    disconnect(ui->pushButton_cancel, &QPushButton::clicked, this, nullptr);

    auto saveNewItem = [this, newItem]() {
        if (!validateItemInputs(newItem)) {
            return;
        }

        newItem->name = ui->textEdit_name->toPlainText().toStdString();
        newItem->weight = ui->textEdit_weight->toPlainText().toDouble();
        newItem->height = ui->textEdit_height->toPlainText().toDouble();
        newItem->width = ui->textEdit_width->toPlainText().toDouble();
        newItem->price = ui->textEdit_price->toPlainText().toDouble();
        newItem->stock = ui->checkBox_stock->isChecked();

        if (auto usedItem = dynamic_pointer_cast<used_item>(newItem)) {
            usedItem->age = ui->textEdit_age->toPlainText().toInt();
            usedItem->condition = ui->doubleSpinBox_condition->value();
            usedItem->description = ui->textEdit_description->toPlainText().toStdString();
        }

        updateListWidget();
        toViewMode();
    };

    changeditems.push_back(newItem);

    auto cancelNewItem = [this]() {
        clearFields();
        updateListWidget();
        toViewMode();
    };

    int lastRow = changeditems.size() - 1;
    ui->listWidget->setCurrentRow(lastRow);
    emit ui->listWidget->itemClicked(ui->listWidget->item(lastRow));

    connect(ui->pushButton_save, &QPushButton::clicked, this, saveNewItem);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, cancelNewItem);
}


void petrov_dialog::on_pushButton_change_clicked() {
    int currentRow = ui->listWidget->currentRow();

    if (currentRow < 0 || currentRow >= changeditems.size()) {
        QMessageBox::information(this, "Ошибка", "У вас нет товаров для редактирования.");
        return;
    }

    auto selectedItem = changeditems[currentRow];

    ui->textEdit_name->setText(QString::fromStdString(selectedItem->name));
    ui->textEdit_weight->setText(QString::number(selectedItem->weight));
    ui->textEdit_height->setText(QString::number(selectedItem->height));
    ui->textEdit_width->setText(QString::number(selectedItem->width));
    ui->textEdit_price->setText(QString::number(selectedItem->price));
    ui->checkBox_stock->setChecked(selectedItem->stock);

    if (auto usedItem = dynamic_pointer_cast<used_item>(selectedItem)) {
        ui->textEdit_age->setText(QString::number(usedItem->age));
        ui->doubleSpinBox_condition->setValue(usedItem->condition);
        ui->textEdit_description->setText(QString::fromStdString(usedItem->description));

        ui->doubleSpinBox_condition->show();
        ui->textEdit_age->show();
        ui->textEdit_description->show();
        ui->label_7->show();
        ui->label_8->show();
        ui->label_9->show();
    } else {
        ui->doubleSpinBox_condition->hide();
        ui->textEdit_age->hide();
        ui->textEdit_description->hide();
        ui->label_7->hide();
        ui->label_8->hide();
        ui->label_9->hide();
    }

    toChangeMode();

    disconnect(ui->pushButton_save, &QPushButton::clicked, this, nullptr);
    disconnect(ui->pushButton_cancel, &QPushButton::clicked, this, nullptr);

    auto saveChanges = [this, selectedItem, currentRow]() {
        if (!validateItemInputs(selectedItem)) {
            return;
        }

        selectedItem->name = ui->textEdit_name->toPlainText().toStdString();
        selectedItem->weight = ui->textEdit_weight->toPlainText().toDouble();
        selectedItem->height = ui->textEdit_height->toPlainText().toDouble();
        selectedItem->width = ui->textEdit_width->toPlainText().toDouble();
        selectedItem->price = ui->textEdit_price->toPlainText().toDouble();
        selectedItem->stock = ui->checkBox_stock->isChecked();

        if (auto usedItem = dynamic_pointer_cast<used_item>(selectedItem)) {
            usedItem->age = ui->textEdit_age->toPlainText().toInt();
            usedItem->condition = ui->doubleSpinBox_condition->value();
            usedItem->description = ui->textEdit_description->toPlainText().toStdString();
        }

        updateListWidget();
        ui->listWidget->setCurrentRow(currentRow);
        toViewMode();
    };

    auto cancelChanges = [this]() {
        clearFields();
        updateListWidget();
        toViewMode();
    };

    connect(ui->pushButton_save, &QPushButton::clicked, this, saveChanges);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, cancelChanges);
}

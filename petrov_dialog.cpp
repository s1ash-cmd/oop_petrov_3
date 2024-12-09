#include "petrov_dialog.h"
#include "ui_petrov_dialog.h"
#include "petrov_widget.h"

#include <QDebug>
#include <QCloseEvent>

petrov_dialog::petrov_dialog(vector<shared_ptr<item>>& itemsRef, QWidget *parent)
    : QDialog(parent), ui(new Ui::petrov_dialog), items(itemsRef), changeditems(itemsRef) {
    ui->setupUi(this);

    if (changeditems.empty()) {
        changeditems.push_back(make_shared<item>());
    }

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
    toViewMode();
}

void petrov_dialog::onItemClicked(QListWidgetItem *selectedItem) {
    if (!selectedItem) return;

    QString selectedName = selectedItem->text();
    auto it = find_if(items.begin(), items.end(), [&](const shared_ptr<item> &itm) {
        return QString::fromStdString(itm->name) == selectedName;
    });

    shared_ptr<item> selectedObject = *it;

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
    ui->listWidget->setDisabled(false);
    ui->pushButton_save->setVisible(true);
    ui->pushButton_cancel->setVisible(true);

    ui->pushButton_change->setDisabled(true);
    ui->pushButton_add->setDisabled(true);
    ui->pushButton_delete->setDisabled(true);
}

void petrov_dialog::clearFields() {
    ui->textEdit_name->clear();
    ui->textEdit_weight->clear();
    ui->textEdit_width->clear();
    ui->textEdit_price->clear();
    ui->textEdit_description->clear();
    ui->doubleSpinBox_condition->setValue(0.0);
    ui->checkBox_stock->setCheckState(Qt::CheckState(false));
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
    }
}

void petrov_dialog::on_pushButton_change_clicked() {
    int currentRow = ui->listWidget->currentRow();

    if (currentRow < 0) {
        QMessageBox::information(this, "Нет товаров", "У вас нет товаров для редактирования");
        return;
    }

    auto& selectedObject = changeditems[currentRow];
    auto originalObject = make_shared<item>(*selectedObject);
    auto originalUsedObject = dynamic_pointer_cast<used_item>(selectedObject) ? make_shared<used_item>(*dynamic_pointer_cast<used_item>(selectedObject)) : nullptr;

    toChangeMode();

    auto validateInputs = [this, &selectedObject]() -> bool {
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

        if (auto usedItem = dynamic_pointer_cast<used_item>(selectedObject)) {
            bool ageOk;
            int age = ui->textEdit_age->toPlainText().toInt(&ageOk);
            if (!ageOk || age < 0) {
                QMessageBox::warning(nullptr, "Ошибка", "Возраст должен быть числом больше или равным нулю.");
                isValid = false;
            }

            if (ui->doubleSpinBox_condition->value() < 0 || ui->doubleSpinBox_condition->value() > 10) {
                QMessageBox::warning(nullptr, "Ошибка", "Состояние должно быть в диапазоне от 0 до 100.");
                isValid = false;
            }

            if (ui->textEdit_description->toPlainText().isEmpty()) {
                QMessageBox::warning(nullptr, "Ошибка", "Описание не может быть пустым.");
                isValid = false;
            }
        }

        return isValid;
    };

    auto saveChanges = [this, currentRow, validateInputs]() {
        if (!validateInputs()) {
            return;
        }

        auto& selectedObject = changeditems[currentRow];
        selectedObject->name = ui->textEdit_name->toPlainText().toStdString();
        selectedObject->weight = ui->textEdit_weight->toPlainText().toDouble();
        selectedObject->height = ui->textEdit_height->toPlainText().toDouble();
        selectedObject->width = ui->textEdit_width->toPlainText().toDouble();
        selectedObject->price = ui->textEdit_price->toPlainText().toDouble();
        selectedObject->stock = ui->checkBox_stock->isChecked();

        if (auto usedItem = dynamic_pointer_cast<used_item>(selectedObject)) {
            usedItem->age = ui->textEdit_age->toPlainText().toInt();
            usedItem->condition = ui->doubleSpinBox_condition->value();
            usedItem->description = ui->textEdit_description->toPlainText().toStdString();
        }

        updateListWidget();
        toViewMode();
    };

    auto cancelChanges = [this, currentRow, originalObject, originalUsedObject]() {
        if (originalUsedObject) {
            *dynamic_pointer_cast<used_item>(changeditems[currentRow]) = *originalUsedObject;
        } else {
            *changeditems[currentRow] = *originalObject;
        }

        updateListWidget();
        toViewMode();
    };

    connect(ui->pushButton_save, &QPushButton::clicked, this, saveChanges);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, cancelChanges);
}


void petrov_dialog::on_pushButton_add_clicked() {
    QMessageBox msgBox;
    msgBox.setText("Какой товар добавить?");
    QPushButton* usedButton = msgBox.addButton("Б/У", QMessageBox::NoRole);
    QPushButton* newButton = msgBox.addButton("Новый", QMessageBox::YesRole);
    msgBox.exec();

    bool isUsedItem = msgBox.clickedButton() == usedButton;

    shared_ptr<item> newItem;

    if (isUsedItem) {
        auto usedItem = make_shared<used_item>();
        usedItem->age = 0;
        usedItem->condition = 10.0;
        usedItem->description = "Описание отсутствует";
        newItem = usedItem;
    } else {
        newItem = make_shared<item>();
    }

    newItem->name = "Новый товар";
    newItem->weight = 0.0;
    newItem->height = 0.0;
    newItem->width = 0.0;
    newItem->price = 0.0;
    newItem->stock = false;

    changeditems.push_back(newItem);

    updateListWidget();
    toAddMode();


    ui->textEdit_name->setText(QString::fromStdString(newItem->name));
    ui->textEdit_weight->setText(QString::number(newItem->weight));
    ui->textEdit_height->setText(QString::number(newItem->height));
    ui->textEdit_width->setText(QString::number(newItem->width));
    ui->textEdit_price->setText(QString::number(newItem->price));
    ui->checkBox_stock->setChecked(newItem->stock);

    if (isUsedItem) {
        auto usedItem = dynamic_pointer_cast<used_item>(newItem);
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


    connect(ui->pushButton_save, &QPushButton::clicked, this, [this, newItem]() {
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
    });


    connect(ui->pushButton_cancel, &QPushButton::clicked, this, [this, newItem]() {
        changeditems.pop_back();
        updateListWidget();
        toViewMode();
    });
}


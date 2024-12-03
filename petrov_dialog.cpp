#include "petrov_dialog.h"
#include "ui_petrov_dialog.h"

#include <QDebug>

petrov_dialog::petrov_dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::petrov_dialog) {
    ui->setupUi(this);
    ui->checkBox_stock->setGeometry(590, 211, 30, 30);
    ui->checkBox_stock->setStyleSheet("QCheckBox::indicator { width: 30px; height: 30px; }");

    connect(ui->listWidget, &QListWidget::itemClicked, this, &petrov_dialog::onItemClicked);
}

petrov_dialog::~petrov_dialog() {
    delete ui;
}

void petrov_dialog::updateListWidget(const vector<shared_ptr<item>>& items) {
    this->items = items;
    ui->listWidget->clear();

    for (const auto& item : items) {
        QString itemText = QString::fromStdString(item->name);
        ui->listWidget->addItem(new QListWidgetItem(itemText));
    }
}


// void petrov_dialog::onItemClicked(QListWidgetItem *selectedItem) {
//     if (!selectedItem) return;

//     QString selectedName = selectedItem->text();
//     auto it = std::find_if(items.begin(), items.end(), [&](const shared_ptr<item> &itm) {
//         return QString::fromStdString(itm->name) == selectedName;
//     });

//     shared_ptr<item> selectedObject = *it;

//     ui->textEdit_name->setText(QString::fromStdString(selectedObject->name));
//     ui->textEdit_weight->setText(QString::number(selectedObject->weight));
//     ui->textEdit_height->setText(QString::number(selectedObject->height));
//     ui->textEdit_width->setText(QString::number(selectedObject->width));
//     ui->textEdit_price->setText(QString::number(selectedObject->price));
//     ui->checkBox_stock->setChecked(selectedObject->stock);


//     auto usedItem = dynamic_pointer_cast<used_item>(selectedObject);
//     if (usedItem) {

//         ui->textEdit_age->setText(QString::number(usedItem->age));
//         ui->doubleSpinBox_condition->setValue(usedItem->condition);

//         ui->textEdit_description->setText(QString::fromStdString(usedItem->description));

//         ui->doubleSpinBox_condition->show();
//         ui->textEdit_age->show();
//         ui->textEdit_description->show();
//         ui->label_7->show();
//         ui->label_8->show();
//         ui->label_9->show();

//     } else {
//         ui->doubleSpinBox_condition->hide();
//         ui->textEdit_age->hide();
//         ui->textEdit_description->hide();
//         ui->label_7->hide();
//         ui->label_8->hide();
//         ui->label_9->hide();
//     }

//     ui->textEdit_name->setReadOnly(true);
//     ui->textEdit_weight->setReadOnly(true);
//     ui->textEdit_height->setReadOnly(true);
//     ui->textEdit_width->setReadOnly(true);
//     ui->textEdit_price->setReadOnly(true);
//     ui->textEdit_description->setReadOnly(true);
//     ui->textEdit_age->setReadOnly(true);


//     connect(ui->checkBox_stock, &QCheckBox::clicked, ui->checkBox_stock, [=](bool) {
//         ui->checkBox_stock->setChecked(!ui->checkBox_stock->isChecked());
//     });

//     ui->doubleSpinBox_condition->setReadOnly(true);


// }


void petrov_dialog::onItemClicked(QListWidgetItem *selectedItem) {
    if (!selectedItem) return;

    QString selectedName = selectedItem->text();
    auto it = std::find_if(items.begin(), items.end(), [&](const shared_ptr<item> &itm) {
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


}


void petrov_dialog::setFieldsDisabled(bool disabledState)
{
    ui->textEdit_name->setDisabled(disabledState);
    ui->textEdit_weight->setDisabled(disabledState);
    ui->textEdit_height->setDisabled(disabledState);
    ui->textEdit_width->setDisabled(disabledState);
    ui->textEdit_price->setDisabled(disabledState);
    ui->textEdit_description->setDisabled(disabledState);
    ui->textEdit_age->setDisabled(disabledState);
    ui->checkBox_stock->setDisabled(disabledState);
    ui->doubleSpinBox_condition->setDisabled(disabledState);
}

void petrov_dialog::toViewMode()
{
    setFieldsDisabled(true);
    ui->listWidget->setDisabled(false);
    ui->pushButton_save->setVisible(false);
    ui->pushButton_cancel->setVisible(false);
}

void petrov_dialog::toAddMode()
{
    clearFields();
    setFieldsDisabled(false);
    ui->listWidget->setDisabled(true);
    ui->pushButton_save->setVisible(true);
    ui->pushButton_cancel->setVisible(true);
}

void petrov_dialog::toChangeMode()
{
    setFieldsDisabled(false);
    ui->listWidget->setDisabled(false);
    ui->pushButton_save->setVisible(true);
    ui->pushButton_cancel->setVisible(true);
}

void petrov_dialog::clearFields()
{
    ui->textEdit_name->setPlainText("");
    ui->textEdit_weight->setPlainText("");
    ui->textEdit_width->setPlainText("");
    ui->textEdit_price->setPlainText("");
    ui->textEdit_description->setPlainText("");

    ui->doubleSpinBox_condition->setValue(0.0);

    ui->checkBox_stock->setCheckState(Qt::CheckState(false));


}

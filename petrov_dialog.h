#ifndef PETROV_DIALOG_H
#define PETROV_DIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <vector>
#include <memory>
#include "petrov_widget.h"
#include "petrov_item.h"
#include "petrov_used_item.h"

using namespace std;

namespace Ui {
class petrov_dialog;
}

class petrov_dialog : public QDialog {
    Q_OBJECT

public:
    explicit petrov_dialog(vector<shared_ptr<item>>& itemsRef, QWidget *parent = nullptr);

    ~petrov_dialog();

    void updateListWidget();

private slots:
    void onItemClicked(QListWidgetItem* item);
    void on_pushButton_exit_clicked();

signals:
    void dataChanged(vector<shared_ptr<item>>&);

private:
    Ui::petrov_dialog *ui;
    vector<shared_ptr<item>>& items;
    vector<shared_ptr<item>> changeditems;

    void setFieldsDisabled(bool disabledState);
    void closeEvent(QCloseEvent *event);
    void toViewMode();
    void toAddMode();
    void toChangeMode();
    void clearFields();
    bool validateItemInputs(shared_ptr<item> targetItem);
    void on_pushButton_delete_clicked();
    void on_pushButton_change_clicked();
    void on_pushButton_add_clicked();
};

#endif // PETROV_DIALOG_H

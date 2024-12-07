#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "petrov_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

bool shouldDisplayItems = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);

    connect(ui->load_from_file_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::loadFromFile);
    connect(ui->save_file_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::saveToFile);
    connect(ui->clear_items_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::clearItems);

    connect(ui->edit_items_qt, &QAction::triggered, this, &MainWindow::openEditDialog);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openEditDialog() {

    this->setEnabled(false);

    petrov_dialog d(ui->petrovwidgetInstance->getItems(), this);

    connect(&d, &petrov_dialog::dataChanged, ui->petrovwidgetInstance, &petrov_widget::update);

    d.updateListWidget();


    d.setWindowModality(Qt::ApplicationModal);
    d.exec();


    this->setEnabled(true);

    disconnect(&d, &petrov_dialog::dataChanged, ui->petrovwidgetInstance, &petrov_widget::update);
}

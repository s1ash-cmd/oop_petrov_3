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

    connect(ui->load_from_file_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::loadFromFile);
    connect(ui->save_file_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::saveToFile);
    connect(ui->clear_items_qt, &QAction::triggered, ui->petrovwidgetInstance, &petrov_widget::clearItems);
}

MainWindow::~MainWindow() {
    delete ui;
}

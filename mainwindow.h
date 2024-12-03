#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>
#include "petrov_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openEditDialog();

private:
    Ui::MainWindow *ui;
    petrov_dialog d;
};

#endif // MAINWINDOW_H

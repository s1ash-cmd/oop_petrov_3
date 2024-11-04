#ifndef PETROV_WIDGET_H
#define PETROV_WIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include <QPainter>
#include <QScrollArea>
#include <fstream>

#include "petrov_item.h"
#include "petrov_used_item.h"
#include "petrov_header.h"

using namespace std;

class petrov_widget : public QWidget {
    Q_OBJECT
    vector<shared_ptr<item>> items;

public:
    explicit petrov_widget(QWidget *parent = nullptr);
    void loadFromFile();
    void saveToFile();
    void clearItems();

protected:
    void paintEvent(QPaintEvent *event) override;

};
#endif // PETROV_WIDGET_H

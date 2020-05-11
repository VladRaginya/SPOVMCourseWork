#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <baselogic.h>
#include <qtreewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    BaseLogic* logic;
};

#endif // MAINWINDOW_H

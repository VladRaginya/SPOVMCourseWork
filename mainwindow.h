#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controller.h>
#include <qtreewidget.h>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <editstringdialog.h>
#include <editdworddialog.h>
#include <qtablewidget.h>
#include <QAction>
#include <QContextMenuEvent>
#include <addkeydialog.h>
#include <addvaluedialog.h>
#include <editdworddialog.h>
#include <editstringdialog.h>
#include <editqworddialog.h>
#include <editbinarydialog.h>
#include <sstream>
#include <baseexception.h>
#include <QMessageBox>

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

    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_actionDeleteKey_triggered();

    void on_actionDeleteValue_triggered();

    void on_actionAddKey_triggered();

    void on_actionAddValue_triggered();

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Controller* controller;
};

#endif // MAINWINDOW_H

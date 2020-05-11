#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    logic = new BaseLogic();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{

}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
   //logic->getValueByKey(item->text());
}

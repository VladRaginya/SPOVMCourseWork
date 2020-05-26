#ifndef EDITBINARYDIALOG_H
#define EDITBINARYDIALOG_H

#include <QDialog>
#include <controller.h>
#include <QTableWidget>
#include <QTreeWidget>
#include <QRegExpValidator>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class EditBinaryDialog;
}

class EditBinaryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditBinaryDialog(QWidget *parent = 0, Controller* controller = NULL, QTableWidgetItem* item1 = NULL, QTableWidgetItem *item2 = NULL, QTreeWidgetItem* itemTree = NULL);
    ~EditBinaryDialog();
    
private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditBinaryDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _itemTree;
    QTableWidgetItem* _item1;
    QTableWidgetItem* _item2;
};

#endif // EDITBINARYDIALOG_H

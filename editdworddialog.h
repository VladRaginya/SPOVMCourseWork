#ifndef EDITDWORDDIALOG_H
#define EDITDWORDDIALOG_H

#include <QDialog>
#include <controller.h>
#include <QTableWidget>
#include <QTreeWidget>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class EditDwordDialog;
}

class EditDwordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditDwordDialog(QWidget *parent = 0, Controller* controller = NULL, QTableWidgetItem* item1 = NULL, QTableWidgetItem *item2 = NULL, QTreeWidgetItem* itemTree = NULL);
    ~EditDwordDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditDwordDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _itemTree;
    QTableWidgetItem* _item1;
    QTableWidgetItem* _item2;
};

#endif // EDITDWORDDIALOG_H

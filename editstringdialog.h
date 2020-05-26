#ifndef EDITSTRINGDIALOG_H
#define EDITSTRINGDIALOG_H

#include <QDialog>
#include <controller.h>
#include <QTableWidget>
#include <QTreeWidget>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class EditStringDialog;
}

class EditStringDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditStringDialog(QWidget *parent = 0, Controller* controller = NULL, QTableWidgetItem* item1 = NULL, QTableWidgetItem* item2 = NULL, QTreeWidgetItem* itemTree = NULL);
    ~EditStringDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditStringDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _itemTree;
    QTableWidgetItem* _item1;
    QTableWidgetItem* _item2;
};

#endif // EDITSTRINGDIALOG_H

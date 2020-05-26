#ifndef EDITQWORDDIALOG_H
#define EDITQWORDDIALOG_H

#include <QDialog>
#include <controller.h>
#include <QTableWidget>
#include <QTreeWidget>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class EditQwordDialog;
}

class EditQwordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit EditQwordDialog(QWidget *parent = 0, Controller *controller = NULL, QTableWidgetItem *item1 = NULL, QTableWidgetItem *item2 = NULL, QTreeWidgetItem *itemTree = NULL);
    ~EditQwordDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditQwordDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _itemTree;
    QTableWidgetItem* _item1;
    QTableWidgetItem* _item2;
};

#endif // EDITQWORDDIALOG_H

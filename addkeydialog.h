#ifndef ADDKEYDIALOG_H
#define ADDKEYDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <controller.h>
#include <nameexception.h>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class AddKeyDialog;
}

class AddKeyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddKeyDialog(QWidget *parent = 0, Controller* controller = NULL, QTreeWidgetItem* item = NULL);
    ~AddKeyDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddKeyDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _item;
};

#endif // ADDKEYDIALOG_H

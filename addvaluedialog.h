#ifndef ADDVALUEDIALOG_H
#define ADDVALUEDIALOG_H

#include <QDialog>
#include <QTreeWidget>
#include <QTableWidget>
#include <controller.h>
#include <string>
#include <QString>
#include <nameexception.h>
#include <typeexception.h>
#include <baseexception.h>
#include <QMessageBox>

namespace Ui {
class AddValueDialog;
}

class AddValueDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddValueDialog(QWidget *parent = 0, Controller* controller = NULL, QTreeWidgetItem* item = NULL, QTableWidget* table = NULL);
    ~AddValueDialog();
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddValueDialog *ui;
    Controller* _controller;
    QTreeWidgetItem* _item;
    string getButton();
    QTableWidget* _table;
};

#endif // ADDVALUEDIALOG_H

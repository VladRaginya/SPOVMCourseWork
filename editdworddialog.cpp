#include "editdworddialog.h"
#include "ui_editdworddialog.h"

EditDwordDialog::EditDwordDialog(QWidget *parent, Controller* controller, QTableWidgetItem* item1, QTableWidgetItem *item2, QTreeWidgetItem *itemTree) :
    QDialog(parent),
    _controller(controller),
    _itemTree(itemTree),
    _item1(item1),
    _item2(item2),
    ui(new Ui::EditDwordDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(item1->text());
    ui->lineEdit->setEnabled(false);
    ui->spinBox->setMaximum(2147483647);
    ui->spinBox->setValue(item2->text().toInt());
}

EditDwordDialog::~EditDwordDialog()
{
    delete ui;
}

void EditDwordDialog::on_buttonBox_accepted()
{
    QString baseKey, subkey;
    if(_itemTree->text(0) == "Computer") return;
    QTreeWidgetItem* parent = _itemTree->parent();
    if(parent->text(0) == "Computer")
    {
        baseKey = _itemTree->text(0);
        subkey = "";
    }
    else
    {
        subkey = _itemTree->text(0);
        while(parent->parent()->text(0) != "Computer")
        {
            subkey = parent->text(0) + "\\" + subkey;
            parent = parent->parent();
        }
        baseKey = parent->text(0);

    }
    string valueName = ui->lineEdit->text().toStdString();
    string valueType = "REG_DWORD";
    string valueData = ui->spinBox->text().toStdString();
    try
    {
       if(!_controller->setNewValueData(baseKey.toStdString(), subkey.toStdString(), valueName, valueType, valueData))
       {
           throw new BaseException();
       }
    }
    catch(BaseException* e)
    {
        QMessageBox::critical(this, "Error", "Internal error");
        return;
    }

    _item2->setText(ui->spinBox->text());
}

#include "editstringdialog.h"
#include "ui_editstringdialog.h"

EditStringDialog::EditStringDialog(QWidget *parent, Controller* controller, QTableWidgetItem* item1, QTableWidgetItem *item2, QTreeWidgetItem* itemTree) :
    QDialog(parent),
    _controller(controller),
    _itemTree(itemTree),
    _item1(item1),
    _item2(item2),
    ui(new Ui::EditStringDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(item1->text());
     ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setText(item2->text());
}

EditStringDialog::~EditStringDialog()
{
    delete ui;
}

void EditStringDialog::on_buttonBox_accepted()
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
    string valueType = "REG_SZ";
    string valueData = ui->lineEdit_2->text().toStdString();
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
    _item2->setText(ui->lineEdit_2->text());

}

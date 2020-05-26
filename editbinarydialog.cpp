#include "editbinarydialog.h"
#include "ui_editbinarydialog.h"

EditBinaryDialog::EditBinaryDialog(QWidget *parent, Controller *controller, QTableWidgetItem *item1, QTableWidgetItem *item2, QTreeWidgetItem *itemTree) :
    QDialog(parent),
    _controller(controller),
    _itemTree(itemTree),
    _item1(item1),
    _item2(item2),
    ui(new Ui::EditBinaryDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(item1->text());
    if(item2->text() != "(Value not set)")
    ui->lineEdit_2->setText(item2->text());
    QRegExp regex("[a-fA-F0-9]*");
    QRegExpValidator *v = new QRegExpValidator(regex, this->parent()->parent()); // or QRegularExpressionValidator
    ui->lineEdit_2->setValidator(v);
}

EditBinaryDialog::~EditBinaryDialog()
{
    delete ui;
}



void EditBinaryDialog::on_buttonBox_accepted()
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
    string valueType = "REG_BINARY";
    string valueData = ui->lineEdit_2->text().toStdString();
    if(valueData.size() % 2 == 1)
    {
        valueData = "0" + valueData;
    }
    int bufSize = valueData.size() / 2;
    char buf[bufSize+1];
    char byte[2];
    for(int i = 0, j = 0; i < valueData.size() / 2; i++, j+=2)
    {
        byte[0] = valueData[j];
        byte[1] = valueData[j+1];
        buf[i] = strtol(byte, NULL, 16);
        qDebug() << buf[i];
    }
    buf[bufSize] = '\0';
    valueData = buf;
    qDebug() << QString::fromStdString(valueData);
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
    this->close();
}

void EditBinaryDialog::on_buttonBox_rejected()
{
    this->close();
}

#include "addvaluedialog.h"
#include "ui_addvaluedialog.h"

AddValueDialog::AddValueDialog(QWidget *parent, Controller* controller, QTreeWidgetItem* item, QTableWidget* table) :
    QDialog(parent),
    _controller(controller),
    _item(item),
    _table(table),
    ui(new Ui::AddValueDialog)
{
    ui->setupUi(this);
}

AddValueDialog::~AddValueDialog()
{
    delete ui;
}

void AddValueDialog::on_buttonBox_accepted()
{
    try
    {
        if(ui->lineEdit->text() == "") throw new NameException();
        QString baseKey, subkey;
        if(_item->text(0) == "Computer") return;
        QTreeWidgetItem* parent = _item->parent();
        if(parent->text(0) == "Computer")
        {
            baseKey = _item->text(0);
            subkey = "";
        }
        else
        {
            subkey = _item->text(0);
            while(parent->parent()->text(0) != "Computer")
            {
                subkey = parent->text(0) + "\\" + subkey;
                parent = parent->parent();
            }
            baseKey = parent->text(0);

        }
        string newValueName = ui->lineEdit->text().toStdString();
        string valueType = getButton();
        if(valueType == "") throw new TypeException();
        qDebug() << QString::fromStdString(valueType);
        try
        {
            if(!_controller->addNewValue(baseKey.toStdString(), subkey.toStdString(), newValueName, valueType))
            {
                throw new BaseException();
            }
        }
        catch(BaseException * e)
        {
            QMessageBox::critical(this, "Error", "Internal error");
            return;
        }
        _table->insertRow(_table->rowCount());
        QTableWidgetItem* name = new QTableWidgetItem(0);
        name->setFlags(name->flags() & ~Qt::ItemIsEditable);
        if(newValueName == "")
        {
            name->setText("(Default)");
        }
        else
        {
            name->setText(QString::fromStdString(newValueName));
        }
        _table->setItem(_table->rowCount() - 1,0, name);
        QTableWidgetItem* type = new QTableWidgetItem(0);
        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        type->setText(QString::fromStdString(valueType));
        _table->setItem(_table->rowCount() - 1,1, type);
        QTableWidgetItem* value = new QTableWidgetItem(0);
        value->setFlags(value->flags() & ~Qt::ItemIsEditable);
        value->setText("(Value not set)");
        _table->setItem(_table->rowCount() - 1,2, value);
    }
    catch(NameException* e)
    {
        QMessageBox::critical(this, "Error", "Name field is empty! You must enter the name");
        return;
    }
    catch(TypeException* e)
    {
        QMessageBox::critical(this, "Error", "Value type is not chosen! You must choose the type");
        return;
    }

}

string AddValueDialog::getButton()
{
    if(ui->radioButton->isChecked()) return ui->radioButton->text().toStdString();
    if(ui->radioButton_2->isChecked()) return ui->radioButton_2->text().toStdString();
    if(ui->radioButton_3->isChecked()) return ui->radioButton_3->text().toStdString();
    if(ui->radioButton_4->isChecked()) return ui->radioButton_4->text().toStdString();
    return "";
}





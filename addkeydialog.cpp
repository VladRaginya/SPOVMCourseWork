#include "addkeydialog.h"
#include "ui_addkeydialog.h"

AddKeyDialog::AddKeyDialog(QWidget *parent, Controller* controller, QTreeWidgetItem* item) :
    QDialog(parent),
    _controller(controller),
    _item(item),
    ui(new Ui::AddKeyDialog)
{
    ui->setupUi(this);
}

AddKeyDialog::~AddKeyDialog()
{
    delete ui;
}

void AddKeyDialog::on_buttonBox_accepted()
{
    try{
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
        try
        {
            if(!_controller->addNewKey(baseKey.toStdString(), subkey.toStdString(), ui->lineEdit->text().toStdString()))
            {
                throw new BaseException();
            }
        }
        catch(BaseException* e)
        {
            QMessageBox::critical(this, "Error", "Internal error");
            return;
        }

        QStringList list;
        list.push_front(QString::fromStdString(ui->lineEdit->text().toStdString()));
        QTreeWidgetItem* child = new QTreeWidgetItem(list, 0);
        _item->addChild(child);
    }
    catch(NameException* e)
    {
        QMessageBox::critical(this, "Error", "Name field is empty! You must enter the name");
        return;
    }
}

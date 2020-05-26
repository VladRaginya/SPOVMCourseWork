#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionDeleteKey->setEnabled(false);
    ui->actionAddKey->setEnabled(false);
    ui->actionDeleteValue->setEnabled(false);
    ui->actionAddValue->setEnabled(false);
    ui->tableWidget->setSelectionBehavior( QAbstractItemView::SelectRows );
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    controller = new Controller();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    QString baseKey, subkey;
    if(item->text(0) == "Computer") return;
    QTreeWidgetItem* parent = item->parent();
    if(parent->text(0) == "Computer")
    {
        baseKey = item->text(0);
        subkey = "";
    }
    else
    {
        subkey = item->text(0);
        while(parent->parent()->text(0) != "Computer")
        {
            subkey = parent->text(0) + "//" + subkey;
            parent = parent->parent();
        }
        baseKey = parent->text(0);

    }

    vector<string> subkeys;
    subkeys = controller->getSubkeysByKey(baseKey.toStdString(), subkey.toStdString());
    while(item->childCount() != 0) item->removeChild(item->child(0));
    for(int i = 0; i < subkeys.size(); i++)
    {
        QStringList list;
        list.push_front(QString::fromStdString(subkeys[i]));
        QTreeWidgetItem* child = new QTreeWidgetItem(list, 0);
        item->addChild(child);
    }
}

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    QString baseKey, subkey;
    if(item->text(0) == "Computer")
    {
        ui->actionDeleteKey->setEnabled(false);
        ui->actionAddKey->setEnabled(false);
        ui->actionDeleteValue->setEnabled(false);
        ui->actionAddValue->setEnabled(false);
        return;
    }
    QTreeWidgetItem* parent = item->parent();
    ui->actionAddKey->setEnabled(true);
    ui->actionAddValue->setEnabled(true);
    if(parent->text(0) == "Computer")
    {
        ui->actionDeleteKey->setEnabled(false);
        baseKey = item->text(0);
        subkey = "";
    }
    else
    {
        ui->actionDeleteKey->setEnabled(true);
        subkey = item->text(0);
        while(parent->parent()->text(0) != "Computer")
        {
            subkey = parent->text(0) + "\\" + subkey;
            parent = parent->parent();
        }
        baseKey = parent->text(0);

    }

    vector<string> values;
    values = controller->getValuesByKey(baseKey.toStdString(), subkey.toStdString());
    ui->tableWidget->setRowCount(values.size() / 3);
    for(int i = 0, j = 0; i < values.size(); j++)
    {
            QTableWidgetItem* name = new QTableWidgetItem(0);
            name->setFlags(name->flags() & ~Qt::ItemIsEditable);
            if(values[i] == "")
            {
                name->setText("(Default)");
                i++;
            }
            else
            {
                name->setText(QString::fromStdString(values[i++]));
            }
            ui->tableWidget->setItem(j,0, name);
            QTableWidgetItem* type = new QTableWidgetItem(0);
            type->setFlags(type->flags() & ~Qt::ItemIsEditable);
            type->setText(QString::fromStdString(values[i++]));
            ui->tableWidget->setItem(j,1, type);
            QTableWidgetItem* value = new QTableWidgetItem(0);
            value->setFlags(value->flags() & ~Qt::ItemIsEditable);
            if(values[i] == "")
            {
                value->setText("(Value not set)");
                i++;
            }
            else
            {
                if(type->text() == "REG_BINARY")
                {

                    string dataString;
                    unsigned char byte;
                    stringstream ss;
                    for(int k = 0; k < values[i].size(); k++)
                    {
                        byte = values[i][k];
                        ss << hex << (int)byte;
                    }
                    dataString = ss.str();
                    value->setText(QString::fromStdString(dataString));
                    i++;
                }
                else
                value->setText(QString::fromStdString(values[i++]));
            }
            ui->tableWidget->setItem(j,2, value);
    }

}


void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{

    if(item->column() == 0)
    {
        QTableWidgetItem* value = ui->tableWidget->item(item->row(), 2);
        if(ui->tableWidget->item(item->row(), 1)->text() == "REG_SZ")
        {
            EditStringDialog window(this, controller, item, value, ui->treeWidget->selectedItems()[0]);
            window.setModal(true);
            window.exec();
        }
        if(ui->tableWidget->item(item->row(), 1)->text() == "REG_DWORD")
        {
            EditDwordDialog window(this, controller, item, value, ui->treeWidget->selectedItems()[0]);
            window.setModal(true);
            window.exec();
        }
        if(ui->tableWidget->item(item->row(), 1)->text() == "REG_BINARY")
        {
            EditBinaryDialog window(this, controller, item, value, ui->treeWidget->selectedItems()[0]);
            window.setModal(true);
            window.exec();
        }
        if(ui->tableWidget->item(item->row(), 1)->text() == "REG_QWORD")
        {
            EditQwordDialog window(this, controller, item, value, ui->treeWidget->selectedItems()[0]);
            window.setModal(true);
            window.exec();
        }
    }

}


void MainWindow::on_actionDeleteKey_triggered()
{

    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0) {
        QTreeWidgetItem* item = selected[0];
        QString baseKey, subkey;
        if(item->text(0) == "Computer") return;
        QTreeWidgetItem* parent = item->parent();
        if(parent->text(0) == "Computer")
        {
            baseKey = item->text(0);
            subkey = "";
        }
        else
        {
            subkey = item->text(0);
            while(parent->parent()->text(0) != "Computer")
            {
                subkey = parent->text(0) + "\\" + subkey;
                parent = parent->parent();
            }
            baseKey = parent->text(0);

        }

        try
        {
            if(!controller->deleteKey(baseKey.toStdString(), subkey.toStdString()))
            {
                throw new BaseException();
            }
        }
        catch(BaseException * e)
        {
            QMessageBox::critical(this, "Error", "Internal error");
            return;
        }

        delete item;
    }
}


void MainWindow::on_actionDeleteValue_triggered()
{
    QList<QTreeWidgetItem*> selectedTree = ui->treeWidget->selectedItems();
    QList<QTableWidgetItem*> selectedTable = ui->tableWidget->selectedItems();
    if(selectedTable.size() > 0) {
        QTreeWidgetItem* item = selectedTree[0];
        QTableWidgetItem* itemTable = selectedTable[0];
        QString baseKey, subkey;
        if(item->text(0) == "Computer") return;
        QTreeWidgetItem* parent = item->parent();
        if(parent->text(0) == "Computer")
        {
            baseKey = item->text(0);
            subkey = "";
        }
        else
        {
            subkey = item->text(0);
            while(parent->parent()->text(0) != "Computer")
            {
                subkey = parent->text(0) + "\\" + subkey;
                parent = parent->parent();
            }
            baseKey = parent->text(0);

        }
        try
        {
            if(!controller->deleteValue(baseKey.toStdString(), subkey.toStdString(), itemTable->text().toStdString()))
            {
                throw new BaseException();
            }
        }
        catch(BaseException * e)
        {
            QMessageBox::critical(this, "Error", "Internal error");
            return;
        }

        ui->tableWidget->removeRow(itemTable->row());
    }
}

void MainWindow::on_actionAddKey_triggered()
{
    QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
    if(selected.size() > 0) {
        QTreeWidgetItem* item = selected[0];
        AddKeyDialog* window = new AddKeyDialog(this, controller, item);
        window->setModal(true);
        window->exec();
    }

}

void MainWindow::on_actionAddValue_triggered()
{
        QList<QTreeWidgetItem*> selected = ui->treeWidget->selectedItems();
        if(selected.size() > 0) {
        QTreeWidgetItem* item = selected[0];
        AddValueDialog* window = new AddValueDialog(this, controller, item, ui->tableWidget);
        window->setModal(true);
        window->exec();

    }
}

void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    ui->actionDeleteValue->setEnabled(true);
}

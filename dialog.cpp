#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setData(QString url, QString name)
{
    ui->urlLineEdit->setText(url);
    ui->nameLineEdit->setText(name);
}

QString Dialog::getURL()
{
    return ui->urlLineEdit->text();
}

QString Dialog::getName()
{
    return ui->nameLineEdit->text();
}

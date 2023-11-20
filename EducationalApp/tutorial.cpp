#include "tutorial.h"
#include "ui_tutorial.h"

Tutorial::Tutorial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tutorial)
{
    ui->setupUi(this);
}

Tutorial::~Tutorial()
{
    delete ui;
}

void Tutorial::setDescriptionText(QString text) {
    ui->descriptionLabel->setText(text);
}

void Tutorial::setHyperlink(QString link) {
    this->link = link;
}

void Tutorial::on_linkButton_clicked()
{
    QDesktopServices::openUrl(QUrl(this->link));
}

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <QDialog>
#include <QDesktopServices>

namespace Ui {
class Tutorial;
}

class Tutorial : public QDialog
{
    Q_OBJECT

public:
    explicit Tutorial(QWidget *parent = nullptr);
    ~Tutorial();
    void setDescriptionText(QString text);
    void setHyperlink(QString link);

private slots:
    void on_linkButton_clicked();

private:
    Ui::Tutorial *ui;
    QString link;
};

#endif // TUTORIAL_H

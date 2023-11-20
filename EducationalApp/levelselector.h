#ifndef LEVELSELECTOR_H
#define LEVELSELECTOR_H

#include <QMainWindow>
#include <iomanip>
#include <sstream>
#include "educationalapp.h"
#include "equationhandler.h"
#include "tutorial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LevelSelector; }
QT_END_NAMESPACE

class LevelSelector : public QMainWindow
{
    Q_OBJECT

public:
    LevelSelector(QWidget *parent = nullptr);
    ~LevelSelector();
    string convertToStringWithPrecision2(float val);

private slots:
    void on_levelSelector1_Button_clicked();
    void on_levelSelector2_Button_clicked();
    void on_levelSelector3_Button_clicked();
    void on_levelSelector4_Button_clicked();
    void on_guideVariables_Button_clicked();
    void on_movementGuide_Button_clicked();
    void on_equationGuide_Button_clicked();

private:
    Ui::LevelSelector *ui;
    EducationalApp *gameWindow = new EducationalApp();
    EquationHandler *getInitialValues = new EquationHandler();
    Tutorial *tutorialWindow = new Tutorial();
};
#endif // LEVELSELECTOR_H

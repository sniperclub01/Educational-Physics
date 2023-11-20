#ifndef EDUCATIONALAPP_H
#define EDUCATIONALAPP_H

#include <QMainWindow>
#include <DraggableItem.h>
#include <QKeyEvent>
#include <iostream>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
#include <QTime>
#include <scene.h>
#include <equationhandler.h>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class EducationalApp; }
QT_END_NAMESPACE

class EducationalApp : public QMainWindow
{
    Q_OBJECT

public:
    EducationalApp(QWidget *parent = nullptr);
    ~EducationalApp();

    void drawBoundaries();
    void createAnswers(vector<QString> answers);
    QGraphicsItemGroup* groupAnswer(DraggableItem* answerBox, QGraphicsTextItem* answerText);
    void setAnswerText(vector<float> answers);
    void applyImpulse(float initX, float initY);
    void paintEvent(QPaintEvent *);
    void setTargetDistance(float x);
    void setInitVelocity(float x, float y);
    void showLaunchButton();
    void getAnswer();
    void getEndState();
    void setCorrectAnswer(float answer);

    static vector<int> levelCompletion;

private:
    Ui::EducationalApp *ui;
    QGraphicsScene scene;
    float targetDistance;
    float initX;
    float initY;
    float userAnswer;
    bool isLvl;
    float answer;

public slots:
    void setPromptText(const QString);

signals:
    void valueChanged(const QString);
private slots:
    void on_launchButton_clicked();
    void on_actionGo_back_to_main_menu_triggered();
};
#endif // EDUCATIONALAPP_H

#ifndef SCENE_H
#define SCENE_H


#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QPainter>
#include <QtMath>
#include <iostream>

class Scene : public QWidget
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = nullptr, float _Xvel = 0, float _Yvel = 0, float _initHeight = 0);
    void paintEvent(QPaintEvent *);
    void applyImpulse(float initX, float initY);

    bool getEndState();
    void setEndState(bool state);

signals:
    void levelSelected();

public slots:
    void updateWorld();

private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
    float Xvel;
    float Yvel;
    float initHeight;
    static bool endState;
    int count;
};


#endif // SCENE_H

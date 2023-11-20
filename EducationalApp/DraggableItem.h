#ifndef DRAGGABLEITEM_H
#define DRAGGABLEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <iostream>

class DraggableItem : public QGraphicsRectItem
{
    QGraphicsTextItem m_text;
public:
    DraggableItem(const std::string &answer, QGraphicsItem* parent = 0);
    void setAnchor(const QPointF& anchorPoint);
    void setTarget(QGraphicsItem* target);
    void setAnswer(float answer);
    float getAnswer();
    void setText(const std::string &text);
    static float userAnswer;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPointF anchorPoint;
    bool m_Dragged;
    QGraphicsItem* targetCollision = nullptr;
    bool collidesWithTarget;
    float answerText;
};

#endif // DRAGGABLEITEM_H

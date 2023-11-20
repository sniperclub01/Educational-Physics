#include "DraggableItem.h"

float DraggableItem::userAnswer = 0;

/**
 * @brief Constructor for draggable items
 * @param answer: the value on the draggable item
 * @param parent
 */
DraggableItem::DraggableItem(const std::string &answer, QGraphicsItem* parent) :
    QGraphicsRectItem(parent), m_text(this), m_Dragged(false)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setText(answer);
    char* endptr;
    answerText = std::strtof(answer.c_str(), &endptr);
}

/**
 * @brief Sets the value to be displayed on a draggable item.
 * @param answer: the value to be displayed
 */
void DraggableItem::setText(const std::string &answer) {
    QFont font("Seqoe UI");
    font.setPointSize(15);
    m_text.setPlainText(QString::fromStdString(answer));
    m_text.setFont(font);
    m_text.setPos(37.5 - m_text.boundingRect().width()/2, 37.5 - m_text.boundingRect().height()/2);
}

/**
 * @brief This method sets the location of a draggable item.
 * @param anchorPoint: location of where the draggable item is placed
 */
void DraggableItem::setAnchor(const QPointF &anchorPoint) {
    this->anchorPoint = anchorPoint;
}

/**
 * @brief This method detecs when a draggable item is dragged
 * @param event: mouse event
 */
void DraggableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    setZValue(+1);
    m_Dragged = true;
    QGraphicsRectItem::mouseMoveEvent(event);
}

/**
 * @brief This method detecs when a draggable item is dragged
 * @param event: mouse event
 */
void DraggableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (m_Dragged) {
        QList<QGraphicsItem*> collisions = collidingItems();

        // Make sure it isn't colliding with it's own text
        for(int i = 0; i < collisions.size(); i++) {
            if (collisions.at(i) == &m_text) {
                collisions.removeAt(i);
            }
        }

        // If our collisions are empty, we go back!
        if (collisions.isEmpty()) {
            this->setPos(anchorPoint);
        }
        else { // If we have collisions, check to see if the target is there, and no other answers
            if (collisions.contains(targetCollision) && (collisions.size() <= 2)) {
                this->setPos(targetCollision->scenePos());
                setAnswer(answerText);
            }
            else { // If there are other answers in the slot, go back
                this->setPos(anchorPoint);
            }
        }
        m_Dragged = false;
    }
    setZValue(0);
    QGraphicsRectItem::mouseReleaseEvent(event);
}

/**
 * @brief DraggableItem::setAnswer
 * @param answer
 */
void DraggableItem::setAnswer(float answer) {
    DraggableItem::userAnswer = answer;
}

/**
 * @brief This method gets the value of a draggable item
 * @return
 */
float DraggableItem::getAnswer() {
    return DraggableItem::userAnswer;
}

/**
 * @brief This method detecs if a draggable item collides with a target
 * @param target
 */
void DraggableItem::setTarget(QGraphicsItem* target) {
    targetCollision = target;
}

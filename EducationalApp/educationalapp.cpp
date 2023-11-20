#include "educationalapp.h"
#include "ui_educationalapp.h"

/// Used to figure out what levels have been completed before or not.
vector<int> EducationalApp::levelCompletion{0, 0, 0, 0}; // Must be initialized.

/**
 * @brief Constructor
 * @param parent
 */
EducationalApp::EducationalApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EducationalApp)

{
    ui->setupUi(this);
    ui->widget->show();
    ui->endStateButton->setVisible(false);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setStyleSheet("background: transparent");
    QPixmap bkgnd(":/images/background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

/**
 * @brief Destructor
 */
EducationalApp::~EducationalApp()
{
    delete ui;
}

/**
 * @brief This method displays the problem statement
 * @param text
 */
void EducationalApp::setPromptText(QString text) {
    ui->label->setStyleSheet("QLabel { background-color : transparent; color : white; }");
    ui->label->setText(text);
}

/**
 * @brief This mehtod provides draggable items with the value to be displayed.
 * @param answers
 */
void EducationalApp::createAnswers(vector<QString> answers) {
    ui->graphicsView->setSceneRect(0,0,771,150);
    QRectF rect(0,0,75,75);

    // Create the answerTarget (where answers should go!)
    DraggableItem* answerTarget = new DraggableItem("");
    answerTarget->setRect(rect);
    answerTarget->setPos(400, 37.5);
    answerTarget->setFlag(QGraphicsItem::ItemIsSelectable, false);
    answerTarget->setFlag(QGraphicsItem::ItemIsMovable, false);

    QBrush brushTest(Qt::darkGray, Qt::Dense5Pattern);
    answerTarget->setBrush(brushTest);
    QGraphicsRectItem* equationBox = new QGraphicsRectItem(0, 0, 450, 75);
    equationBox->setPos(368, 0);

    // Create all answer objects

    DraggableItem* answer1Box = new DraggableItem(answers.at(0).toStdString());
    DraggableItem* answer2Box = new DraggableItem(answers.at(1).toStdString());
    DraggableItem* answer3Box = new DraggableItem(answers.at(2).toStdString());
    DraggableItem* answer4Box = new DraggableItem(answers.at(3).toStdString());
    DraggableItem* answer5Box = new DraggableItem(answers.at(4).toStdString());
    DraggableItem* answer6Box = new DraggableItem(answers.at(5).toStdString());
    DraggableItem* answer7Box = new DraggableItem(answers.at(6).toStdString());
    DraggableItem* answer8Box = new DraggableItem(answers.at(7).toStdString());
    answer1Box->setRect(rect);
    answer2Box->setRect(rect);
    answer3Box->setRect(rect);
    answer4Box->setRect(rect);
    answer5Box->setRect(rect);
    answer6Box->setRect(rect);
    answer7Box->setRect(rect);
    answer8Box->setRect(rect);

    answer1Box->setPos(0, 0);
    answer2Box->setPos(75, 0);
    answer3Box->setPos(150, 0);
    answer4Box->setPos(225, 0);
    answer5Box->setPos(0, 75);
    answer6Box->setPos(75, 75);
    answer7Box->setPos(150, 75);
    answer8Box->setPos(225, 75);

    answer1Box->setAnchor(answer1Box->pos());
    answer2Box->setAnchor(answer2Box->pos());
    answer3Box->setAnchor(answer3Box->pos());
    answer4Box->setAnchor(answer4Box->pos());
    answer5Box->setAnchor(answer5Box->pos());
    answer6Box->setAnchor(answer6Box->pos());
    answer7Box->setAnchor(answer7Box->pos());
    answer8Box->setAnchor(answer8Box->pos());

    answer1Box->setTarget(answerTarget);
    answer2Box->setTarget(answerTarget);
    answer3Box->setTarget(answerTarget);
    answer4Box->setTarget(answerTarget);
    answer5Box->setTarget(answerTarget);
    answer6Box->setTarget(answerTarget);
    answer7Box->setTarget(answerTarget);
    answer8Box->setTarget(answerTarget);

    QList<DraggableItem*> answerList;
    answerList.push_back(answer1Box);
    answerList.push_back(answer2Box);
    answerList.push_back(answer3Box);
    answerList.push_back(answer4Box);
    answerList.push_back(answer5Box);
    answerList.push_back(answer6Box);
    answerList.push_back(answer7Box);
    answerList.push_back(answer8Box);

    /// cool random colored answer stuff
    QRadialGradient gradient(37.5, 37.5, 60, 37.5, 37.5); // x, y, centerRadius, (fx, fy focal point), focus radius
    for (int i = 0; i < answerList.size(); i++) {
        QColor color;
        int colorPicker = rand()%5;
        if (colorPicker == 0) {
            color = QColor::fromRgbF(0.1,0.9,0.1,1); // green
        }
        else if (colorPicker == 1) {
            color = QColor::fromRgbF(1,0.1,0.6,1); // pink
        }
        else if (colorPicker == 2) {
            color = QColor::fromRgbF(1,0.6,0,1); // orange
        }
        else if (colorPicker == 3) {
            color = QColor::fromRgbF(0.8,0.8,0,1); // yellow
        }
        else if (colorPicker == 4) {
            color = QColor::fromRgbF(0.4,0.2,1,1); // purple
        }
        gradient.setColorAt(0, color);
        gradient.setColorAt(1, QColor::fromRgbF(0,0,0,0));
        answerList.at(i)->setBrush(gradient);
    }

    scene.addItem(answerTarget);
    scene.addItem(answer1Box);
    scene.addItem(answer2Box);
    scene.addItem(answer3Box);
    scene.addItem(answer4Box);
    scene.addItem(answer5Box);
    scene.addItem(answer6Box);
    scene.addItem(answer7Box);
    scene.addItem(answer8Box);
}

/**
 * @brief This method adds values to a corresponding draggable item
 * @param answerBox
 * @param answerText
 * @return
 */
QGraphicsItemGroup* EducationalApp::groupAnswer(DraggableItem* answerBox, QGraphicsTextItem* answerText) {
    QGraphicsItemGroup* groupedItem = new QGraphicsItemGroup();
    groupedItem->addToGroup(answerBox);
    groupedItem->addToGroup(answerText);
    //groupedItem->setFlag(QAbstractGraphicsShapeItem::ItemIsMovable);
    return groupedItem;
}

/**
 * @brief This method gets the value from a draggable item
 */
void EducationalApp::getAnswer() {
    DraggableItem* temp = new DraggableItem("");
    userAnswer = temp->getAnswer();
}

/**
 * @brief This method draws the target on the scene
 */
void EducationalApp::paintEvent(QPaintEvent *) {
    QImage image(":/images/target.png");
    //QImage image2(":/images/background.png");
    QPainter painter(this);
    //painter.drawImage(0, 180, image2);

    image = image.scaled(60, 60, Qt::KeepAspectRatio);
    painter.drawImage(this->targetDistance - 15, 530, image);
    painter.end();
}

/**
 * @brief This method sets the location where the target item is draw on the scene
 * @param x
 */
void EducationalApp::setTargetDistance(float x) {
    this->targetDistance = x;
}

/**
 * @brief This method sets the intial velocity
 * @param x
 * @param y
 */
void EducationalApp::setInitVelocity(float x, float y) {
    this->initX = x;
    this->initY = y;
}

/**
 * @brief This method displays the launch button
 */
void EducationalApp::showLaunchButton() {
    ui->launchButton->setVisible(true);
}

/**
 * @brief This method applies impulse to the cannon ball
 * @param x
 * @param y
 */
void EducationalApp::applyImpulse(float x, float y) {
    ui->widget->applyImpulse(x, y);
}

/**
 * @brief This method launches the cannon ball
 */
void EducationalApp::on_launchButton_clicked()
{
    QImage win(":/images/well_done.png");
    QImage loss(":/images/fail.png");
    QImage endState;
    getAnswer();
    Scene tempScene;

    if (userAnswer != 0) {
        if ((int)userAnswer < (int)this->answer) {
            this->applyImpulse(initX*.8, initY*.7);
            endState = loss;

        }
        else if ((int)userAnswer > (int)this->answer) {
            this->applyImpulse(initX*1.3, initY*1.2);
            endState = loss;
        }
        else {
            this->applyImpulse(initX, initY);
            endState = win;
        }

        ui->endStateButton->setIcon(QPixmap::fromImage(endState));
        ui->launchButton->setVisible(false);
        //ui->endStateButton->setVisible(true);
    }

    EquationHandler tempFlight;
    QTime delay= QTime::currentTime().addSecs(tempFlight.getFlightTime());
    while (QTime::currentTime() < delay){
        if (tempScene.getEndState()) {
            ui->endStateButton->setVisible(true);
            delay = delay.currentTime();
            break;
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents);
    }
    // Reset to 0 to prevent instantly launching with same value in next level.
    DraggableItem* temp = new DraggableItem("");
    temp->setAnswer(0);
    tempScene.setEndState(false);
}

/**
 * @brief This method sets the correct answer
 * @param answer
 */
void EducationalApp::setCorrectAnswer(float answer) {
    this->answer = answer;
}

#include "levelselector.h"
/**
 * @brief This method allows users to go back to the main menu
 */
void EducationalApp::on_actionGo_back_to_main_menu_triggered()
{
    this->hide();
    LevelSelector *lvl = new LevelSelector();
    lvl->show();
}


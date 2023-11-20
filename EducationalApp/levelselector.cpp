#include "levelselector.h"
#include "ui_levelselector.h"

/**
 * @brief Constructor
 * @param parent
 */
LevelSelector::LevelSelector(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LevelSelector)
{
    ui->setupUi(this);

    this->centralWidget()->setStyleSheet(
             "background-image:url(\":/images/level_selector_background.png\"); background-position: center;" );

    QPixmap title = QPixmap(":/images/title.png");
    title = title.scaled(title.size() * .7);
    ui->label->setPixmap(title);


    QPixmap tutorial = QPixmap(":/images/tutorial.png");
    tutorial = tutorial.scaled(tutorial.size() * .2);
    ui->label_2->setPixmap(tutorial);

    QPixmap levels = QPixmap(":/images/level_selector.png");
    levels = levels.scaled(levels.size() * .2);
    ui->label_3->setPixmap(levels);
}
/**
 * @brief Destructor
 */
LevelSelector::~LevelSelector() {
    delete ui;
}


// Level Selection Buttons
/*
 * Level 1: Given angle and velocity, calculate distance.
 */
void LevelSelector::on_levelSelector1_Button_clicked()
{
    this->hide();

    // generate random values for problem:
    vector<float> initValues = getInitialValues->CalculateInputsFromDistance(420, 500);
    float initVel = initValues.at(2);
    float angle = initValues.at(1); // degrees

    //display equation and problem statement:
    QString prompt = QString::fromStdString("If the initial velocity of the ball is " +
                                            convertToStringWithPrecision2(initVel) +
                                            " and the angle of that velocity from the horizontal is " +
                                            convertToStringWithPrecision2(angle) +
                                            " degrees, what is the distance the ball will hit the ground? \n\n" +
                                            "(Drag correct answer into the right box)");
    gameWindow->setPromptText(prompt);
    gameWindow->showLaunchButton();

    //place the world object at the initial positions. (ball and target)
    float targetDistance = initValues.at(0);
    gameWindow->setTargetDistance(targetDistance);
    gameWindow->setCorrectAnswer(targetDistance);
    gameWindow->update();

    // draw lines for floor, angle, and distance:
    vector<QString> possibleAnswers = getInitialValues->GeneratePossibleAnswers(targetDistance, 8);
    gameWindow->createAnswers(possibleAnswers);

    // re-calculate to get initial velecities that box2D can use:
    float box_d = targetDistance/20;
    float box_initV = sqrt((box_d*9.81)/(2*cos(qDegreesToRadians(angle))*sin(qDegreesToRadians(angle))));
    float initX = box_initV*cos(qDegreesToRadians(angle));
    float initY = box_initV*sin(qDegreesToRadians(angle));
    std::cout << "Correct distance: " << targetDistance << std::endl;
    gameWindow->setInitVelocity(initX, initY);
    gameWindow->show();

}

/*
 * Level 2: Given angle and distance, calculate initial velocity.
 */
void LevelSelector::on_levelSelector2_Button_clicked()
{
    this->hide();

    // generate random values for problem:
    vector<float> initValues = getInitialValues->CalculateInputsFromDistance(420, 500);
    float initVel = initValues.at(2);
    float angle = initValues.at(1); // degrees
    float targetDistance = initValues.at(0);

    //display equation and problem statement:
    QString prompt = QString::fromStdString("The angle of that velocity from the horizontal is " +
                                            convertToStringWithPrecision2(angle) +
                                            " degrees, and you want to hit a target ," +
                                            convertToStringWithPrecision2(targetDistance) +
                                            " meters away, what is the inital velocity you will need? (in meters per second)\n\n" +
                                            "(Round answer down)");
    gameWindow->setPromptText(prompt);
    gameWindow->setTargetDistance(targetDistance);
    gameWindow->setCorrectAnswer(initVel);
    gameWindow->update();
    cout << initVel << endl;
    vector<QString> possibleAnswers = getInitialValues->GeneratePossibleAnswers(initVel, 8);
    gameWindow->createAnswers(possibleAnswers);

    float box_d = targetDistance/20;
    float box_initV = sqrt((box_d*9.81)/(2*cos(qDegreesToRadians(angle))*sin(qDegreesToRadians(angle))));
    float initX = box_initV*cos(qDegreesToRadians(angle));
    float initY = box_initV*sin(qDegreesToRadians(angle));

    gameWindow->setInitVelocity(initX, initY);
    gameWindow->show();
}

/*
 * Level 3: Given angle and velocity, calculate time of flight.
 */
void LevelSelector::on_levelSelector3_Button_clicked()
{
    this->hide();

    // generate random values for problem:
    vector<float> initValues = getInitialValues->CalculateInputsFromDistance(420, 500);
    float initVel = initValues.at(2);
    float angle = initValues.at(1); // degrees
    float timeOfFlight = initValues.at(3);

    //display equation and problem statement:
    QString prompt = QString::fromStdString("If the initial velocity of the ball is " +
                                            convertToStringWithPrecision2(initVel) +
                                            " and the angle of that velocity from the horizontal is " +
                                            convertToStringWithPrecision2(angle) +
                                            " degrees, how long will the ball be in the air before it falls"
                                            " back down to the ground?\n\n" +
                                            "(Round answer down)");
    gameWindow->setPromptText(prompt);
    float targetDistance = initValues.at(0);

    gameWindow->setTargetDistance(targetDistance);
    gameWindow->setCorrectAnswer(timeOfFlight);
    gameWindow->update();
    cout << timeOfFlight << endl;
    vector<QString> possibleAnswers = getInitialValues->GeneratePossibleAnswers(timeOfFlight, 8);
    gameWindow->createAnswers(possibleAnswers);

    float box_d = targetDistance/20;
    float box_initV = sqrt((box_d*9.81)/(2*cos(qDegreesToRadians(angle))*sin(qDegreesToRadians(angle))));
    float initX = box_initV*cos(qDegreesToRadians(angle));
    float initY = box_initV*sin(qDegreesToRadians(angle));

    gameWindow->setInitVelocity(initX, initY);
    gameWindow->show();
}

/*
 * Level 4: Given angle and velocity, calculate max height.
 */
void LevelSelector::on_levelSelector4_Button_clicked()
{
    this->hide();

    // generate random values for problem:
    vector<float> initValues = getInitialValues->CalculateInputsFromDistance(420, 500);
    float initVel = initValues.at(2);
    float angle = initValues.at(1); // degrees
    float maxH = initValues.at(4);
    //display equation and problem statement:
    QString prompt = QString::fromStdString("If the initial velocity of the ball is " +
                                            convertToStringWithPrecision2(initVel) +
                                            " and the angle of that velocity from the horizontal is " +
                                            convertToStringWithPrecision2(angle) +
                                            " degrees, what is the maximum height the ball will reach?\n\n" +
                                            "(Round answer down)");
    gameWindow->setPromptText(prompt);
    gameWindow->show();
    float targetDistance = initValues.at(0);

    gameWindow->setTargetDistance(targetDistance);
    gameWindow->setCorrectAnswer(maxH);
    gameWindow->update();
    cout << maxH << endl;
    vector<QString> possibleAnswers = getInitialValues->GeneratePossibleAnswers(maxH, 8);
    gameWindow->createAnswers(possibleAnswers);

    float box_d = targetDistance/20;
    float box_initV = sqrt((box_d*9.81)/(2*cos(qDegreesToRadians(angle))*sin(qDegreesToRadians(angle))));
    float initX = box_initV*cos(qDegreesToRadians(angle));
    float initY = box_initV*sin(qDegreesToRadians(angle));

    gameWindow->setInitVelocity(initX, initY);
    gameWindow->show();
}

/**
 * @brief Displays problem statement
 */
void LevelSelector::on_guideVariables_Button_clicked()
{
    //this->hide();
    tutorialWindow->setHyperlink("https://openstax.org/books/university-physics-volume-1/pages/4-1-displacement-and-velocity-vectors");
    tutorialWindow->show();
    tutorialWindow->setDescriptionText("Displacement and velocity in two or three "
                                       "dimensions are straightforward extensions "
                                       "of the one-dimensional definitions. However, "
                                       "now they are vector quantities, so calculations "
                                       "with them have to follow the rules of vector "
                                       "algebra, not scalar algebra.");
}

/**
 * @brief Displays problem statement
 */
void LevelSelector::on_movementGuide_Button_clicked()
{
    //this->hide();
    tutorialWindow->setHyperlink("https://openstax.org/books/university-physics-volume-1/pages/4-5-relative-motion-in-one-and-two-dimensions");
    tutorialWindow->show();
    tutorialWindow->setDescriptionText("The most important fact to remember here is that motions along perpendicular axes are independent and "
                                       "thus can be analyzed separately. We discussed this fact in Displacement and Velocity Vectors, where we "
                                       "saw that vertical and horizontal motions are independent. The key to analyzing two-dimensional "
                                       "projectile motion is to break it into two motions: one along the horizontal axis and the other "
                                       "along the vertical. (This choice of axes is the most sensible because acceleration resulting from "
                                       "gravity is vertical; thus, there is no acceleration along the horizontal axis when air resistance is "
                                       "negligible.) As is customary, we call the horizontal axis the x-axis and the vertical axis the y-axis.");
}

/**
 * @brief Displays problem statement
 */
void LevelSelector::on_equationGuide_Button_clicked()
{
    //this->hide();
    tutorialWindow->setHyperlink("https://openstax.org/books/university-physics-volume-1/pages/4-3-projectile-motion");
    tutorialWindow->show();
    tutorialWindow->setDescriptionText("To describe projectile motion completely, we must include velocity and acceleration, as well as "
                                       "displacement. We must find their components along the x- and y-axes.");

}

/**
 * @brief Converts value to string
 * @param val
 * @return
 */
string LevelSelector::convertToStringWithPrecision2(float val) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << val;
    std::string string = stream.str();
    return string;
}

#include "equationhandler.h"
#include <cstdlib>

float EquationHandler::flightTime = 0; // static variable must be initialized

EquationHandler::EquationHandler()
{

}

/*
 * Generates a random distance between min and max, and the corresponding angle and initial
 * velocity needed to hit that distance.
 *
 * @param min: minimum desired distance
 * @param max: maximum desired distance
 * @return vector in order distance, angle (deg), and initial velocity, time of flight,
 * and maximum height
 */
vector<float> EquationHandler::CalculateInputsFromDistance(int min, int max) {
    float distance = rand()%(max-min + 1) + min;
    float angle = rand()%(60-35 + 1) + 35;
    float initVel = sqrt(distance*g/(sin(2*to_radians(angle))));
    float timeFlight = 2*initVel*sin(to_radians(angle))/g;
    float maxH = (initVel*sin(to_radians(angle))*initVel*sin(to_radians(angle)))/(2*g);

    flightTime = timeFlight;

    std::vector<float> outputs;
    outputs.push_back(distance);
    outputs.push_back(angle);
    outputs.push_back(initVel);
    outputs.push_back(timeFlight);
    outputs.push_back(maxH);
    return outputs;
}


/*
 * Generates a random velocity between min and max, and given the height provided, calculates the corresponding
 * angle and the distance .
 *
 * @param minV: minimum desired velocity
 * @param maxV: maximum desired velocity
 * @param height: starting height
 * @return vector in order distance, angle (deg), initial velocity, time of flight, and max  height
 */
vector<float> EquationHandler::CalculateInputsWithHeight(int minV, int maxV, int height) {
    float initVel = rand()%(maxV-minV + 1) + minV;
    float angle = rand()%(70 + 1);
    float v_x = initVel*cos(to_radians(angle));
    float v_y = initVel*sin(to_radians(angle));
    float distance = v_x*(v_y + sqrt(v_y*v_y + 2*g*height))/g;
    float timeFlight = ((v_y) + sqrt(v_y*v_y + 2*g*height))/g;
    float maxH = (v_y*v_y)/(2*g);

    flightTime = timeFlight;

    vector<float> outputs;
    outputs.push_back(distance);
    outputs.push_back(angle);
    outputs.push_back(initVel);
    outputs.push_back(timeFlight);
    outputs.push_back(maxH);
    return outputs;
}

/*
 * Generates the specified number of random numbers that are between +-5 from the input 'answer' value.
 *
 * @param answer: correct answer
 * @return vector of randomly sorted QStrings of incorrect and correct answers
 */
vector <QString> EquationHandler::GeneratePossibleAnswers(float answer, int numAnswers) {
    int max = answer + 15;
    int min = answer - 15;
    float wrongAnswer;
    vector<QString> wrongAnswers;

    for (int i = 0; i < numAnswers - 1; i++) {
        wrongAnswer = rand()%(max-min + 1) + min;
        // check to make sure value is not the same as the answer
        if (wrongAnswer == (int)answer) {
            i--;
        }
        else {
            wrongAnswers.push_back(QString::number(wrongAnswer));
        }
    }
    wrongAnswers.push_back(QString::number((int)answer));
    std::shuffle(wrongAnswers.begin(), wrongAnswers.end(), std::random_device());
    return wrongAnswers;
}

/**
 * @brief This method determians the velocity
 * @param angle
 * @param distance
 * @return
 */
float EquationHandler::FindVelocity(float angle, float distance) {
    return sqrt((distance*g)/(sin(2*to_radians(angle))));
}

/*
 * Helper method for converting degree values to radian.
 */
double EquationHandler::to_radians(double degrees) {
    return degrees * (M_PI/180.0);
}

/**
 * @brief This method gets the flight time
 * @return
 */
float EquationHandler::getFlightTime() {
    return flightTime;
}

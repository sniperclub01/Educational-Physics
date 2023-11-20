#ifndef EQUATIONHANDLER_H
#define EQUATIONHANDLER_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <QString>

using namespace std;

class EquationHandler
{
public:
    EquationHandler();
    vector<float> CalculateInputsFromDistance(int min, int max);
    vector<float> CalculateInputsWithHeight(int minV, int maxV, int height);
    vector<QString> GeneratePossibleAnswers(float answer, int numAnswers);
    float FindVelocity(float angle, float distance);
    float getFlightTime();

private:
    const float g = 9.81; // m/s^2
    double to_radians(double degrees);
    static float flightTime;
};

#endif // EQUATIONHANDLER_H

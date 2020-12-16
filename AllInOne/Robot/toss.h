#ifndef TOSS_H
#define TOSS_H

#include <math.h>
#include <string>


class Toss
{
public:
    Toss();

    void setTossPositionX(float tossPositionX);
    void setTossPositionY(float tossPositionY);
    void setTargetPositionX(float targetPositionX);
    void setTargetPositionY(float targetPositionY);
    void setVelocity(double velocity);
    void setTestNumber(int testNumber);

    float getTossPositionX() const;
    float getTossPositionY() const;
    float getTargetPositionX() const;
    float getTargetPositionY() const;
    double getVelocity() const;
    int getTestNumber() const;

    double getAngularVelocity(double GribberToTarget);
    double getBaseAngle(double x, double y, double distanceToCup);
    double getGribberToTarget(double x1, double y1, double BaseAngle);

    std::pair<double,double> calculateThrowingInformation();
    std::pair<double, double> calculateTCPVelocity(double jointPositions[6], double jointSpeeds[6]);

private:
    int mTossPositionX;
    int mTossPositionY;
    double mVelocity;
    double mAngleVelocity;
    int mTargetPositionX;
    int mTargetPositionY;
    int mTestNumber;
};

#endif // TOSS_H

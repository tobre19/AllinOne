#include "toss.h"

Toss::Toss()
{

}

float Toss::getTossPositionX() const {
    return mTossPositionX;
}

float Toss::getTossPositionY() const {
    return mTossPositionY;
}

float Toss::getTargetPositionX() const {
    return mTargetPositionX;
}

float Toss::getTargetPositionY() const {
    return mTargetPositionY;
}

double Toss::getVelocity() const {
    return mVelocity;
}

int Toss::getTestNumber() const {
    return mTestNumber;
}

void Toss::setTossPositionX(float tossPositionX) {
    mTossPositionX = tossPositionX;
}

void Toss::setTossPositionY(float tossPositionY) {
    mTossPositionY = tossPositionY;
}

void Toss::setTargetPositionX(float targetPositionX) {
    mTargetPositionX = targetPositionX;
}

void Toss::setTargetPositionY(float targetPositionY) {
    mTargetPositionY = targetPositionY;
}

void Toss::setVelocity(double velocity) {
    mVelocity = velocity;
}

void Toss::setTestNumber(int testNumber) {
    mTestNumber = testNumber;
}

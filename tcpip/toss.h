#ifndef TOSS_H
#define TOSS_H


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

private:
    int mTossPositionX;
    int mTossPositionY;
    double mVelocity;
    int mTargetPositionX;
    int mTargetPositionY;
    int mTestNumber;
};

#endif // TOSS_H

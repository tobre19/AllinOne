#include "toss.h"
#include "iostream"

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

double Toss::getAngularVelocity(double GribberToTarget) //Function til at find hvilken vinklehastighed de valgte led skal have til at ramme målet
{
    //v = (sqrt(62990043593.51803) * GribberToTarget * sqrt(351457206744.5472 * GribberToTarget + 906137116100.7427 * ballHeight)) / (2 * (351457206744.5472 * GribberToTarget + 906137116100.7427 * ballHeight)); brug af albue
    //v = (0.04282 * GribberToTarget * sqrt(ballHeight + 0.38786 * GribberToTarget)) / (ballHeight + 0.38786 * GribberToTarget); brug af albue og skulder
    double v = (sqrt(22855775659.325) * GribberToTarget * sqrt(tan(0.37) * GribberToTarget + 1096.06)) / (2330640.5 * cos(0.37) * tan(0.37) * GribberToTarget + 2554521826.43 * cos(0.37));// brug af skulder
        return v;
}




double Toss::getBaseAngle(double x, double y, double BaseToTarget)
{
    double Angle = 1.5707963268 - atan(x / y); //finder en vinkle på basen som er tæt på målet
    double A = 2.2849850567; // 130.92 grader som er vinklen mellem basens retning og gripperen
    double distanceToGripper = 144.65; // denne værdig er altid konstant ligemeget hvilken vinkel basen af robotten har.

    double x2 = x; //laver en kopi af parameteren x
    double y2 = y; //laver en kopi af parameteren y

    while (true) { //finder den resulternde vinkle på basen ved at teste om og om igen hvor tæt skydebanen er på vores mål.
        double B = A - Angle - 1.5707963268;
        double x1 = distanceToGripper * sin(B);
        double y1 = distanceToGripper * cos(B);
        double a1 = (y2 - 0) / (x2 - 0);
        double b1 = round(y2 - a1 * x2);
        double a2 = a1;
        double b2 = (y1 - a2 * x1) * -1;
        double dist = abs(a2 * x + b2 - y) / sqrt(pow(a2, 2) + 1);
        std::cerr << "dist: " << dist;

        if (dist < 0.3 && dist > -0.3) {
            std::cerr << "End angle: " << Angle;
            break;
        }
        else if (dist > 10) {
            Angle = Angle + 0.011;
            x2 = BaseToTarget * cos(Angle);
            y2 = BaseToTarget * sin(Angle);
        }
        else if (dist <= 10) {
            Angle = Angle + 0.0003;
            x2 = BaseToTarget * cos(Angle);
            y2 = BaseToTarget * sin(Angle);
        }
    }

    return Angle;
}

double Toss::getGribberToTarget(double x, double y, double BaseAngle) { // ud fra målets koordinater og vinklen på robottens base udregner denne funktion afstanden fra gribberen til målet
    double GribberToTarget = 0;
    double Angle = BaseAngle - 2.2849850567;
    double distanceToGripper = 144.65; // denne værdig er altid konstant ligemeget hvilken vinkel basen af robotten har.

    if (Angle > 1.5708) {
        Angle = Angle - 6.2832;
    }

    double x2 = distanceToGripper * cos(Angle);
    double y2 = distanceToGripper * sin(Angle);

    return GribberToTarget = abs(sqrt(pow((x2 - x), 2) + pow((y2 - y), 2)));


}

std::pair<double,double> Toss::calculateThrowingInformation() {
    double BaseToTarget = abs(sqrt(pow(mTargetPositionX, 2) + pow(mTargetPositionY, 2)));


    double baseAngle = getBaseAngle(mTargetPositionX, mTargetPositionY, BaseToTarget);

    if (baseAngle > 1.5708) {
        baseAngle = baseAngle - 6.2832;
    }

    double GribberToTarget = getGribberToTarget(mTargetPositionX, mTargetPositionY, baseAngle);


    double angularVelocity = getAngularVelocity(GribberToTarget);

    return std::pair<double,double>(baseAngle,angularVelocity);

}

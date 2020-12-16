#include "toss.h"
#include "iostream"
#include <array>

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
//        std::cerr << "dist: " << dist;

        if (dist < 0.3 && dist > -0.3) {
//            std::cerr << "End angle: " << Angle;
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

std::pair<double, double> Toss::calculateTCPVelocity(double jointPositions[], double jointSpeeds[]) {
    double theta1 = jointPositions[0];
    double theta2 = jointPositions[1];
    double theta3 = jointPositions[2];
    double theta4 = jointPositions[3];
    double theta5 = jointPositions[4];

    //Define the elements in the Jacobian as calculated in Matlab
    double JO1_x = 0.1091*cos(theta1)+0.0823*cos(theta1)*cos(theta5)+0.425*cos(theta2)*sin(theta1)-0.3922*sin(theta1)*sin(theta2)*sin(theta3)+0.0823*cos(theta2+theta3+theta4)*sin(theta1)*sin(theta5)-0.0946*cos(theta2+theta3)*sin(theta1)*sin(theta4)-0.0946*sin(theta2+theta3)*cos(theta4)*sin(theta1)+0.3922*cos(theta2)*cos(theta3)*sin(theta1);
    double JO1_y = (1091*sin(theta1))/10000+0.0946*cos(theta4)*(1.0*cos(theta1)*cos(theta2)*sin(theta3)+1.0*cos(theta1)*cos(theta3)*sin(theta2))-(17*cos(theta1)*cos(theta2))/40+(823*cos(theta5)*sin(theta1))/10000+0.0823*sin(theta5)*(sin(theta4)*(1.0*cos(theta1)*cos(theta2)*sin(theta3)+1.0*cos(theta1)*cos(theta3)*sin(theta2))+cos(theta4)*(1.0*cos(theta1)*sin(theta2)*sin(theta3)-cos(theta1)*cos(theta2)*cos(theta3)))-(473*sin(theta4)*(1.0*cos(theta1)*sin(theta2)*sin(theta3)-cos(theta1)*cos(theta2)*cos(theta3)))/5000+0.3922*cos(theta1)*sin(theta2)*sin(theta3)-(1961*cos(theta1)*cos(theta2)*cos(theta3))/5000;
    double JO1_z = 0;

    double JO2_x = cos(theta1)*((1961*sin(theta2 + theta3))/5000 + (17*sin(theta2))/40 - (473*sin(theta2 + theta3)*sin(theta4))/5000 + sin(theta5)*(0.0823*cos(theta2 + theta3)*sin(theta4) + 0.0823*sin(theta2 + theta3)*cos(theta4)) + 0.0946*cos(theta2 + theta3)*cos(theta4) - 0.08915899693);
    double JO2_y = sin(theta1)*((1961*sin(theta2 + theta3))/5000 + (17*sin(theta2))/40 - (473*sin(theta2 + theta3)*sin(theta4))/5000 + sin(theta5)*(0.0823*cos(theta2 + theta3)*sin(theta4) + 0.0823*sin(theta2 + theta3)*cos(theta4)) + 0.0946*cos(theta2 + theta3)*cos(theta4) - 0.08915899693);
    double JO2_z = 0.04115*sin(theta2 + theta3 + theta4 - theta5) + 0.0946*sin(theta2 + theta3 + theta4) - 0.04115*sin(theta2 + theta3 + theta4 + theta5) - 0.3922*cos(theta2 + theta3) - 0.425*cos(theta2) - 1.0;

    double JO3_x = (cos(theta1)*(946.0*cos(theta2 + theta3 + theta4) + 3922.0*sin(theta2 + theta3) + 823.0*sin(theta2 + theta3 + theta4)*sin(theta5)))/10000;
    double JO3_y = (sin(theta1)*(946.0*cos(theta2 + theta3 + theta4) + 3922.0*sin(theta2 + theta3) + 823.0*sin(theta2 + theta3 + theta4)*sin(theta5)))/10000;
    double JO3_z = 0.04115*sin(theta2 + theta3 + theta4 - theta5) + 0.0946*sin(theta2 + theta3 + theta4) - 0.04115*sin(theta2 + theta3 + theta4 + theta5) - 0.3922*cos(theta2 + theta3);

    double JO4_x = cos(theta1)*(0.0946*cos(theta2 + theta3 + theta4) + 0.0823*sin(theta2 + theta3 + theta4)*sin(theta5));
    double JO4_y = sin(theta1)*(0.0946*cos(theta2 + theta3 + theta4) + 0.0823*sin(theta2 + theta3 + theta4)*sin(theta5));
    double JO4_z = 0.04115*sin(theta2 + theta3 + theta4 - theta5) + 0.0946*sin(theta2 + theta3 + theta4) - 0.04115*sin(theta2 + theta3 + theta4 + theta5);

    double JO5_x = 0.0823*cos(theta1)*cos(theta2)*cos(theta5)*sin(theta3)*sin(theta4) - 0.0823*cos(theta1)*cos(theta2)*cos(theta3)*cos(theta4)*cos(theta5) - 0.0823*sin(theta1)*sin(theta5) + 0.0823*cos(theta1)*cos(theta3)*cos(theta5)*sin(theta2)*sin(theta4) + 0.0823*cos(theta1)*cos(theta4)*cos(theta5)*sin(theta2)*sin(theta3);
    double JO5_y = 0.0823*cos(theta1)*sin(theta5) - 0.0823*cos(theta2)*cos(theta3)*cos(theta4)*cos(theta5)*sin(theta1) + 0.0823*cos(theta2)*cos(theta5)*sin(theta1)*sin(theta3)*sin(theta4) + 0.0823*cos(theta3)*cos(theta5)*sin(theta1)*sin(theta2)*sin(theta4) + 0.0823*cos(theta4)*cos(theta5)*sin(theta1)*sin(theta2)*sin(theta3);
    double JO5_z = -0.04115*sin(theta2 + theta3 + theta4 - theta5) - 0.04115*sin(theta2 + theta3 + theta4 + theta5);

    double JO6_x = 0;
    double JO6_y = 0;
    double JO6_z = 0;

    double z0_x = 0;
    double z0_y = 0;
    double z0_z = 1;

    double z1_x = sin(theta1);
    double z1_y = -cos(theta1);
    double z1_z = 0;

    double z2_x = sin(theta1);
    double z2_y = -cos(theta1);
    double z2_z = 0;

    double z3_x = sin(theta1);
    double z3_y = -cos(theta1);
    double z3_z = 0;

    double z4_x = sin(theta2 + theta3 + theta4)*cos(theta1);
    double z4_y = sin(theta2 + theta3 + theta4)*sin(theta1);
    double z4_z = -cos(theta2 + theta3 + theta4);

    double z5_x = cos(theta5)*sin(theta1)-cos(theta2+theta3+theta4)*cos(theta1)*sin(theta5);
    double z5_y = -cos(theta1)*cos(theta5)-cos(theta2+theta3+theta4)*sin(theta1)*sin(theta5);
    double z5_z = -sin(theta2+theta3+theta4)*sin(theta5);

    //Combine the elements of the Jacobian
    double jacobian[6][6] = {{JO1_x,    JO2_x,  JO3_x,  JO4_x,  JO5_x,  JO6_x   },
                             {JO1_y,    JO2_y,  JO3_y,  JO4_y,  JO5_y,  JO6_y   },
                             {JO1_z,    JO2_z,  JO3_z,  JO4_z,  JO5_z,  JO6_z   },
                             {z0_x,     z1_x,   z2_x,   z3_x,   z4_x,   z5_x    },
                             {z0_y,     z1_y,   z2_y,   z3_y,   z4_y,   z5_y    },
                             {z0_z,     z1_z,   z2_z,   z3_z,   z4_z,   z5_z    }};

    //Calculate the TCP velocities based on the Jacobian. Also return the tcpVelocity as a vector
    std::array<double, 6> tcpVelocity;
    for (int i = 0; i < 6; i++){
        double val = 0;
        for (int j = 0; j < 6; j++){
            val += jointSpeeds[j] * jacobian[i][j];
        }
        tcpVelocity[i] = val;
    }

    double linearVelocity = sqrt(tcpVelocity.at(0)*tcpVelocity.at(0)+tcpVelocity.at(1)*tcpVelocity.at(1)+tcpVelocity.at(2)*tcpVelocity.at(2));
    double rotationalVelocity = sqrt(tcpVelocity.at(3)*tcpVelocity.at(3)+tcpVelocity.at(4)*tcpVelocity.at(4)+tcpVelocity.at(5)*tcpVelocity.at(5));

    return std::pair<double, double>(linearVelocity, rotationalVelocity);
}

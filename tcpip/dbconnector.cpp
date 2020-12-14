#include "dbconnector.h"
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <iostream>
dbconnector::dbconnector()
{

}

bool dbconnector::connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabaseName("throws");

    if(db.open()) {
        return true;
    }

    else {
        return false;
    }
}

void dbconnector::addTossToDatabase(Toss toss) {
    std::string string;
    string = "INSERT INTO throw(throwPositionX, throwPositionY, velocity, targetPositionX, targetPositionY, testNumber) values(" + std::to_string(toss.getTossPositionX()) + ", " + std::to_string(toss.getTossPositionY()) + ", " + std::to_string(toss.getVelocity()) + ", " + std::to_string(toss.getTargetPositionX()) + ", " + std::to_string(toss.getTargetPositionY()) + ", " + std::to_string(toss.getTestNumber()) + ")";
    QString qstring = QString::fromStdString(string);
    QSqlQuery query;
    query.exec(qstring);
}

int dbconnector::getNumberOfTosses(Toss toss) {
    std::string string = "SELECT COUNT(testNumber) FROM throws.throw WHERE testNumber = " + std::to_string(toss.getTestNumber()) + ";";
    QString qString = QString::fromStdString(string);
    QSqlQuery query;
    query.exec(qString);
    int number;
    while (query.next()) {
        number = query.value(0).toInt();
    }
    return number;
}

double dbconnector::getAveragePrecision(Toss toss) {
    std::string string = "SELECT throwPrecision FROM throws.throw WHERE testNumber = " + std::to_string(toss.getTestNumber()) + ";";
    QString qString = QString::fromStdString(string);
    QSqlQuery query;
    query.exec(qString);
    double totalPrecision;
    double averagePrecision;
    while (query.next()) {
        totalPrecision += query.value(0).toDouble();
    }

    averagePrecision = totalPrecision/getNumberOfTosses(toss);

    return averagePrecision;
}

int dbconnector::getTestNumber() {
    QSqlQuery query;
    query.exec("SELECT MAX(testNumber) FROM throw");
    int testNumber;
    while(query.next()) {
        testNumber = query.value(0).toInt();
    }
    return testNumber;
}

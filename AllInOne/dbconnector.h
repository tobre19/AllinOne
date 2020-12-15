#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include "toss.h"

class dbconnector
{
public:
    dbconnector();
    bool connectToDatabase();
    void addTossToDatabase(Toss);
    int getNumberOfTosses(Toss);
    double getAveragePrecision(Toss);
    void updateGUI();
    int getTestNumber();
};

#endif // DBCONNECTOR_H

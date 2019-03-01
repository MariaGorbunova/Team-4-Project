// Created by: Zhuoxuan Wang
#include "iPhone.h"
#include <iostream>
#include <iomanip>
using namespace std;

iPhone::iPhone()
{
    IMEI = "";
    capacity = "";
    serialNum = "";
    model = "";
    manuLocn = "";
    
}
iPhone::iPhone(std::string IMEI_in, std::string capacity_in, std::string serialNum_in, std::string model_in, std::string manuLocn_in)
{
    IMEI = IMEI_in;
    capacity = capacity_in;
    serialNum = serialNum_in;
    model = model_in;
    manuLocn = manuLocn_in;
}
ostream &operator <<(ostream & out, const iPhone &obj)
{
    cout << left << setw(20) << obj.IMEI
    << setw(10) << obj.capacity
    << setw(20) << obj.serialNum
    << setw(20) << obj.model
    << setw(10) << obj.manuLocn << endl;
    return out;
}
iPhone & iPhone::operator =(const iPhone & rh)
{
    IMEI = rh.IMEI;
    capacity = rh.capacity;
    serialNum = rh.serialNum;
    model = rh.model;
    manuLocn = rh.manuLocn;
    return *this;
}
bool iPhone::operator <= (const iPhone & rh)
{
    return ((IMEI <= rh.IMEI));
    
}
bool iPhone::operator >= (const iPhone & rh)
{
    return ((IMEI >= rh.IMEI));
}
bool iPhone::operator < (const iPhone & rh)
{
    return ((IMEI < rh.IMEI));
    
}
bool iPhone::operator > (const iPhone & rh)
{
    return ((IMEI > rh.IMEI));
}

bool iPhone::operator ==(const iPhone & rh)
{
    return ((IMEI == rh.IMEI));
}

void iPhone::displayInfo()
{
    cout << left << setw(20) << IMEI
    << setw(10) << capacity
    << setw(20) << serialNum
    << setw(20) << model
    << setw(10) << manuLocn << endl;
}


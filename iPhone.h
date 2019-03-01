/// phone class
/// Dat Nguyen & Zhuoxuan Wang

#ifndef IPHONE_H
#define IPHONE_H
#include <iostream>



class iPhone
{
private:
        std::string IMEI;
        std::string capacity;
        std::string serialNum;
        std::string model;
        std::string manuLocn;
public:
    /// constructors
    iPhone(); /// default constructor
    iPhone(std::string IMEI_in, std::string capacity_in, std::string serialNum_in, std::string model_in, std::string manuLocn_in);
    
    void setIMEI(std::string IMEI_in){ IMEI = IMEI_in;}
    void setCapacity(std::string capacity_in){ capacity = capacity_in;}
    void setSerialNum(std::string serialNum_in){ serialNum = serialNum_in;}
    void setModel(std::string model_in){ model = model_in;}
    void setManuLocn(std::string manuLocn_in){ manuLocn = manuLocn_in;}
    void setInfo(std::string IMEI_in, std::string capacity_in, std::string serialNum_in, std::string model_in, std::string manuLocn_in)
    {
        IMEI = IMEI_in;
        capacity = capacity_in;
        serialNum = serialNum_in;
        model = model_in;
        manuLocn = manuLocn_in;
        
    }
    
    /// getters
    std::string getIMEI() const { return IMEI;}
    std::string getCapacity() const { return capacity;}//int myint = atoi(capacity);
    std::string getSerialNum() const { return serialNum;}
    std::string getModel() const { return model;}
    std::string getManuLocn() const { return manuLocn;}

    void displayInfo();

    friend std::ostream &operator <<(std::ostream & out, const iPhone &obj);
    iPhone &operator =(const iPhone & rh);
    bool operator < (const iPhone & rh);
    bool operator > (const iPhone & rh);
    bool operator <= (const iPhone & rh);
    bool operator >= (const iPhone & rh);
    bool operator ==(const iPhone & rh);

};
#endif

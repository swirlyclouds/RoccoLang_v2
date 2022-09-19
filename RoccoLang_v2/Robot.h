#pragma once
#include "Fake_Funcs.h"

class Sensor {
public:
    std::string name;
    Sensor(std::string name_) {
        name = name_;
    }
    virtual float getReading() {
        return -9.0f;
    }
};

class US_Sensor : public Sensor {
public:
    HCSR04* sensor;
    US_Sensor(std::string name, PinName trigg, PinName echo) : Sensor(name), sensor(new HCSR04(trigg, echo)) {
        //sensor = HCSR04(trigg, echo);    
    }
    float getReading() {
        //return -2.0f;
        return (sensor->distance(1));

    }
};

class IR_Sensor : public Sensor {
private:
    Sharp sensor;
public:
    IR_Sensor(std::string name, PinName input) : Sensor(name), sensor(Sharp(input)) {
        // sensor = Sharp(input);
    }
    float getReading() {
        return sensor.getIRDistance();
    }
};

class Robot {
private:
    m3pi m3pi;
    std::vector<Sensor*> sensors;
    float s;
    long d;
public:
    Robot() {
        m3pi.locate(0, 1);
        m3pi.printf("Hi! :)");
        d = 0;
    }

    void add_sensor(std::string name, PinName Echo, PinName Trigger) {
        sensors.push_back(new US_Sensor(name, Echo, Trigger));
    }
    void add_sensor(std::string name, PinName inp) {
        sensors.push_back(new IR_Sensor(name, inp));
    }

    bool remove_sensor(std::string name) {
        for (int i = 0; i < sensors.size(); i++) {
            if (sensors[i]->name == name) {
                delete sensors[i];
                sensors.erase(sensors.begin() + i);
                return true;
            }
        }
        return false;
    }


    void kill() {
        for (int i = 0; i < sensors.size(); i++) {
            delete sensors[i];
        }
        sensors.clear();
    }

    // DEBUG FUNCTIONS

    Sensor* getSensor(std::string name) {
        for (int i = 0; i < sensors.size(); i++) {
            if (sensors[i]->name == name) {
                return sensors[i];
            }
        }
    }

    void output() {
        wait(0.2f);
        m3pi.cls();
        s = getSensor("US")->getReading();
        m3pi.printf("US: " + std::to_string(s));
        wait(0.2f);
        m3pi.cls();
        s = getSensor("ir")->getReading();
        m3pi.printf("IR: %f" + std::to_string(s));
        d += 1;
    }

    void stats() {
        std::cout << "number of sensors: " << sensors.size() << std::endl;
    }


    void setup() {


    }
    void print(std::string txt) {
        m3pi.cls();
        m3pi.printf(txt);
    }
};
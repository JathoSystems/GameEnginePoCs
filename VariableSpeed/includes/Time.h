#ifndef VARIABLESPEED_TIME_H
#define VARIABLESPEED_TIME_H

class Time {
public:
    static Time& instance() {
        static Time instance;
        return instance;
    }

    double getModifier() const {
        return modifier;
    }

    void setModifier(double value) {
        if (value < 0.0) value = 0.0;
        else modifier = value;
    }

    void increaseModifier(double amount) {
        modifier += amount;
    }

    void decreaseModifier(double amount) {
        if (modifier - amount < 0.0) modifier = 0.0;
        else modifier -= amount;
    }

private:
    Time() : modifier(1.0) {}
    double modifier;
};

#endif //VARIABLESPEED_TIME_H
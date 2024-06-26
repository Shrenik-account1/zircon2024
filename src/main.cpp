#include <Arduino.h>
#include <zirconLib.h>
#include <iostream>
#include <BallFinding.h>
#include <math.h>

// use compass sensor to continuously make sure that the attachment is in the front
// fix weird wheel thing

double Speed_ceiling;
double FrontRight, Back, FrontLeft;
double maxVal;
double FRpower, Backpower, FLpower;
int theta1, theta2, theta3;
double avg, average, num_sens;

BallFinding ballFinder;

void setup() {
    InitializeZircon();
    Serial.begin(9600);

}

int sign(double var) {
    if (var < 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void movement(double degrees) {
    // double radians = degrees * (PI/180);
    // FrontRight = sin(radians-(3*(PI/2)));
    // Back = sin(radians - PI);
    // FrontLeft = sin(radians - (5*(PI/3)));

    // FrontRight = sin(radians - (5*(PI/3)));
    // Back = sin(radians - PI);
    // FrontLeft = sin(radians - (PI/3));

    // degrees = 360-degrees;
    Serial.println(degrees);
    theta1 = 60;
    theta2 = 180;
    theta3 = 300;

    if (degrees >= 360) {
        degrees -= 360;
    }
    FrontRight = sin((degrees-theta1)*(PI/180.0));
    Back = sin((degrees-theta2)*(PI/180.0));
    FrontLeft = sin((degrees-theta3)*(PI/180.0));

    maxVal = max(max(abs(FrontRight), abs(FrontLeft)), abs(Back));


    FRpower  = FrontRight / maxVal;
    Backpower  = Back / maxVal;
    FLpower  = FrontLeft / maxVal;

// change back to 100
    motor3(100*abs(FLpower), sign(FrontLeft));
    motor2(100*abs(FRpower), sign(FrontRight));
    motor1(100*abs(Backpower), sign(Back));
}

void reset_all () {
    motor1(0,0);
    motor2(0,0);
    motor3(0,0);

}
void loop () {
    Serial.println(readBall(1));

    while (readBall(1) > 501 || readBall(1) < 499) {
        if (ballFinder.main_calc() < 0) {
            movement(ballFinder.main_calc());
        }

        else if(ballFinder.main_calc() > 0) {
            movement(-ballFinder.main_calc());
        }

        if (readBall(1) > 501) {
            movement(180);
        }

        else if (readBall(1) < 499) {
            movement(0);
        }
    }
}


    // Serial.println(ballFinder.main_calc());
    // movement(0);

    // Serial.println("BallAngle:" + String(ballFinder.main_calc()));
    // Serial.println("Orbit" + String(ballFinder.orbit()));
    // motor1(100,1);
    // motor2(100,1);
    // motor3(100,1);
    // Serial.println(ballFinder.main_calc());
    // movement(ballFinder.orbit());
    // delay(100);

    // reset_all();

    // Serial.println("ball 1:   " + String(readBall(1)));
    // Serial.println("ball 2:   " + String(readBall(2)));
    // Serial.println("ball 3:   " + String(readBall(3)));
    // Serial.println("ball 4:   " + String(readBall(4)));
    // Serial.println("ball 5:   " + String(readBall(5)));
    // Serial.println("ball 6:   " + String(readBall(6)));
    // Serial.println("ball 7:   " + String(readBall(7)));
    // Serial.println("ball 8:   " + String(readBall(8)));

    // for (int i = 1; i < 9; i++) {
    //     if (readBall(i) >= 75) {
    //         avg += readBall(i);
    //         num_sens += 1;
    //     }
    // average = avg/num_sens;
    // Serial.println(average);
    // }
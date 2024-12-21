#pragma once
#include "subsystems/Candle.h"

//0  1   2  3   4  5   6
//0  .5  1  1.5 2  2.5 3
//on off on off on off stat

/*
start
    if disabled
        blink 0.5s yellow for 3s
        static alliance color
    elif auto or auto command
        larson yellow
    else
        if has gp
            static green
        elif wants gp
            gp color
        else
            rainbow
*/

Candle::Candle() {
    ctre::phoenix::led::CANdleConfiguration config;
    config.stripType = ctre::phoenix::led::LEDStripType::RGB; // GRB?
    config.brightnessScalar = 0.5;
    m_candle.ConfigAllSettings(config);
    m_candle.ClearAnimation(0);
    m_candle.SetLEDs(0, 0, 0);
};

void Candle::Periodic() {
    if (frc::DriverStation::IsEnabled()) {
        blink_counter = 0;
        if (IsAuto()) {
            if (state != AUTO) {
                m_candle.ClearAnimation(0);
                m_candle.Animate(m_larson_yellow);
                state = AUTO;
            }
        } else if(HasGP()) {
            if (state != HASGP) {
                m_candle.ClearAnimation(0);
                m_candle.SetLEDs(0, 255, 0);
                state = HASGP;
            }
        } else if (state == WANTGP) {
            if (wants_r + wants_g + wants_b != 0) {
                m_candle.ClearAnimation(0);
                m_candle.SetLEDs(wants_r, wants_g, wants_b);
                wants_r = 0;
                wants_g = 0;
                wants_b = 0;
            }
        } else {
            if (state != FREE) {
                m_candle.ClearAnimation(0);
                m_candle.Animate(m_rainbow);
                state = FREE;
            }
        }
    } else {
        if (blink_counter < 6) {
            if (blink_counter == 0) {
                m_candle.ClearAnimation(0);
            }
            if (timer.Get() > units::time::second_t{0.5}) {
                if (blink_counter % 2 == 0) {
                    m_candle.SetLEDs(255, 255, 0);
                } else {
                    m_candle.SetLEDs(0, 0, 0);
                }
                timer.Restart();
                blink_counter++;
            }
        } else if (blink_counter == 6) {
            if (IsRed()) {
                m_candle.SetLEDs(255, 0, 0);
            } else {
                m_candle.SetLEDs(0, 0, 255);
            }
            blink_counter++;
        }
    }
};


void Candle::WantGP(int r, int g, int b) {
    wants_r = r;
    wants_g = g;
    wants_b = b;
};


bool Candle::HasGP() {
    return false; //TODO
};


bool Candle::IsAuto() {
    return frc::DriverStation::IsAutonomousEnabled();
};


bool Candle::IsRed() {
    if (frc::DriverStation::GetAlliance()) {
        if (frc::DriverStation::GetAlliance().value() == frc::DriverStation::Alliance::kBlue) {
            return false;
        }
    }
    return true;
};
#pragma once
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include "ctre/phoenix/led/CANdle.h"
#include "ctre/phoenix/led/RainbowAnimation.h"
#include "ctre/phoenix/led/LarsonAnimation.h"
#include <frc/Timer.h>
#include <frc/DriverStation.h>
#include <units/Time.h>
#include "Constants.h"

class Candle : public frc2::SubsystemBase {
    public:
        Candle();
        void Periodic() override;
        void WantGP(int r, int g, int b);

    private:

        bool HasGP();
        bool IsAuto();
        bool IsRed();

        enum CANDLE_STATE {
            AUTO,
            WANTGP,
            HASGP,
            FREE
        };

        int blink_counter = 0;
        CANDLE_STATE state = FREE;
        int wants_r = 0;
        int wants_g = 0;
        int wants_b = 0;

        frc::Timer timer;
        ctre::phoenix::led::CANdle m_candle{CONSTANTS::CANDLE::CANDLE_ID};
                                                          // r    g   b  w  spd  num
        ctre::phoenix::led::LarsonAnimation m_larson_yellow{255, 255, 0, 0, 0.5, CONSTANTS::CANDLE::NUM_LEDS};
        //                                              brt  spd
        ctre::phoenix::led::RainbowAnimation m_rainbow {0.5, 0.5};
};
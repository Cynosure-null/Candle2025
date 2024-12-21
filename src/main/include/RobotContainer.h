#pragma once

#include <frc2/command/CommandPtr.h>
#include "commands/Autos.h"
#include "subsystems/Candle.h"


class RobotContainer {
    public:
        RobotContainer();

        frc2::CommandPtr GetAutonomousCommand();

    private:
        Candle m_candle;
};

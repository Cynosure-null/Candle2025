#pragma once

#include <frc2/command/CommandPtr.h>
#include "commands/Autos.h"
#include "subsystems/Candle.h"
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/Commands.h>


class RobotContainer {
    public:
        RobotContainer();

        void configure_bindings();

        frc2::CommandPtr GetAutonomousCommand();

    private:
    frc2::CommandXboxController m_stick{0};
        Candle m_candle{ [this]() -> bool {return m_stick.A().Get();} };
};

#include "RobotContainer.h"

RobotContainer::RobotContainer()
{
    configure_bindings();
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand()
{
    return autos::ExampleAuto();
}

void RobotContainer::configure_bindings()
{
    m_stick.B().OnTrue(frc2::cmd::RunOnce(
                                 [this]()
                                 {
                                     if (!this->m_candle.HasGP())
                                     {
                                         this->m_candle.WantGP(128, 0, 128);
                                     }
                                 },
                                 {}))
        .OnFalse(frc2::cmd::RunOnce(
            [this]()
            { this->m_candle.WantGP(0, 0, 0); }, {})

        );
}

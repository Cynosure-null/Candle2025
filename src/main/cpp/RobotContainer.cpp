#include "RobotContainer.h"

RobotContainer::RobotContainer() {

}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
    return autos::ExampleAuto();
}

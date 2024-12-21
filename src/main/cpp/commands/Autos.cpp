#include <frc2/command/Commands.h>
#include <frc2/command/PrintCommand.h>
#include "commands/Autos.h"

frc2::CommandPtr autos::ExampleAuto() {
  return frc2::PrintCommand(std::string_view{"unimplemented"}).ToPtr();
}

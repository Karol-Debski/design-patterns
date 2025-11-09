#include "rocket.hpp"


int main()
{
   std::cout<<"-> Rocket created.\n";
   Rocket rocket;

   rocket.handleCommand(RocketCommand::Arm);
   rocket.handleCommand(RocketCommand::Launch);
   rocket.handleCommand(RocketCommand::SelfDestroy);
   rocket.handleCommand(RocketCommand::TurnOff);

   std::cout<<"-> Rocket initialized.\n";
   rocket.initialize();

   rocket.handleCommand(RocketCommand::SelfDestroy);
   rocket.handleCommand(RocketCommand::Arm);
   rocket.handleCommand(RocketCommand::TurnOff);

   std::cout<<"-> Rocket initialized again.\n";
   rocket.initialize();

   rocket.handleCommand(RocketCommand::Arm);
   rocket.handleCommand(RocketCommand::Launch);
   rocket.handleCommand(RocketCommand::SelfDestroy);
}
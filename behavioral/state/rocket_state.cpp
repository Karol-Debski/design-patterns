#include <iostream> 
#include <memory>
#include "rocket_state.hpp"
#include "rocket.hpp"


std::string_view RocketOffState::getName() const
{
   return "[Off]";
}

void RocketOffState::handleCommand(IRocket& rocket, const RocketCommand command) {
   switch (command)
   {
   default:
      std::cout<<getName()<<" command ignored.\n";
      break;
   }
};

std::string_view RocketInitState::getName() const
{
   return "[Init]";
}

void RocketInitState::handleCommand(IRocket& rocket, const RocketCommand command) {
   switch (command)
   {
   case RocketCommand::Arm:
      std::cout<<"Accepted 'Arm' command!\n";
      rocket.setState(std::make_unique<RocketArmState>());
      break;
   case RocketCommand::TurnOff:
      std::cout<<"Accepted 'TurnOff' command!\n";
      rocket.setState(std::make_unique<RocketOffState>());
      break;
   default:
      std::cout<<getName()<<" command ignored.\n";
      break;
   }
};

std::string_view RocketArmState::getName() const
{
   return "[Arm]";
}

void RocketArmState::handleCommand(IRocket& rocket, const RocketCommand command) {
   switch (command)
   {
   case RocketCommand::Launch:
      std::cout<<"Accepted 'Launch' command!\n";
      rocket.setState(std::make_unique<RocketFlyingState>());
      break;
   case RocketCommand::TurnOff:
      std::cout<<"Accepted 'TurnOff' command!\n";
      rocket.setState(std::make_unique<RocketOffState>());
      break;
   default:
      std::cout<<getName()<<" command ignored.\n";
      break;
   }
};

std::string_view RocketFlyingState::getName() const
{
   return "[Flying]";
}

void RocketFlyingState::handleCommand(IRocket& rocket, const RocketCommand command) {
   switch (command)
   {
   case RocketCommand::SelfDestroy:
      std::cout<<"Accepted 'SelfDestroy' command!\n";
      rocket.selfDestroy();
      rocket.setState(std::make_unique<RocketToDestroyState>());
      break;
   default:
      std::cout<<getName()<<" command ignored.\n";
      break;
   }
};

std::string_view RocketToDestroyState::getName() const
{
   return "[ToDestroy]";
}

void RocketToDestroyState::handleCommand(IRocket& rocket, const RocketCommand command) {
   std::cout<<"All commands discarded, rocket will be destroyed soon!\n";
};

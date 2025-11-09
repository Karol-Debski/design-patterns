
#ifndef ROCKET_H
#define ROCKET_H

#include <iostream> 
#include <memory>
#include "rocket_state.hpp"
#include "rocket_command.hpp"

/*
Finite state machine of a rocket:

| OFF | -----> | INIT | ----> | ARM | ----> | FLYING | ----> | TO_DESTROY |
^--------------'              |                     
^-----------------------------'                                
*/

class IRocket
{
public:
   virtual ~IRocket() = default;
   virtual void setState(std::unique_ptr<RocketState> state) = 0;
   virtual void selfDestroy() = 0;
};

class Rocket : public IRocket
{
public:
   Rocket();
   ~Rocket() = default;

   void initialize();
   void handleCommand(const RocketCommand command);

private:
   void setState(std::unique_ptr<RocketState> state) override;
   void selfDestroy() override;
   
   std::unique_ptr<RocketState> state_;
};

#endif // ROCKET_H
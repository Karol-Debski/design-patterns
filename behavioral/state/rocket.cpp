#include <iostream> 
#include <memory>
#include "rocket.hpp"


Rocket::Rocket() : state_(std::make_unique<RocketOffState>()) {};

void Rocket::setState(std::unique_ptr<RocketState> state) {
   state_ = std::move(state);
};

void Rocket::initialize() {
   setState(std::make_unique<RocketInitState>());
};

void Rocket::handleCommand(const RocketCommand command) {
      state_->handleCommand(*this, command);
};

void Rocket::selfDestroy(){
   std::cout<<"Kabum!\n";
}

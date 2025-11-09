#ifndef ROCKET_STATE_H
#define ROCKET_STATE_H

#include <iostream> 
#include <memory>

class IRocket;
enum class RocketCommand;

class RocketState
{
public:
   virtual ~RocketState() = default;
   virtual void handleCommand(IRocket& rocket, const RocketCommand command) = 0;
   virtual std::string_view getName() const = 0;
};

class RocketOffState : public RocketState
{
public:
   RocketOffState() = default;
   ~RocketOffState() = default;

   void handleCommand(IRocket& rocket, const RocketCommand command) override;
   std::string_view getName() const override;
};

class RocketInitState : public RocketState
{
public:
   RocketInitState() = default;
   ~RocketInitState() = default;

   void handleCommand(IRocket& rocket, const RocketCommand command) override;
   std::string_view getName() const override;
};

class RocketArmState : public RocketState
{
public:
   RocketArmState() = default;
   ~RocketArmState() = default;

   void handleCommand(IRocket& rocket, const RocketCommand command) override;
   std::string_view getName() const override;
};

class RocketFlyingState : public RocketState
{
public:
   RocketFlyingState() = default;
   ~RocketFlyingState() = default;

   void handleCommand(IRocket& rocket, const RocketCommand command) override;
   std::string_view getName() const override;
};

class RocketToDestroyState : public RocketState
{
public:
   RocketToDestroyState() = default;
   ~RocketToDestroyState() = default;

   void handleCommand(IRocket& rocket, const RocketCommand command) override;
   std::string_view getName() const override;
};


#endif // ROCKET_STATE_H
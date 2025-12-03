#include <iostream>
#include <typeinfo>
#include <memory>

/*
The bridge pattern - a solution to decouple abstraction from its implementation using composition instead of inheritance.
*/

class Engine
{
public:
   virtual ~Engine() = default;

   virtual void ignite()      = 0;       
   virtual void shutdown()    = 0;         
   virtual void increaseRPM() = 0;            
};

class GasEngine : public Engine
{
public:
   GasEngine() = default;

   void ignite() override
   {
      std::cout<<"GasEngine "<<__func__<<'\n';
   }

   void shutdown() override
   {
      std::cout<<"GasEngine "<<__func__<<'\n';
   }

   void increaseRPM() override
   {
      std::cout<<"GasEngine "<<__func__<<'\n';
   }
};

class ElectricEngine : public Engine
{
public:
   ElectricEngine() = default;

   void ignite() override
   {
      std::cout<<"ElectricEngine "<<__func__<<'\n';
   }

   void shutdown() override
   {
      std::cout<<"ElectricEngine "<<__func__<<'\n';
   }

   void increaseRPM() override
   {
      std::cout<<"ElectricEngine "<<__func__<<'\n';
   }
};


class Car
{
public:
   Car(std::unique_ptr<Engine> engine) : engine_(std::move(engine)) {}

   void start()
   {
      engine_->ignite();
   }

   void stop()
   {
      engine_->shutdown();
   }

   void accelerate()
   {
      engine_->increaseRPM();
   }
private:
   std::unique_ptr<Engine> engine_;
};



int main()
{
   Car gasCar(std::make_unique<GasEngine>());
   gasCar.start();
   gasCar.accelerate();
   gasCar.stop();

   Car electricCar(std::make_unique<ElectricEngine>());
   electricCar.start();
   electricCar.accelerate();
   electricCar.stop();

   return 0;
}
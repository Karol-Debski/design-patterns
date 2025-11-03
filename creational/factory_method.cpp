#include <iostream>
#include <memory>
#include <vector>

/*
Factory Method – central place to decide which concrete object to create, user only sees the interface.
It is mock-friendly and works best when the type of object depends on configuration or user choice.
For example:
- a display driver object, e.g. an I2C driver or an SPI driver,
- a coffee object, e.g. latte, cappuccino or black coffee.
*/

class Sensor
{
public:
   virtual ~Sensor() = default;
   virtual float read() const = 0;
};

class TemperatureSensor : public Sensor
{
public:
   float read() const override {
      std::cout<<"Read from temperature sensor\n";
      return 21.0f;
   }
};

class PressureSensor : public Sensor
{
public:
   float read() const override {
      std::cout<<"Read from pressure sensor\n";
      return 3.4f;
   }
};

enum class ESensor
{
   Temperature,
   Pressure,
};

class SensorFactory
{
public: 
   std::unique_ptr<Sensor> createSensor(const ESensor sensor) {
      switch(sensor)
      {
      case ESensor::Temperature:
         return std::make_unique<TemperatureSensor>(); 
      case ESensor::Pressure:
         return std::make_unique<PressureSensor>(); 
      default:
         return nullptr;
      }
   };
};

int main()
{
   SensorFactory factory{};

   std::vector<std::unique_ptr<Sensor>> sensors;

   sensors.push_back(factory.createSensor(ESensor::Temperature));
   sensors.push_back(factory.createSensor(ESensor::Pressure));

   for(auto& s : sensors)
   {
      s->read();
   }
}
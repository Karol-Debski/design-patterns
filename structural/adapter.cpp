#include <iostream>
#include <memory>

class OldTemperatureSensor
{
public:
   float getTempFahrenheit()
   {
      return 98.6f;
   };
};

class TemperatureSensor
{
public:
   virtual ~TemperatureSensor() = default;
   virtual float getTemperatureCelsius() = 0;
};

class TemperatureSensorAdapter : public TemperatureSensor
{
public:
   explicit TemperatureSensorAdapter(std::unique_ptr<OldTemperatureSensor> oldTemperatureSensor) 
      : oldTemperatureSensor_(std::move(oldTemperatureSensor)) {}; 

   float getTemperatureCelsius() override 
   {
      float tempFahrenheit = oldTemperatureSensor_->getTempFahrenheit();
      return (tempFahrenheit - 32) *5/(9.0f);
   }

private:
   std::unique_ptr<OldTemperatureSensor> oldTemperatureSensor_;
};


int main()
{
   auto oldTempSensor = std::make_unique<OldTemperatureSensor>();

   std::cout<<"OldSensor: Temperature in Fahrenheit: "<<oldTempSensor->getTempFahrenheit()<<'\n';
   
   auto tempSensor = std::make_unique<TemperatureSensorAdapter>(std::move(oldTempSensor));

   std::cout<<"Adapter:   Temperature in Celsius: "<<tempSensor->getTemperatureCelsius()<<'\n';
}
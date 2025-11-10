#include <iostream>
#include <string>
#include <memory>

/*
Abstract factory - a way to get interfaces of objects which belong to the same family. 
*/


class Cpu
{
public:
   virtual ~Cpu() = default;
   virtual std::string_view getName() const = 0;
   virtual unsigned int getClockSpeedMHz() const = 0;
};

class ARMCortexM : public Cpu
{
public:
   ARMCortexM(std::string name, unsigned int clockSpeedMHz) : name_(name), clockSpeedMHz_(clockSpeedMHz) {};
   ~ARMCortexM() = default;

   std::string_view getName() const override
   {
      return name_;
   };

   unsigned int getClockSpeedMHz() const override
   {
      return clockSpeedMHz_;
   };

private:
   std::string  name_;
   unsigned int clockSpeedMHz_;
};

class XtensaCpu : public Cpu
{
public:
   XtensaCpu(std::string name, unsigned int clockSpeedMHz) : name_(name), clockSpeedMHz_(clockSpeedMHz) {};
   ~XtensaCpu() = default;

   std::string_view getName() const override
   {
      return name_;
   };

   unsigned int getClockSpeedMHz() const override
   {
      return clockSpeedMHz_;
   };

private:
   std::string  name_;
   unsigned int clockSpeedMHz_;
};


class InterruptController
{
public:
   virtual ~InterruptController() = default;

   virtual void initialize() = 0;
};

class STM32_InterruptController : public InterruptController
{
public:
   STM32_InterruptController() {};
   ~STM32_InterruptController() = default;

   void initialize() override {
      std::cout<<"Initialization of STM32_InterruptController...\n";
   };
};

class ESP32_InterruptController : public InterruptController
{
public:
   ESP32_InterruptController() {};
   ~ESP32_InterruptController() = default;

   void initialize() override {
      std::cout<<"Initialization of ESP32_InterruptController...\n";
   };
};

class McuFactory
{
public:
   virtual ~McuFactory() = default;

   virtual std::unique_ptr<Cpu> createCpu(const std::string& name, unsigned int clockSpeedMHz) const = 0;

   virtual std::unique_ptr<InterruptController> createInterruptController() const = 0;
};

class STM32_McuFactory : public McuFactory
{
public:
   STM32_McuFactory()  = default;
   ~STM32_McuFactory() = default;

   [[nodiscard]] std::unique_ptr<Cpu> createCpu(const std::string& name, unsigned int clockSpeedMHz) const override
   {
      return std::make_unique<ARMCortexM>(name, clockSpeedMHz);
   };

   [[nodiscard]] std::unique_ptr<InterruptController> createInterruptController() const override
   {
      return std::make_unique<STM32_InterruptController>();
   };
};

class ESP32_McuFactory : public McuFactory
{
public:
   ESP32_McuFactory()  = default;
   ~ESP32_McuFactory() = default;

   [[nodiscard]] std::unique_ptr<Cpu> createCpu(const std::string& name, unsigned int clockSpeedMHz) const override
   {
      return std::make_unique<XtensaCpu>(name, clockSpeedMHz);
   };

   [[nodiscard]] std::unique_ptr<InterruptController> createInterruptController() const override
   {
      return std::make_unique<ESP32_InterruptController>();
   };
};



int main()
{
   std::unique_ptr<McuFactory> factory = std::make_unique<STM32_McuFactory>();
   
   std::unique_ptr<Cpu> cpu = factory->createCpu("CortexM4", 168);

   std::unique_ptr<InterruptController> interruptController = factory->createInterruptController();

   std::cout<<"[STM32] cpu name: "<<cpu->getName()<<", clock speed in MHz: "<<cpu->getClockSpeedMHz()<<'\n';
   interruptController->initialize();


   factory = std::make_unique<ESP32_McuFactory>();

   cpu = factory->createCpu("XtensaLX7", 240);

   interruptController = factory->createInterruptController();
   
   std::cout<<"[ESP32] cpu name: "<<cpu->getName()<<", clock speed in MHz: "<<cpu->getClockSpeedMHz()<<'\n';
   interruptController->initialize();
}
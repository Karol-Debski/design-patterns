#include <iostream>
#include <memory>
#include <optional>

class Visitor;

class BMS
{
public:
   BMS() = default;

   float getVoltage() {return 21.4f;}

   void accept(Visitor& visitor);
};

class TemperatureSensor
{
public:
   TemperatureSensor() = default;

   float getTemp() {return 20.3f;}

   void accept(Visitor& visitor);
};

class Barometer
{
public:
   Barometer() = default;

   float getPressure() {return 1025.2;}
   
   void accept(Visitor& visitor);
};

class Visitor
{
public:
   virtual ~Visitor() = default;

   virtual void visit(BMS& bms) = 0;
   virtual void visit(TemperatureSensor& tempSen) = 0;
   virtual void visit(Barometer& bm) = 0;
};

class TelemetryVisitor : public Visitor
{
public:
   TelemetryVisitor() = default;

   void visit(BMS& bms) override
   {
      bmsVoltage_ = bms.getVoltage();
   }

   void visit(TemperatureSensor& tempSen) override
   {
      temperature_ = tempSen.getTemp();
   }

   void visit(Barometer& bm) override
   {
      pressure_ = bm.getPressure();
   }

   bool isAllDataCollected() 
   {
      return bmsVoltage_.has_value() && temperature_.has_value() && pressure_.has_value();
   }

   void sendData()
   {
      std::cout<<"Sending collected data: voltage of BMS: "<<bmsVoltage_.value()<<
                 ", temperature: "<<temperature_.value()<<
                 ", pressure: "<<pressure_.value()<<".\n";
      
      bmsVoltage_.reset();
      temperature_.reset();
      pressure_.reset();
   }
private:
   std::optional<float> bmsVoltage_;
   std::optional<float> temperature_;
   std::optional<float> pressure_;
};


void BMS::accept(Visitor& visitor) /* double dispatch */
{
   visitor.visit(*this);
}

void TemperatureSensor::accept(Visitor& visitor) /* double dispatch */
{
   visitor.visit(*this);
}

void Barometer::accept(Visitor& visitor) /* double dispatch */
{
   visitor.visit(*this);
}


int main()
{
   std::shared_ptr<TelemetryVisitor> telemetry = std::make_shared<TelemetryVisitor>();
   
   BMS               bms;
   TemperatureSensor tempSen;
   Barometer         bm;
   
   std::cout<<"Adding bms data in progress...\n";
   bms.accept(*telemetry);

   std::cout<<"Is all data collected? "<<std::boolalpha<<telemetry->isAllDataCollected()<<'\n';


   std::cout<<"Adding temperature data in progress...\n";
   tempSen.accept(*telemetry);

   std::cout<<"Is all data collected? "<<std::boolalpha<<telemetry->isAllDataCollected()<<'\n';


   std::cout<<"Adding barometer data in progress...\n";
   bm.accept(*telemetry);

   std::cout<<"Is all data collected? "<<std::boolalpha<<telemetry->isAllDataCollected()<<'\n';


   telemetry->sendData();

   return 0;
}
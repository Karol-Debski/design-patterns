#include <iostream>
#include <memory>


class Car
{
public:
   virtual ~Car() = default;

   virtual void ride() = 0;
   virtual float getSpeed() const = 0;
   virtual std::unique_ptr<Car> clone() const = 0;
};

class Sedan : public Car
{
public:
   Sedan()  = default;
   ~Sedan() = default;
   
   Sedan(const Sedan& other) = default;

   void ride() override {
      speed_ = 50;
   }

   float getSpeed() const override {
      return speed_;
   }

   std::unique_ptr<Car> clone() const override {
      return std::make_unique<Sedan>(*this);
   }
private:
   float speed_ = 0;
};


int main()
{
   std::unique_ptr<Car> passat = std::make_unique<Sedan>();

   passat->ride();

   std::cout<<"Speed of passat: "<<passat->getSpeed()<<"\n";

   std::unique_ptr<Car> passatCloned = passat->clone();

   std::cout<<"Speed of cloned passat: "<<passatCloned->getSpeed()<<"\n";
}

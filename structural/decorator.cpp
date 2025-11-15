#include <iostream>
#include <memory>
#include <string>

/*
Decorator – a structural pattern that allows adding new functionalities
by wrapping an object inside special decorator objects.

In contrast to inheritance, which is static and changing the behavior
requires replacing the entire object, composition allows modifying behavior
by stacking objects dynamically on top of each other.
*/

class Coffee
{
public:
   Coffee() = default;
   virtual ~Coffee() = default;

   [[nodiscard]] virtual int getCost() const
   {
      return 10;
   };

   [[nodiscard]] virtual std::string getDescription() const
   {
      return "Coffee";
   };
};

class CoffeeDecorator : public Coffee
{
public:
   CoffeeDecorator(std::unique_ptr<Coffee> coffee) : coffee_(std::move(coffee)) {};
   ~CoffeeDecorator() = default;

   [[nodiscard]] int getCost() const override = 0;
   [[nodiscard]] std::string getDescription() const override = 0;

protected:
   const std::unique_ptr<Coffee> coffee_;
};

class MilkDecorator : public CoffeeDecorator
{
public:
   MilkDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {};
   ~MilkDecorator() = default;

   [[nodiscard]] int getCost() const override
   {
      return coffee_->getCost() + 2;
   }

   [[nodiscard]] std::string getDescription() const override
   {
      return coffee_->getDescription() + " + Milk";
   };
};

class HoneyDecorator : public CoffeeDecorator
{
public:
   HoneyDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {};
   ~HoneyDecorator() = default;

   [[nodiscard]] int getCost() const override
   {
      return coffee_->getCost() + 3;
   }

   [[nodiscard]] std::string getDescription() const override
   {
      return coffee_->getDescription() + " + Honey";
   };
};

class ChocolateDecorator : public CoffeeDecorator
{
public:
   ChocolateDecorator(std::unique_ptr<Coffee> coffee) : CoffeeDecorator(std::move(coffee)) {};
   ~ChocolateDecorator() = default;

   [[nodiscard]] int getCost() const override
   {
      return coffee_->getCost() + 5;
   }

   [[nodiscard]] std::string getDescription() const override
   {
      return coffee_->getDescription() + " + Chocolate";
   };
};


int main()
{
   auto coffee = std::make_unique<Coffee>();

   coffee = std::make_unique<MilkDecorator>(std::move(coffee));

   std::cout<<"Cost of \""<<coffee->getDescription()<<"\" is equal to "<<coffee->getCost()<<'\n';

   coffee = std::make_unique<HoneyDecorator>(std::move(coffee));

   std::cout<<"Cost of \""<<coffee->getDescription()<<"\" is equal to "<<coffee->getCost()<<'\n';

   coffee = std::make_unique<ChocolateDecorator>(std::move(coffee));

   std::cout<<"Cost of \""<<coffee->getDescription()<<"\" is equal to "<<coffee->getCost()<<'\n';
}
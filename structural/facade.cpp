#include <iostream>
#include <memory>


/*
Facade - simpler interface for complex system.
*/

class Kitchen
{
public:
   Kitchen() = default;
   ~Kitchen() = default;

   void prepareFood()
   {
      std::cout<<"Preparing food in progress...\n";
   }
   void callWaiter()
   {
      std::cout<<"Call waiter\n";
   }
   void washDishes()
   {
      std::cout<<"Washing dishes in progress...\n";
   }
};

class Waiter
{
public:
   Waiter() = default;
   ~Waiter() = default;

   void writeOrder()
   {
      std::cout<<"Write order\n";
   }
   void requestOrderInKitchen()
   {
      std::cout<<"Request order in kitchen\n";
   }
   void serveCustomer()
   {
      std::cout<<"Serve customer\n";
   }
};

class OrderFacade
{
public:
   OrderFacade(Waiter& waiter, Kitchen& kitchen) : waiter_(waiter), kitchen_(kitchen) {};
   ~OrderFacade() = default;

   void orderFood()
   {
      waiter_.writeOrder();
      waiter_.requestOrderInKitchen();
      kitchen_.prepareFood();
      kitchen_.callWaiter();
      waiter_.serveCustomer();
      kitchen_.washDishes();
   }

private:
   Waiter&  waiter_;
   Kitchen& kitchen_;
};


int main()
{
   Kitchen kitchen;
   Waiter  waiter;

   OrderFacade orderFacade(waiter, kitchen);

   orderFacade.orderFood();
}
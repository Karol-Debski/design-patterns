#include <iostream>
#include <memory>

/*
Chain of Responsibility - a chain of conencted handlers (objects) for an event. 
If a handler can't process an event, then the next one is invoked. A request 
enters from one end of the chain and is passed along until it finds a suitable handler.
*/

class Account
{
public:
   virtual ~Account() = default;

   Account(double balance) : balance_(balance) {} 

   std::shared_ptr<Account> setNext(std::shared_ptr<Account> account)
   {
      nextAccount_ = account;
      return account;
   }

   bool pay(double amountToPay)
   {  
      bool result = process(amountToPay);

      if(result)
      {
         return result;
      }
      
      if(nextAccount_ != nullptr)
      {
         return nextAccount_->pay(amountToPay);
      }

      return false;
   }

protected:
   virtual bool process(double amountToPay) = 0;
   
   double balance_;
   std::shared_ptr<Account> nextAccount_;
};


class BankAccount : public Account
{
public:
   BankAccount(double balance) : Account(balance) {}

protected:
   bool process(double amountToPay) override
   {
      if(amountToPay <= balance_)
      {
         std::cout<<"Pay handled from bank account\n";
         balance_ -= amountToPay;
         return true;
      }
      return false;
   }
};

class PayPalAccount : public Account
{
public:
   PayPalAccount(double balance) : Account(balance) {}

protected:
   bool process(double amountToPay) override
   {
      if(amountToPay <= balance_)
      {
         std::cout<<"Pay handled from paypal account\n";
         balance_ -= amountToPay;
         return true;
      }
      return false;
   }
};

class CryptoAccount : public Account
{
public:
   CryptoAccount(double balance) : Account(balance) {}

protected:
   bool process(double amountToPay) override
   {
      if(amountToPay <= balance_)
      {
         std::cout<<"Pay handled from crypto account\n";
         balance_ -= amountToPay;
         return true;
      }
      return false;
   }
};


int main()
{
   auto bankAccount   = std::make_shared<BankAccount>(200);
   auto payPalAccount = std::make_shared<PayPalAccount>(400);
   auto cryptoAccount = std::make_shared<CryptoAccount>(500);

   bankAccount->setNext(payPalAccount)->setNext(cryptoAccount);

   std::cout<<std::boolalpha<<"Is payment handled? "<<bankAccount->pay(300)<<'\n';

   std::cout<<std::boolalpha<<"Is payment handled? "<<bankAccount->pay(300)<<'\n';

   std::cout<<std::boolalpha<<"Is payment handled? "<<bankAccount->pay(400)<<'\n';

   return 0;
}
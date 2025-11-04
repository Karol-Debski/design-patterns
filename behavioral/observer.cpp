#include <iostream>
#include <vector>
#include <memory>


class IObserver;

class ISubject
{
public:
   virtual ~ISubject() = default;
   virtual void attach(const std::weak_ptr<IObserver>& observer) = 0;
   virtual void detach(const std::weak_ptr<IObserver>& observer) = 0;
   virtual void notify(const std::string& msg) = 0;
};

class IObserver
{
public:
   virtual ~IObserver() = default;
   virtual void update(const std::string& msg) = 0;
};

class Observer : public IObserver
{
public:
   Observer(const std::string& name) : name_(name) {};

   void update(const std::string& msg) {
      std::cout<<name_<<" got: \""<<msg<<"\" from subject!\n";
   }
private:
   std::string name_;
};


// Subject - keeps a list of observers and notifies them about updates.

class Subject : public ISubject
{
public:
   Subject() = default;
   
   void attach(const std::weak_ptr<IObserver>& observer) {
      for(auto it = observers_.begin(); it != observers_.end();)
      {
         if(auto strong = it->lock())
         {
            if(strong == observer.lock())
            {
               return;
            }
            ++it;
         }
         else
         {
            it = observers_.erase(it);
         }
      }
      observers_.push_back(observer);
   }

   void detach(const std::weak_ptr<IObserver>& observer) {
      for(auto it = observers_.begin(); it != observers_.end();)
      {
         if(auto strong = it->lock())
         {
            if(strong == observer.lock())
            {
               it = observers_.erase(it);
               continue;
            }
         }
         else
         {
            it = observers_.erase(it);
            continue;
         }

         ++it;
      }
   }

   void notify(const std::string& msg) {
      for(auto it = observers_.begin(); it != observers_.end();)
      {
         if(auto ob = it->lock())
         {
            ob->update(msg);
            ++it;
         }
         else
         {
            it = observers_.erase(it);
         }
      }
   }

private:
   std::vector<std::weak_ptr<IObserver>> observers_; 
};



int main()
{
   Subject subject;

   std::shared_ptr<Observer> observer1 = std::make_shared<Observer>("observer1");
   std::shared_ptr<Observer> observer2 = std::make_shared<Observer>("observer2");
   std::shared_ptr<Observer> observer3 = std::make_shared<Observer>("observer3");
   std::shared_ptr<Observer> observer4 = std::make_shared<Observer>("observer4");

   subject.attach(observer1);
   subject.attach(observer1);
   subject.attach(observer3);

   std::cout<<"--- Notify ---\n";

   subject.notify("msg 1");

   subject.detach(observer1);
   subject.detach(observer2);
   subject.detach(observer2);

   std::cout<<"--- Notify ---\n";

   subject.notify("msg 2");

   subject.attach(observer1);
   subject.attach(observer4);

   std::cout<<"--- Notify ---\n";

   subject.notify("msg 3");

   observer1.reset();
   observer3.reset();

   std::cout<<"--- Notify ---\n";

   subject.notify("msg 4");
}
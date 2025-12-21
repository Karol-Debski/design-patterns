#include <iostream>
#include <memory>

/*
Proxy - an intermediary object that controls access to another object, implementing the same interface
*/

class Database
{
public:
   virtual ~Database() = default;

   virtual void connect()    = 0;
   virtual void disconnect() = 0;
   virtual void execute(const std::string& query) = 0;
};

class RealDatabase : public Database
{
public:
   void connect() override
   {
      std::cout<<"Connect...\n";
   }

   void disconnect() override
   {
      std::cout<<"Disconnect...\n";
   }

   void execute(const std::string& query) override
   {
      if(query == "SELECT * FROM users")
      {
         std::cout<<"SELECT...\n";
      }
      else if (query == "DELETE FROM users")
      {
         std::cout<<"DELETE...\n";
      }
      else
      {
         std::cout<<"Bad query.\n";
      }
   }
};

class ProxyDatabase : public Database
{
public:
   ProxyDatabase() = default;

   ~ProxyDatabase()
   {
      if(realDB_)
         realDB_->disconnect();
   }

   void connect() override
   {
      if(!realDB_)
      {
         realDB_ = std::make_unique<RealDatabase>();
      }

      realDB_->connect();
   }

   void disconnect() override
   {
      if(!realDB_)
      {
         return;
      }

      realDB_->disconnect();
   }

   void execute(const std::string& query) override
   {
      if(!realDB_)
      {
         realDB_ = std::make_unique<RealDatabase>();
      }

      if(query == "DELETE FROM users")
      {
         std::cout << "Proxy: permission denied.\n";
      }
      else
      {
         realDB_->execute(query);
      }

      requestCnt++;
   }
private:
   std::unique_ptr<RealDatabase> realDB_;
   int requestCnt = 0;
};



int main()
{
   ProxyDatabase db;

   db.connect();
   db.execute("SELECT * FROM users");
   db.execute("DELETE FROM users");
   db.execute("DELETE FR");

   return 0;
}
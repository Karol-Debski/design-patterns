#include <iostream>

/*
Mediator - reduce chaotic dependencies between objects and forces them to collaborate only via a mediator object.
*/

class MediatorInterface;


class TrajectoryManagerInterface
{
public:
   virtual ~TrajectoryManagerInterface() = default;

   virtual void avoidObstacle(float x, float y, float z) = 0;
   virtual void landNow() = 0;
   virtual void landAsPractical() = 0;
};

class TrajectoryManager : public TrajectoryManagerInterface
{
public:
   void avoidObstacle(float x, float y, float z) override
   {
      std::cout<<"Calculate new path to avoid obstacle...\n";
   }

   void landAsPractical() override
   {
      std::cout<<"Calculate new path to land as practical...\n";
   }

   void landNow() override
   {
      std::cout<<"Calculate new path to land now...\n";
   }
};


class BMSInterface
{
public:
   virtual ~BMSInterface() = default;

   virtual void updateBatteryLevel(int batteryLevel) = 0;
};

class BMS : public BMSInterface
{
public:
   BMS() = default;

   void updateBatteryLevel(int batteryLevel) override;

   void setMediator(MediatorInterface* p_mediator);
private:
   MediatorInterface* p_mediator_ = nullptr;
};


class StereoCameraInterface
{
public:
   virtual ~StereoCameraInterface() = default;

   virtual void scanArea() = 0;
};

class StereoCamera : public StereoCameraInterface
{
public:
   StereoCamera() = default;

   void scanArea() override;

   void setMediator(MediatorInterface* p_mediator);
private:
   MediatorInterface* p_mediator_ = nullptr;
};


class MediatorInterface
{
public:
   virtual ~MediatorInterface() = default;
   virtual void notifyObstacleDetected(float x, float y, float z) = 0;
   virtual void notifyBatteryLow(int batteryLevel) = 0;
};

class DroneMediator : public MediatorInterface
{
public:
   DroneMediator(TrajectoryManagerInterface& tm) 
      : tm_(tm) {}

   void notifyObstacleDetected(float x, float y, float z) override 
   {
      tm_.avoidObstacle(x, y, z);
   }

   void notifyBatteryLow(int batteryLevel) override
   {
      if(batteryLevel >= 5 && batteryLevel < 15)
      {
         tm_.landAsPractical();
      }
      else if(batteryLevel < 5)
      {
         tm_.landNow();
      }
   };
private:
   TrajectoryManagerInterface& tm_;
};


void BMS::updateBatteryLevel(int batteryLevel)
{
   p_mediator_->notifyBatteryLow(batteryLevel);
}

void BMS::setMediator(MediatorInterface* p_mediator)
{
   p_mediator_ = p_mediator;
}

void StereoCamera::scanArea()
{
   p_mediator_->notifyObstacleDetected(2.4f, 1.5f, 23.f);
}

void StereoCamera::setMediator(MediatorInterface* p_mediator)
{
   p_mediator_ = p_mediator;
}



int main()
{
   BMS bms;
   StereoCamera camera;
   TrajectoryManager tm;

   DroneMediator drone(tm);

   bms.setMediator(&drone);
   camera.setMediator(&drone);

   bms.updateBatteryLevel(11);
   bms.updateBatteryLevel(2);

   camera.scanArea();

   return 0;
}
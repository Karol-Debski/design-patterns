#include <iostream>
#include <vector>
#include <memory>

struct Point
{
   Point(double x, double y) : x_(x), y_(y) {};

   double x_;
   double y_;
};

class RouteStrategy
{
public:
   virtual ~RouteStrategy() = default;
   virtual std::vector<Point> buildRoute(const Point& p) const = 0;
};

class WalkStrategy : public RouteStrategy
{
public:
   std::vector<Point> buildRoute(const Point& p) const override {
      std::cout<<"buildRoute for walk!\n";
      return std::vector<Point>{{34.2, 23.78}, {34.1, 12.99}, {67.1, 45.2}, p};
   };
};

class RoadStrategy : public RouteStrategy
{
public:
   std::vector<Point> buildRoute(const Point& p) const override {
      std::cout<<"buildRoute for road!\n";
      return std::vector<Point>{{14.2, 23.78}, {44.1, 12.99}, {77.1, 45.2}, p};
   };
};

class CycleStrategy : public RouteStrategy
{
public:
   std::vector<Point> buildRoute(const Point& p) const override {
      std::cout<<"buildRoute for cycle!\n";
      return std::vector<Point>{{7.2, 2.78}, {4.1, 12.99}, {55.1, 45.2}, p};
   };
};


class Navigator
{
public:
   Navigator(const std::shared_ptr<RouteStrategy>& strategy) : strategy_(strategy) {};
   ~Navigator() = default;

   void setStrategy(const std::shared_ptr<RouteStrategy>& strategy) {
      strategy_ = strategy;
   }

   std::vector<Point> buildRoute(const Point& p) {
      return strategy_->buildRoute(p);
   };
private:
   std::shared_ptr<RouteStrategy> strategy_;
};


int main()
{
   auto  walkStrategy  = std::make_shared<WalkStrategy>();
   auto  roadStrategy  = std::make_shared<RoadStrategy>();
   auto  cycleStrategy = std::make_shared<CycleStrategy>();

   Navigator navigator(walkStrategy);
   auto route = navigator.buildRoute(Point(4.12, 7.8));

   navigator.setStrategy(roadStrategy);
   route = navigator.buildRoute(Point(4.12, 7.8));

   navigator.setStrategy(cycleStrategy);
   route = navigator.buildRoute(Point(4.12, 7.8));
}
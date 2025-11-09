#include <iostream>
#include <memory>
#include <string>

enum class Handlebar
{
   Flat,
   Drop,
   BMX,
   Bullhorn
};

enum class ForkType
{
   Suspension,
   Rigid
};

enum class Material
{
   Titanium,
   Aluminum,
   Steel,
   Carbon
};

class Bicycle
{
public:
   void setName(const std::string& name) {
      name_ = name;
   };

   void setHandlebar(const Handlebar handlebar) {
      handlebar_ = handlebar;
   };

   void setFork(const ForkType forkType) {
      forkType_ = forkType;
   };

   void setFrameMaterial(const Material frameMaterial) {
      frameMaterial_ = frameMaterial;
   };

   void setForkMaterial(const Material forkMaterial) {
      forkMaterial_ = forkMaterial;
   };

   std::string getName() const {
      return name_;
   };

   Handlebar getHandlebar() const {
      return handlebar_;
   };

   ForkType getFork() const {
      return forkType_;
   };

   Material getFrameMaterial() const {
      return frameMaterial_;
   };

   Material getForkMaterial() const {
      return forkMaterial_;
   };

private:
   std::string name_          = "Unnamed";
   Handlebar   handlebar_     = Handlebar::Flat;
   ForkType    forkType_      = ForkType::Suspension;
   Material    frameMaterial_ = Material::Aluminum;
   Material    forkMaterial_  = Material::Aluminum;
};


class BicycleBuilder
{
public:
   BicycleBuilder() : bicycle_(std::make_unique<Bicycle>()) {};

   void reset() {
      bicycle_ = std::make_unique<Bicycle>();
   };

   BicycleBuilder& addName(const std::string& name) { 
      bicycle_->setName(name); 
      return *this;
   };
   
   BicycleBuilder& setHandlebar(const Handlebar handlebar) { 
      bicycle_->setHandlebar(handlebar); 
      return *this;
   };

   BicycleBuilder& setForkType(const ForkType forkType) { 
      bicycle_->setFork(forkType); 
      return *this;
   };

   BicycleBuilder& setFrameMaterial(const Material material) { 
      bicycle_->setFrameMaterial(material); 
      return *this;
   };

   BicycleBuilder& setForkMaterial(const Material material) { 
      bicycle_->setForkMaterial(material); 
      return *this;
   };

   std::unique_ptr<Bicycle> getResult() {
      auto bicycle = std::move(bicycle_);
      reset();
      return bicycle;
   };
private:
   std::unique_ptr<Bicycle> bicycle_;
};


int main()
{
   BicycleBuilder builder;

   auto gravel = builder.addName("Author").setHandlebar(Handlebar::Drop)
                                          .setForkMaterial(Material::Steel)
                                          .setFrameMaterial(Material::Steel)
                                          .setForkType(ForkType::Rigid)
                                          .getResult();
   
   std::cout<<gravel->getName()<<'\n'; 
}
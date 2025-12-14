#include <iostream>
#include <unordered_map>
#include <vector>

/*
The flyweight - a solution to saving memory by sharing similar objects. 
Usually, the objects state consists of modifiable and invariant data.
The pattern propose spliting theses data into separated classes. 
The class which stores invariant state, is called the flyweight class 
and it is sharable and immutable.
*/

struct TreeType
{
   std::string name;
   std::string texture;
};

struct TreeTypeHash
{
   std::size_t operator()(const std::pair<std::string, std::string>& treeType) const
   {
      return std::hash<std::string>{}(treeType.first) ^ std::hash<std::string>{}(treeType.second);
   }
};

class Tree
{
public:
   Tree(int x, int y, const TreeType& type)
      : x_(x), y_(y), type_(type) {}

   void draw() const 
   {
      std::cout<<"Started drawing tree "<<type_.name<<"...\n";
   }

private:
   int x_;
   int y_;
   const TreeType& type_;
};

class TreeFactory
{
public:
   using Key = std::pair<std::string, std::string>;
   
   static const TreeType& getTreeType(const std::string& name, const std::string& texture)
   {

      Key key{name, texture};
      
      if(treeTypes.find(key) == treeTypes.end())
      {
         treeTypes[key] = TreeType{name, texture};
      }

      return treeTypes.at(key);
   }

private:
   static inline std::unordered_map<Key, TreeType, TreeTypeHash> treeTypes;
};



int main()
{
   std::vector<Tree> forest;

   for(int i = 0; i < 10; ++i)
   {
      for(int j = 0; j < 10; ++j)
      {
         forest.emplace_back(i*10, j*10, TreeFactory::getTreeType("Oak", "oak.png"));
      }
   }

   for(int i = 0; i < 10; ++i)
   {
      for(int j = 0; j < 10; ++j)
      {
         forest.emplace_back(5 + i*15, 5 + j*15, TreeFactory::getTreeType("Pine", "pine.png"));
      }
   }

   for(const auto& tree : forest)
   {
      tree.draw();
   }


   return 0;
}
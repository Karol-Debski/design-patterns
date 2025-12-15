#include <iostream>
#include <vector>
#include <memory>

/*
Composite - defines a common interface for both leaf objects and composite objects, 
enabling recursive tree structures where clients do not need to distinguish between 
single objects and compositions.
*/

enum class FileSystemNodeType
{
   File = 0,
   Directory,
};

class FileSystemNode
{
public:
   virtual ~FileSystemNode() = default;

   virtual void               printInfo(int indent = 0, int id = 0) const = 0;
   virtual const std::string& getName() const = 0;
   virtual size_t             getSize() const = 0;
   virtual FileSystemNodeType getType() const = 0;
};

class File : public FileSystemNode /* Leaf */
{
public:
   File(const std::string& name, size_t size) : name_(name), size_(size) {}

   void printInfo(int indent = 0, int id = 0) const override
   {
      std::cout<<std::string(indent, ' ')<<id<<". "<<"Type: [File], name: ["<<name_<<"] size: ["<<size_<<"]\n";
   }

   const std::string& getName() const override
   {
      return name_;
   }

   size_t getSize() const override
   {
      return size_;
   }

   FileSystemNodeType getType() const override
   {
      return FileSystemNodeType::File;
   }
private:
   std::string        name_;
   size_t             size_;
};

class Directory : public FileSystemNode /* Composite */
{
public:
   Directory(const std::string& name) : name_(name) {}

   void add(std::unique_ptr<FileSystemNode> node)
   {
      children_.push_back(std::move(node));
   }

   std::unique_ptr<FileSystemNode> remove(const std::string& name)
   {
      std::unique_ptr<FileSystemNode> ptr = nullptr;

      for(auto it = children_.begin(); it != children_.end(); ++it)
      {
         if(name == (*it)->getName())
         {
            ptr = std::move(*it);
            children_.erase(it);

            return ptr;
         }
      }

      return ptr;
   }

   Directory* getSubDirectory(const std::string& name)
   {
      for(auto it = children_.begin(); it != children_.end(); ++it)
      {
         if((name == (*it)->getName()) && ((*it)->getType() == FileSystemNodeType::Directory))
         {
            return static_cast<Directory*>((*it).get());
         }
      }
      return nullptr;
   }

   void printInfo(int indent = 0, int id = 0) const override
   {
      id = (id == 0) ? id : 0;

      std::cout<<std::string(indent, ' ')<<"Type: [Directory], name: ["<<name_<<"] size: ["<<getSize()<<"]\n";

      for(const auto& child : children_)
      {
         child->printInfo(indent + 3, id);
         ++id;
      }
   }

   const std::string& getName() const override
   {
      return name_;
   }

   size_t getSize() const override
   {
      size_t size = 0;

      for(const auto& child : children_)
      {
         size += child->getSize();
      }

      return size;
   }

   FileSystemNodeType getType() const override
   {
      return FileSystemNodeType::Directory;
   }
private:
   std::string name_;

   std::vector<std::unique_ptr<FileSystemNode>> children_;
};



int main()
{
   auto root = std::make_unique<Directory>("root");

   root->add(std::make_unique<File>("File0", 100));
   root->add(std::make_unique<File>("File1", 200));

   auto home = std::make_unique<Directory>("home");

   home->add(std::make_unique<File>("File2", 512));
   home->add(std::make_unique<File>("File3", 256));

   auto music = std::make_unique<Directory>("music");

   music->add(std::make_unique<File>("disco_polo_mix.mp3", 2048));
   music->add(std::make_unique<File>("never_gonna_give_you_up.mp3", 16096));
   music->add(std::make_unique<File>("save_your_tears.mp3", 8096));


   home->add(std::move(music));
   root->add(std::move(home));

   std::cout<<"### Print whole file system tree\n";

   root->printInfo();

   std::cout<<"\nTotal size: "<<root->getSize()<<'\n';

   auto subDir = root->getSubDirectory("home");
   subDir = subDir->getSubDirectory("music");

   std::cout<<"\n### Print sub folder tree and remove file\n";

   if(subDir)
   {
      subDir->printInfo();
      subDir->remove("disco_polo_mix.mp3");
   }

   std::cout<<"\n### Print whole file system tree\n";

   root->printInfo();

   std::cout<<"\nTotal size: "<<root->getSize()<<'\n';

   return 0;
}
#include <iostream>
#include <memory>



template<typename T>
class ForwardList
{
private:
   class Node;

public:
   ForwardList() = default;
   ~ForwardList();

   class Iterator;

   void     pushFront(T data);
   void     popFront();
   bool     empty() const;
   Iterator begin() const;
   Iterator end() const;

   class Iterator
   {
   public:
      Iterator(Node* p_node) : p_node_(p_node) {}

      bool      operator!=(const Iterator& other) const;
      Iterator& operator++();
      T&        operator*() const;
   private:
      Node* p_node_;
   };

private:
   class Node
   {
   public:
      Node(T data, Node* next) : data_(data), p_next_(next) {}

      T     data_;
      Node* p_next_;
   };

   Node* head_ = nullptr;
};

template<typename T>
ForwardList<T>::~ForwardList<T>()
{
   while(!empty())
   {
      popFront();
   }
}

template<typename T>
bool ForwardList<T>::empty() const
{
   if(head_)
   {
      return false; 
   }
   return true;
}

template<typename T>
void ForwardList<T>::popFront()
{
   if(head_)
   {
      Node* p_next = head_->p_next_;
   
      delete head_;
   
      head_ = p_next;
   }
}

template<typename T>
void ForwardList<T>::pushFront(T data)
{
   head_ = new Node(data, head_);
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin() const
{
   return ForwardList<T>::Iterator(head_);
}

template<typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end() const
{
   return ForwardList<T>::Iterator(nullptr);
}

template<typename T>
bool ForwardList<T>::Iterator::operator!=(const ForwardList<T>::Iterator& other) const
{
   return p_node_ != other.p_node_; 
}

template<typename T>
typename ForwardList<T>::Iterator& ForwardList<T>::Iterator::operator++()
{
   p_node_ = p_node_->p_next_;
   return *this;
}

template<typename T>
T& ForwardList<T>::Iterator::operator*() const
{
   return p_node_->data_;
}


int main()
{
   ForwardList<int> l;
   l.pushFront(5);
   l.pushFront(15);
   l.pushFront(25);
   l.popFront();
   l.popFront();
   l.pushFront(35);
   l.pushFront(45);
   l.popFront();
   l.pushFront(55);
   l.pushFront(65);


   for(const auto& ele : l)
   {
      std::cout<<ele<<'\n';
   }

   return 0;
}
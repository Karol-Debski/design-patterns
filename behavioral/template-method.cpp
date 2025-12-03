#include <iostream>

/* 
The template method pattern - a customizable recipe of steps, where subclasses define the details.
*/

class Display
{
public:
   virtual ~Display() = default;

   void lockBuffer()
   {
      std::cout<<"Buffer locked.\n";
   }

   void clearBuffer()
   {
      std::cout<<"Buffer cleared.\n";
   }

   void updateBuffer()
   {
      std::cout<<"Updating buffer...\n";
   }

   virtual void sendData() = 0;

   virtual void finishStep() = 0;

   void unlockBuffer()
   {
      std::cout<<"Buffer unlocked.\n";
   }

   void refreshFrame()
   {
      lockBuffer();
      clearBuffer();
      updateBuffer();
      sendData();
      finishStep();
      unlockBuffer();
   }   

};

class OLED : public Display
{
public:
   void sendData()
   {
      std::cout<<"Send specific data for an OLED display.\n";
   }

   void finishStep()
   {
      /* do nothing */
   }
};

class ePaper : public Display
{
public:
   void sendData()
   {
      std::cout<<"Send specific data for the ePaper display.\n";
   }

   void finishStep()
   {
      std::cout<<"Perform full refresh of the ePaper display.\n";
   }
};


int main()
{
   std::cout<<"----OLED display----\n";

   OLED oledDisp;
   oledDisp.refreshFrame();

   std::cout<<"----ePaper display----\n";
   ePaper epaperDisp;
   epaperDisp.refreshFrame();

   return 0;
}
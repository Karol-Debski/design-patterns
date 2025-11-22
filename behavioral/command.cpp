#include <iostream>
#include <memory>
#include <vector>

/*
Command pattern - encapsulates a request as an object to  met DRY principle 
*/

class Command
{
public:
   virtual ~Command() = default;

   virtual bool execute() = 0;
   virtual void undo()    = 0;
};

struct Selection
{
   size_t pos;
   size_t len;
};


class Editor
{
public:
   std::string getSelectedText()
   {
      return content_.substr(selection_.pos, selection_.len);
   };

   void setSelection(Selection selection)
   {
      selection_ = selection;
   };

   Selection getSelection()
   {
      return selection_;
   };

   void insertText(size_t pos, const std::string& text)
   {
      content_.insert(pos, text);
   }

   void eraseText(Selection selection)
   {
      content_.erase(selection.pos, selection.len);
   }

   void appendText(const std::string& text)
   {
      content_.append(text);
   }

   std::string getContent()
   {
      return content_;
   }
private:
   std::string content_;
   Selection   selection_;
};


class Application
{
public:
   Application() : posOfLastExecuted_(-1) {};

   void executeCommand(std::unique_ptr<Command> command)
   {
      if(command->execute())
      {
         if(posOfLastExecuted_ != static_cast<int>(history_.size()-1))
         {
            history_.erase(history_.begin() + posOfLastExecuted_ + 1, history_.end());
         }
   
         history_.push_back(std::move(command));
   
         posOfLastExecuted_++;
      }
   }

   void undo()
   {
      if(posOfLastExecuted_ != -1)
      {  
         history_.at(posOfLastExecuted_)->undo();
         
         posOfLastExecuted_--;
      }
   }

   void redo()
   {
      if((history_.size() == 0) || (posOfLastExecuted_ + 1) != static_cast<int>(history_.size()))
      {  
         history_.at(posOfLastExecuted_ + 1)->execute();

         posOfLastExecuted_++;
      }
   }

   void setClipboard(const std::string& copy) 
   {
      clipboard_ = copy;
   }

   std::string getClipboard()
   {
      return clipboard_;
   }
private:
   std::vector<std::unique_ptr<Command>> history_;
   int posOfLastExecuted_;
   std::string clipboard_;
};


class CopyCommand : public Command
{
public:
   CopyCommand(Editor& editor, Application& application) 
      : editor_(editor), 
        application_(application) {};

   ~CopyCommand() = default;

   bool execute() override
   {
      application_.setClipboard(editor_.getSelectedText());

      return false;
   }

   void undo() override
   {
      /* no effect on the editor */
   }
private:
   Editor&      editor_;
   Application& application_;
};

class PasteCommand : public Command
{
public:
   PasteCommand(Editor& editor, Application& application) 
      : editor_(editor), 
        application_(application),
        clipboard_(application.getClipboard()),
        lastPos_(editor_.getContent().size()) {};
   
      ~PasteCommand() = default;

   bool execute() override
   {
      editor_.appendText(clipboard_);

      return true;
   }

   void undo() override
   {
      editor_.eraseText({lastPos_, clipboard_.size()});
   }
private:
   Editor&      editor_;
   Application& application_;
   std::string  clipboard_;
   size_t       lastPos_;
};

class CutCommand : public Command
{
public:
   CutCommand(Editor& editor, Application& application) 
      : editor_(editor), 
        application_(application),
        lastSelection_(editor.getSelection()),
        lastSelectedText_(editor.getSelectedText()) {};

   ~CutCommand() = default;

   bool execute() override
   {
      editor_.eraseText(lastSelection_);

      application_.setClipboard(lastSelectedText_);

      return true;
   }

   void undo()
   {
      editor_.insertText(lastSelection_.pos, lastSelectedText_);
   }
private:
   Editor&      editor_;
   Application& application_;
   Selection    lastSelection_;
   std::string  lastSelectedText_;
};


int main()
{
   Editor editor;
   Application app;

   editor.appendText("Ala ma kota");
   editor.setSelection({0, 3});

   app.executeCommand(std::make_unique<CopyCommand>(editor, app));
   app.executeCommand(std::make_unique<PasteCommand>(editor, app));
   app.executeCommand(std::make_unique<PasteCommand>(editor, app));

   std::cout<<"After 1 copy and 2 paste: "<<editor.getContent()<<'\n';

   for(int i = 0; i < 10; ++i)
   {
      app.undo();
   }

   for(int i = 0; i < 20; ++i)
   {
      app.redo();
   }

   std::cout<<"After all undo and redo commands: "<<editor.getContent()<<'\n';

   editor.setSelection({7, 4});

   app.executeCommand(std::make_unique<CutCommand>(editor, app));
   app.executeCommand(std::make_unique<PasteCommand>(editor, app));
   app.executeCommand(std::make_unique<PasteCommand>(editor, app));
   
   app.undo();
   app.undo();
   
   app.executeCommand(std::make_unique<PasteCommand>(editor, app));

   app.redo();
   app.redo();
   app.redo();

   std::cout<<"After 2 undo and 1 redo commands: "<<editor.getContent()<<'\n';

   for(int i = 0; i < 20; ++i)
   {
      app.undo();
   }

   std::cout<<"After all undo commands: "<<editor.getContent()<<'\n';
}
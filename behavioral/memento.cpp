#include <iostream>
#include <memory>
#include <string>

class Snapshot;

class Editor
{
public:

   std::unique_ptr<Snapshot> createSnapshot() const;

   void restore(std::unique_ptr<Snapshot> snapshot);

   void appendText(const std::string& text);

   std::string getContent() const;

private:
   std::string content_;
};

class Snapshot
{
public:
   explicit Snapshot(const Editor& editor) : snapshot_(editor) {}
private:
   Editor snapshot_;
   friend class Editor;
};

std::unique_ptr<Snapshot> Editor::createSnapshot() const
{
   return std::make_unique<Snapshot>(*this);
}

void Editor::restore(std::unique_ptr<Snapshot> snapshot)
{
   *this = (*snapshot).snapshot_;
}

void Editor::appendText(const std::string& text)
{
   content_ += text;
}

std::string Editor::getContent() const
{
   return content_;
}


int main()
{
   Editor editor;
   editor.appendText("Hello");

   auto snapshot = editor.createSnapshot();

   editor.appendText(" World!");

   editor.restore(std::move(snapshot));

   std::cout << "Content: " << editor.getContent() << '\n';

   return 0;
}

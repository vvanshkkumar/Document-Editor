#include<iostream>
#include<vector>
#include<fstream>


using namespace std;

class document {
    public :
    virtual string render()=0;
};

class setText : public document {
    public :
    string text;

    setText(string text){
        this->text=text;
    }

    string render() override {
        return text;
    }
};

class setImage : public document {
    public :
    string imagePath;

    setImage(string imagePath){
        this->imagePath=imagePath;
    }
    string render() override {
        return "[image : "+imagePath+"]";
    }
};

class setSpace : public document {
    public :
    

    string render() override{
       return "\t";
    }
};
class setNewline : public document{
    public :

    string render() override{
        return "\n";
    }
};

class setDocument {
    private :
    vector<document*>docs;
    
    public :
    void addElement(document* element){
        docs.push_back(element);
    }

   string render() {
     string result;

    for(auto doc : docs){
      result += doc->render();
    }
    return result;
   }

};

class persistance {
    public:
    virtual void save(string data)=0;
};

class fileStorage  : public persistance {
    public:

    void save(string data){
        ofstream outFile("document.txt");
        if(outFile){
            outFile << data;
            outFile.close();
            cout<<"document has been saved successfully"<<endl;
        }
        else {
            cout<<"error : unable to open file"<<endl;
        }
    }

};

class DocumentEditor {
    private :
     setDocument* doc;
     persistance* file;
     string renderedDocument;
     
     public :

     DocumentEditor(setDocument* doc,persistance* file){
        this->doc=doc;
        this->file=file;
     }

     void addText(string text) {
        doc->addElement(new setText(text));
     }
     void addimage(string image) {
        doc->addElement(new setImage(image));
     }
     void addSpace(){
        doc->addElement(new setSpace());
     }
     void addNewline(){
        doc->addElement(new setNewline());
     }

     string renderDocument(){
        if(renderedDocument.empty()){
            renderedDocument= doc->render();
        }
        return renderedDocument;
     }

     void saveDocument(){
        file->save(renderedDocument);
     }

};

int main () {

    setDocument* docum= new setDocument();
    fileStorage* fileSt = new fileStorage();

    DocumentEditor* editor = new DocumentEditor(docum,fileSt);

    editor->addText("hello");
    editor->addSpace();
    editor->addText("this is my first project");
    editor->addNewline();
    

    editor->renderDocument();

    editor->saveDocument();

    return 0;
}

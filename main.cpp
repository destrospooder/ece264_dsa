#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
using namespace std;

template <typename Type> class simpleList{
    private:
        struct Node{
            private:
                Type data;
                struct Node* next;
            Node(Type t){
                data = t;
                next = nullptr;
            }

            Type getData() const {
                return data;
            }

            void setData(Type data) {
                Node::data = data;
            }

            Node *getNext() const {
                return next;
            }

            void setNext(Node *next) {
                Node::next = next;
            }
        };
    protected:
        struct Node* first;
        struct Node* last;
        int size;
    public:
        simpleList(){
            first = nullptr;
            last = nullptr;
            size = 0;
        }
        int getSize() const {
            return size;
        }
        bool isEmpty(){
            return size == 0;
        }
        virtual void push(Type t) = 0;
        virtual Type pop() = 0;

        // cap = attaching the node at the front
        void cap(Type t){
            Node* index = new Node(t);
            if(isEmpty()){
                first = last = index;
                size = size + 1;
            }
            else{
                index -> setNext(first);
                first = index;
                size = size + 1;
            }
        }

        // cup = attaching the node at the back
        void cup(Type t){
            Node* index = new Node(t);
            if(isEmpty()){
                last = first = index;
                size = size + 1;
            }
            else{
                last -> setNext(index);
                last = index;
                size = size + 1;
            }
        }

        // pour = removing the node from the front
        Type pour(){
            if(isEmpty()){
                cout << "it brokey :(\n";
                return 420;
            }
            Type hopper = first -> getValue();
            if(size == 1) {
                size = size - 1;
                first = last = nullptr;
                return hopper;
            }
            else{
                first = first -> getNext();
                size = size - 1;
                return hopper;
            }
        }
};

// Implemented Stack and Queue using Cap, Cup, and Pour!

template <typename Type> class stack:public simpleList<Type>{
    public:
        void push(Type t){
            this -> cap(t);
        }
        Type pop(){
            return this -> pour();
        }
};

template <typename Type> class queue:public simpleList<Type>{
    public:
        void push(Type t){
            this -> cup(t);
        }
        Type pop(){
            return this -> pour();
        }
};

vector<string> tokenizer(string s){
    vector<string> divide;
    stringstream stream(s);
    string reader;
    while(stream >> reader) {
        divide.push_back(reader);
        cout << reader << "\n";
    }
    return divide;
}

//Basic file reader
//Opens input, creates output, prints and stores strings
void billy() {
    list < simpleList<int> *> intList;
    list < simpleList<double> *> doubleList;
    list < simpleList<string> *> stringList;
    vector<string> tokens;
    string primero;
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("output.txt");
    string stored;
    while (getline(input, stored)) {
        tokens = tokenizer(stored);
        primero = tokens[0];
        cout << stored << "\n";
        output << stored << "\n";
        if(primero == "create"){

        }
    }
    input.close();
    output.close();
}

int main(){
    return 0;
}

//Make a loop that reads each line of the file, then breaks each line into its components
//1: "push" "pop" "create"
//2: Name
//3: push/pop: whatever you're pushing && create: "stack" "queue"

//Need to make a file writer
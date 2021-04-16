#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <map>
using namespace std;

template <typename Type> class simpleList{
    private:
        struct Node{
            private:
                Type data;
                struct Node* next;
            public:
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
        string name;

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

        const string &getName() const {
            return name;
        }

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
                cout << "ERROR: This list is empty!\n";
                return 0;
            }
            Type hopper = first -> getData();
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

void tokenizer(string box[], ifstream& input){
    input >> box[0];
    if(box[0] == "pop"){
        input >> box[1];
    }
    else{
        input >> box[1];
        input >> box[2];
    }
}

//Basic file reader
//Opens input, creates output, prints and stores strings


//template<typename Type> simpleList <Type> listFind(string label, list<simpleList<Type>*> labels){
//    for(typename list<simpleList<Type>*> :: iterator it = labels.begin(); it != labels.end(); it++){
//        if(it.getName() == label) {
//            return it;
//        }
//    }
//}

bool duplicateFind(string label, list<string> labels){
    for(string &listlabel : labels){
        if (listlabel == label){
            return true;
        }
    }
    return false;
}

void billy() {
    map <string, simpleList<int> *> intList;
    map <string, simpleList<double> *> doubleList;
    map <string, simpleList<string> *> stringList;
    vector<string> tokens;
    ifstream input;
    ofstream output;
    list<string> labelList;
    input.open("input.txt");
    output.open("output.txt");
    string box[3];
    string bob;
    while (input.peek() != EOF) {
        tokenizer(box, input);
        output << "PROCESSING COMMAND: " << box[0]<<" "<<box[1]<<" "<<box[2]<<"\n";
        cout << box[0] << box[1] << box[2] << "\n";
        if (box[0] == "create"){
            if (duplicateFind(box[1], labelList)){
                output << "ERROR: This name already exists!\n";
                continue;
            }
            labelList.push_front(box[1]);
            if (box[2] == "stack"){
                if (box[1].substr(0,1) == "i") {
                    intList.insert(std::pair<string,simpleList<int>*>(box[1],new stack<int>()));
                }
                if (box[1].substr(0,1) == "d") {
                    doubleList.insert(std::pair<string,simpleList<double>*>(box[1],new stack<double>()));
                }
                if (box[1].substr(0,1) == "s") {
                    stringList.insert(std::pair<string,simpleList<string>*>(box[1],new stack<string>()));
                }
            }
            if (box[2] == "queue"){
                if (box[1].substr(0,1) == "i") {
                    intList.insert(std::pair<string,simpleList<int>*>(box[1],new queue<int>()));
                }
                if (box[1].substr(0,1) == "d") {
                    doubleList.insert(std::pair<string,simpleList<double>*>(box[1],new queue<double>()));
                }
                if (box[1].substr(0,1) == "s") {
                    stringList.insert(std::pair<string,simpleList<string>*>(box[1],new queue<string>()));
                }
            }
        }
        if (box[0] == "push"){
            if (!duplicateFind(box[1], labelList)){
                output << "ERROR: This name already exists!\n";
                continue;
            }
            if (box[1].substr(0,1) == "i"){
                intList[box[1]] -> push(stoi(box[2]));
                continue;
            }
            if (box[1].substr(0,1) == "d"){
                doubleList[box[1]] -> push(stod(box[2]));
                continue;
            }
            if (box[1].substr(0,1) == "s"){
                stringList[box[1]] -> push(box[2]);
                continue;
            }
        }
        if (box[0] == "pop"){
            if (!duplicateFind(box[1], labelList)) {
                output << "ERROR: This name already exists!\n";
                continue;
            }
            if (box[1].substr(0,1) == "i"){
                if(intList[box[1]] -> isEmpty()){
                    output << "ERROR: This list is empty!\n";
                    continue;
                }
                output << "Value popped: " << intList[box[1]] -> pop() << "\n";
                continue;
            }
            if (box[1].substr(0,1) == "d"){
                if(doubleList[box[1]] -> isEmpty()){
                    output << "ERROR: This list is empty!\n";
                    continue;
                }
                output << "Value popped: " << doubleList[box[1]] -> pop() << "\n";
                continue;
            }
            if (box[1].substr(0,1) == "s"){
                if(stringList[box[1]] -> isEmpty()){
                    output << "ERROR: This list is empty!\n";
                    continue;
                }
                output << "Value popped: " << stringList[box[1]] -> pop() << "\n";
                continue;
            }
        }
    }
    input.close();
    output.close();
}

//Read in one word at a time. If doing create or push, read in two more words; if doing pull, read in one.
//Create some function that does the create/pop/push stuff using two arguments each

int main(){
    billy();
    return 0;
}

//Make a loop that reads each line of the file, then breaks each line into its components
//1: "push" "pop" "create"
//2: Name
//3: push/pop: whatever you're pushing && create: "stack" "queue"

//Need to make a file writer
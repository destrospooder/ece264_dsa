//ECE264 - Data Structures and Algorithms I
//Benjamin Aziel
//Due April 27, 2021
//Prof. Carl Sable

//This program manipulates a manual implementation of stacks and
//queues. It goes through an input file with various commands (push,
//pop, create), executes the commands, and outputs a file.

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>

using namespace std;

//Initializing simpleList for Stack and Queue classes

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
        bool isEmpty(){
            return size == 0;
        }
        virtual void push(Type t) = 0;
        virtual Type pop() = 0;

        //cap = Attaching the node at the front

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

        //cup = Attaching the node at the back

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

        //pour = Removing the node from the front

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

//Implemented Stack and Queue classes using cap, cup, and pour

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

//Function that converts (tokenizes) input into string arrays
//Clears the box before each iteration to mitigate unwanted outputs when prompted with newline

void tokenizer(string box[], ifstream& input){
    box[0] = "";
    box[1] = "";
    box[2] = "";

    input >> box[0];
    if(box[0] == "pop"){
        input >> box[1];
    }
    else{
        input >> box[1];
        input >> box[2];
    }
}

//Boolean function that searches for duplicate names and absence thereof, used in billy()

bool duplicateFind(string label, list<string> labels){
    for(string &listlabel : labels){
        if (listlabel == label){
            return true;
        }
    }
    return false;
}

//Basic file reader
//Opens input, creates output, prints and stores strings
//Loop reads each line of the file, then breaks each line into its components

//1: "push" "pop" "create"
//2: Name
//3: push/pop: whatever you're pushing && create: "stack" "queue"

//Reads in one word at a time. If doing create or push, reads in two more
//words; if doing pull, reads in one

void billy() {
    map <string, simpleList<int> *> intList;
    map <string, simpleList<double> *> doubleList;
    map <string, simpleList<string> *> stringList;
    vector<string> tokens;

    ifstream input;
    ofstream output;
    list<string> labelList;

    //Prompts user to provide names for input/output files

    string inName, outName;
    cout << "Enter name of input file: ";
    getline(cin, inName);
    cout << "Enter name of output file: ";
    getline(cin, outName);
    input.open(inName);
    output.open(outName);

    string box[3];
    while (input.peek() != EOF) {
        tokenizer(box, input);

        if(box[0].empty()){
            continue;
        }

        //pop only outputs box[0] and box[1], push and create also output box[2]

        if (box[0] == "pop"){
            output << "PROCESSING COMMAND: " << box[0]<<" "<<box[1]<<"\n";
        }
        else{
            output << "PROCESSING COMMAND: " << box[0]<<" "<<box[1]<<" "<<box[2]<<"\n";
        }

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
                output << "ERROR: This name does not exist!\n";
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
                output << "ERROR: This name does not exist!\n";
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

int main(){
    billy();
    return 0;
}

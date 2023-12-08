// Luisa Rosa
// Due December 14th, 2023
// Semester Project :
// design and implement a push-down automata which can recognize the context-free language
// L = {a^n * b^n | n ≥ 0}

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

char Delta(string& unreadInput, string& state, stack<char>& stack, string& rule);

int main() {
    //declaring variables
    string input, unreadInput, rule, state = "p";
    stack<char> stack, stackCopy;
    int step = 0, stackSize;
    char delta = '-';
    bool lookAhead = true;

    cout << "Theory of Computation - Final Project - Luisa Rosa" << endl;
    cout << "\n" << endl;
    //get string from user
    cout << "Please input a string: ";
    cin >> input;
    cout << "\n" << endl;

    //each output follows the format we did in the class.
    cout << "  Step  |  State  |      Unread Input      |        Stack        |  Delta Used  |  Rule Used  " << endl;

    stack.push('e');  // Initialize the stack with 'e' as per DPA conventions
    unreadInput = input; // Initialize unreadInput with the input

    //scan the string left to right
    //for each character from the input, check the Delta that applies
    while (lookAhead == true) {        
        stackCopy = stack;
        stackSize = stackCopy.size();

        //print out current step
        cout << setw(5) << step << setw(4) << "|" << setw(5) << state << setw(5) << "|" << setw(24) << unreadInput << "|" << setw(10);
        for(::stack<char> stackCopy = stack; !stackCopy.empty(); stackCopy.pop()){
            cout << stackCopy.top();
        }
        cout << setw(13 - stackSize) << "|" << setw(7) << delta << setw(8)<< "|" << setw(5) << rule << endl;

        //check if string was accepted by the PDA
        if (unreadInput[0] == 'e' && stack.top() == 'e'){
            cout << "\n The string " << input << " used as input is accepted by this PDA.\n" << endl;
            lookAhead = false;
        }

        step++;
        rule = " "; 

        //determine Deltas for the DPA
        delta = Delta(unreadInput, state, stack, rule);

        //check if stack is empty, if so, push 'e'
        if (stack.empty() == true){
            stack.push('e');
        }

        //check if string follows the DPA
        if (delta == -1){
            cout << "Error!" << endl;
            break;
        }
    }
    return 0;
}

// function Delta that checks for the current state, character, and top of stack
// and determines what Delta should be applied to that step
char Delta(string& unreadInput, string& state, stack<char>& stack, string& rule){
    char currChar = unreadInput[0];
    char topOfStack = stack.top();
    //Delta 1:
    if(state == "p"){
        state = "q";
        stack.top() = 'S';
        return '1';
    }
    //Delta 2:
    else if((state == "q") && (currChar == 'a')){
        state = "qa";
        unreadInput = unreadInput.substr(1);
        return '2';
    }
    //Delta 3:
    else if((state == "qa") && (topOfStack == 'a')){
        state = "q";
        stack.pop();
        return '3';
    }
    //Delta 4:
    else if((state == "q") && (currChar == 'b')){
        state = "qb";
        unreadInput = unreadInput.substr(1);
        return '4';
    }
    //Delta 5:
    else if((state == "qb") && (topOfStack == 'b')){
        state = "q";
        stack.pop();
        return '5';
    }
    //Delta 6:
    else if((state == "q") && (currChar == '$')){
        state = "q$";
        stack.pop();
        unreadInput = 'e';
        return '6';
    }
    //Delta 7:
    else if((state == "qa") && (topOfStack == 'S')){
        stack.pop();
        stack.push('b');
        stack.push('S');
        stack.push('a');
        rule = "S --> aSb";
        return '7';
    }
    //Delta 8:
    else if((state == "qb") && (topOfStack == 'S')){
        stack.pop();
        rule = "S --> e";
        return '8';
    } 
    //End of DPA
    else if((state == "q$") && (topOfStack == 'e')){
        return '0';
    }
    return -1;
}
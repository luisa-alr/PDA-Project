// Luisa Rosa
// Due December 14th, 2023
// Semester Project :
// design and implement a push-down automata which can recognize the context-free language
// L = {a^n * b^n | n ≥ 0}


#include <iostream>
#include <string>
#include <stack>
using namespace std;

// function Rule that checks for the current state, character, and top of stack
// and determines what rule should be applied to that step
int Rule(string& unreadInput, string& state, stack<char>& stack){
    char currChar = unreadInput[0];
    char topOfStack = stack.top();
    //Rule 1:
    if((state == "q0") && (currChar == 'a') && (topOfStack == 'a')){
        state = "q0";
        unreadInput = unreadInput.substr(1);
        stack.push('Z');
        stack.push('a');
        return 1;
    }
    //Rule 2:
    else if((state == "q0") && (currChar == 'a') && (topOfStack == 'a')){
        state = "q0";
        unreadInput = unreadInput.substr(1);
        stack.push('a');
        stack.push('a');
        return 2;
    }
    //Rule 3:
    else if((state == "q0") && (currChar == 'b') && (topOfStack == 'a')){
        state = "q1";
        unreadInput = unreadInput.substr(1);
        stack.pop();
        return 3;
    }
    //Rule 4:
    else if((state == "q1") && (currChar == 'b') && (topOfStack == 'a')){
        state = "q1";
        unreadInput = unreadInput.substr(1);
        stack.pop();
        return 4;
    }
    //Rule 5:
    else if((state == "q0") && (currChar == '$') && (topOfStack == 'Z')){
        state = "qf";
        return 5;
    }
    return -1;
}

int main() {
    string input, state = "q0";
    stack<char> stack;
    int step = 0, rule;

    cout << "Theory of Computation - Final Project - Luisa Rosa" << endl;
    //get string from user
    cout << "Please input a string: ";
    cin >> input;
    cout << "\n" << endl;

    string unreadInput;

    //each output follows the format we did in the class.
    cout << "  Step  |  State  |  UnreadInput  |  Stack  |  RuleUsed  " << endl;

    stack.push('Z');  // Initialize the stack with 'Z' as per PDA conventions

    //scan the string left to right
    //for each character from the input, check the rule that applies
    for(int i = 0; i < input.size(); i++){
        //determine rules for the PDA
        rule = Rule(unreadInput, state, stack);
        cout << " " << step << " | " << state << " | " << unreadInput << " | ";
        for(int j = 0; j < stack.size(); j++){
            cout << stack.top(); // Print the top element of the stack
            stack.pop(); // Remove the top element
        }
        cout << " | " << rule << endl;
        step++;
    }


    return 0;
}
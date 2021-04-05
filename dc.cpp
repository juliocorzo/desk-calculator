#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include "stack.h"

using namespace std;

void printTop(const Stack<double> &stack);
void printAndPopTop(Stack<double>& stack);
void printAll(Stack<double> stack);
void makeEmpty(Stack<double>& stack);
void duplicateTop(Stack<double>& stack, int& total);
void swapTop(Stack<double>& stack);
void help();
string yellowText(const string &message);
void getInput(string& input);
void populateStack(Stack<double>& stack, string input, int& stackSize);
void operate(Stack<double>& stack, char character);
bool isOperator(char character);
bool isCommand(char character);
bool isAnythingElse(char character);
void checkSize(Stack<double>& stack, int& stackSize);
void err(char errorType, const string &message);
string redText(const string &message);


int main() {
    Stack<double> s;
    string i;
    int t = 10;
    while(true) {
        getInput(i);
        populateStack(s, i, t);
    }
}

/**
 * Allows the user to input numbers and commands into the program.
 *
 * @param input of the user as a string
 */
void getInput(string& input) {
    cout << "\033[0;32m"; getline(cin, input); cout << "\033[0m";
}

/**
 * Checks if the passed stack has reached its maximum size and if it has, it doubles it.
 *
 * @param stack whose size is being checked
 * @param stackSize the size of the stack being checked
 */
void checkSize(Stack<double>&stack, int& stackSize) {
    try {
        if(stack.isFull()) throw Overflow(1);
    }
    catch(Overflow& e) {
        if(stackSize == 10) {
            err(e.type, e.explanation);
        }
        double tempValues[stackSize];
        Stack<double> tempStack(stackSize * 2);
        int pos = 0;
        while(pos < stackSize) {
            tempValues[pos] = stack.topAndPop();
            pos++;
        }
        while(pos > 0) {
            tempStack.push(tempValues[pos - 1]);
            pos--;
        }
        stack = tempStack;
        stackSize *= 2;
    }
}

/**
 * Prints the top value of the passed stack.
 *
 * @param stack whose top value is being printed
 */
void printTop(const Stack<double> &stack) {
    try {
        if(stack.isEmpty()) throw Underflow(1);
        cout << stack.top() << endl;
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

/**
 * Removes and prints the top value from the stack being passed.
 *
 * @param stack whose top value is being removed and printed
 */
void printAndPopTop(Stack<double>& stack) {
    try {
        if(stack.isEmpty()) {
            throw Underflow(2);
        }
        cout << stack.top() << " ";
        stack.pop();
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

/**
 * Prints all the values contained inside the passed stack.
 *
 * @param stack whose values are being printed
 */
void printAll(Stack<double> stack) {
    try {
        if(stack.isEmpty()) throw Underflow(3);
        cout << stack.topAndPop() << endl;
        while(!stack.isEmpty()) {
            cout << stack.topAndPop() << endl;
        }
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

/**
 * Sets the current stack to an empty one.
 *
 * @param stack that is being cleared
 */
void makeEmpty(Stack<double>& stack) {
    try {
        if(stack.isEmpty()) throw Underflow(4);
        Stack<double> tempStack;
        stack = tempStack;
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

/**
 * Duplicates the top number in a stack.
 *
 * @param stack whose top is being pushed again
 * @param stackSize the current size of the stack
 */
void duplicateTop(Stack<double>& stack, int& stackSize) {
    try {
        if(stack.isEmpty()) throw Underflow(5);
        checkSize(stack, stackSize);
        stack.push(stack.top());
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

/**
 * Swaps the top number and the one preceeding it from stack.
 *
 * @param stack whose top two numbers are being swapped
 */
void swapTop(Stack<double>& stack) {
    double tempA = 0, a = 0, b = 0;
    bool aValid = true;
    bool bValid = true;
    try {
        if(stack.isEmpty()) throw Underflow(6);
        tempA = stack.top();
        a = stack.topAndPop();
    }
    catch(Underflow& e) {
        aValid = false;
        err(e.type, e.explanation);
    }
    try {
        if(aValid) {
            if(stack.isEmpty()) throw Underflow(7);
            b = stack.topAndPop();
        }
    }
    catch(Underflow& e) {
        bValid = false;
        err(e.type, e.explanation);
    }
    if(aValid && bValid) {
        stack.push(a);
        stack.push(b);
    }
    if(aValid && !bValid) {
        stack.push(tempA);
    }
}

/**
 * Prints a list of available commands and a small description of each to the command
 * line to aid the user while they are using the calculator.
 */
void help() {
    cout << "\nThe available commands are: \n";
    cout << yellowText("p") << "\t Returns the top of the stack." << endl;
    cout << yellowText("n") << "\t Prints the top of the stack then pops it." << endl;
    cout << yellowText("f") << "\t Prints the stack." << endl;
    cout << yellowText("c") << "\t Clears the stack." << endl;
    cout << yellowText("d") << "\t Pushes the top of the stack unto the stack" << endl;
    cout << yellowText("r") << "\t Swaps the two numbers at the top of the stack." << endl;
    cout << yellowText("h") << "\t Prints a list of possible commands." << endl;
    cout << yellowText("e") << "\t Quits the program \n" << endl;
}

/**
 * Operates on the top two numbers of the stack based on the passed operator and pushes
 * the result to the stack.
 *
 * @param stack where the numbers being operated on are stored
 * @param character that represents the mathematical operator
 */
void operate(Stack<double>& stack, char character) {
    double tempA = 0, tempB = 0, a = 0, b = 0, c = 0;
    bool aValid = true;
    bool bValid = true;
    bool valid = true;
    try {
        if(stack.isEmpty()) throw Underflow(8);
        tempA = stack.top();
        a = stack.topAndPop();
    }
    catch(Underflow& e) {
        aValid = false;
        err(e.type, e.explanation);
    }
    try {
        if(aValid) {
            if(stack.isEmpty()) throw Underflow(9);
            tempB = stack.top();
            b = stack.topAndPop();
        }
    }
    catch(Underflow& e) {
        bValid = false;
        err(e.type, e.explanation);
    }
    switch(character) {
        case '+': c = a + b; break;
        case '-': c = b - a; break;
        case '*': c = a * b; break;
        case '/':
            try {
                if(a == 0) throw DivisionByZero(1);
                else {
                    c = b / a; break;
                }
            }
            catch(DivisionByZero& e) {
                valid = false;
                err(e.type, e.explanation);
                break;
            }
        case '%':
            try {
                if(a == 0) throw DivisionByZero(2);
                else {
                    c = fmod(b, a); break;
                }
            }
            catch(DivisionByZero& e) {
                valid = false;
                err(e.type, e.explanation);
                break;
            }
        default: break;
    }
    if(aValid && bValid && valid) {
        stack.push(c);
    }
    if(!bValid) {
        stack.push(tempA);
    }
    if(aValid && bValid && !valid) {
        stack.push(tempB);
        stack.push(tempA);
    }
}

/**
 * Populates the stack with the user input.
 *
 * @param stack that is being populated
 * @param input that the user has provided
 * @param stackSize size of the stack being populated
 */
void populateStack(Stack<double>& stack, string input, int& stackSize) {
    int pos = 0;

    // While we have not reached the end of the string...
    while(input[pos] != '\0') {

        // If character is a space, go to next character.
        if(input[pos] == ' ') {
            pos++;
        }

        // If character is a '.', double starting with '.' has been found.
        if(input[pos] == '.') {
            bool valid = true;
            string t;
            t.append(string(1, input[pos]));
            pos++;
            while(input[pos] == '.') {
                pos++;
            }
            try {
                if(!isdigit(input[pos])) throw DataError(4);
            }
            catch(DataError& e) {
                valid = false;
                err(e.type, e.explanation);
                pos++;
            }
            while(isdigit(input[pos]) && valid) {
                t.append(string(1, input[pos]));
                pos++;
            }
            if(valid) {
                checkSize(stack, stackSize);
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end);
                stack.push(td);
            }
        }

        // If character is a digit, double has been found.
        if(isdigit(input[pos])) {
            bool point = false;
            bool valid = true;
            string t;
            while((isdigit(input[pos]) || input[pos] == '.') && !point) {
                if(input[pos] == '.') {
                    point = true;
                }
                t.append(string(1, input[pos]));
                pos++;
            }
            while(input[pos] == '.') {
                pos++;
            }
            if(point) {
                try {
                    if(!isdigit(input[pos])) throw DataError(4);
                }
                catch(DataError& e) {
                    valid = false;
                    err(e.type, e.explanation);
                    pos++;
                }
            }
            while(isdigit(input[pos]) && valid) {
                t.append(string(1, input[pos]));
                pos++;
            }
            if(valid) {
                checkSize(stack, stackSize);
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end);
                stack.push(td);
            }
        }

        // If character is '_', negative double has been found.
        if(input[pos] == '_') {
            bool valid = true;
            bool point = false;
            string t;
            pos++;
            while(input[pos] == '_' || input[pos] == '.') {
                if(input[pos] == '.' && !point) {
                    t.append(string(1, input[pos]));
                    point = true;
                }
                pos++;
            }
            if(point) {
                try {
                    if(!isdigit(input[pos])) throw DataError(1);
                }
                catch(DataError& e) {
                    valid = false;
                    err(e.type, e.explanation);
                }
            }
            while((isdigit(input[pos]) || input[pos] == '.') && !point) {
                if(input[pos] == '.') point = true;
                t.append(string(1, input[pos]));
                pos++;
            }
            while(isdigit(input[pos])) {
                t.append(string(1, input[pos]));
                pos++;
            }
            if(valid) {
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end) * -1.0;
                if(td == -0) td*=-1;
                stack.push(td);
            }
        }

        // If character is an operator, operate then move to next character.
        if(isOperator(input[pos])) {
            operate(stack, input[pos]);
            pos++;
        }

        // If character is a command, call specific command then move to next character.
        if(isCommand(input[pos])) {
            switch(input[pos]) {
                case 'p': printTop(stack); break;
                case 'n': printAndPopTop(stack); break;
                case 'f': printAll(stack); break;
                case 'c': makeEmpty(stack); stackSize = 10; break;
                case 'd': duplicateTop(stack, stackSize); break;
                case 'r': swapTop(stack); break;
                case 'h': help(); break;
                case 'e': exit(0);
                case 'w': cout << "\033[2J\033[1;1H"; break;
                default: break;
            }
            pos++;
        }
        try {
            // If character is anything else, erroneous character has been found. Throw error.
            if(isAnythingElse(input[pos])) throw DataError(2);
        }
        catch(DataError& e) {
            err(e.type, e.explanation);
            pos++;
        }
    }
}

/**
 * Returns true if the passed character is a math operator recognized by the application.
 *
 * @param o the character being tested.
 * @return true if character is an operator, false otherwise.
 */
bool isOperator(char o) {
    return o == '+' || o == '-' || o == '*' || o == '/' || o == '%';
}

/**
 * Returns true if the passed character is a command recognized by the application.
 *
 * @param c character being tested.
 * @return true if character is a command, false otherwise.
 */
bool isCommand(char c) {
    return c == 'p' || c == 'n' || c == 'f' || c == 'c' || c == 'd' || c == 'r' || c == 'e' || c == 'h' || c == 'w';
}

/**
 * Returns true if the passed character is not a digit, a command recognized by the
 * application, an operator recognized by the application, a negative value (_), a space,
 * an end-of-line, or a dot (.).
 *
 * @param r character being tested.
 * @return true if character is not any of the things specified above.
 */
bool isAnythingElse(char r) {
    return !isdigit(r) && !isCommand(r) && !isOperator(r) && r != '_' && r != ' ' && r != '\0' && r != '.';
}

/**
 * Wraps passed string in red and returns it, used to output error messages with color in
 * the command line.
 *
 * @param message being returned in color
 * @return passed string but wrapped in color
 */
string redText(const string &message) {
    return "\033[0;31;1m" + message + "\033[0m";
}

/**
 * Wraps passed string in yellow and returns it, used to output text with color in the
 * command line.
 *
 * @param message being returned in color
 * @return passed string but wrapped in color
 */
string yellowText(const string &message) {
    return "\033[0;33;1m" + message + "\033[0m";
}

void err(char errorType, const string &message) {
    switch(errorType) {
        case 'u':
            cout << "\a\n" << redText("    Underflow Exception:\n    ") << message << "\n" << endl; break;
        case 'o':
            cout << "\a\n" << redText("    Overflow Exception:\n    ") << message << "\n" << endl; break;
        case 'd':
            cout << "\a\n" << redText("    Data Error Exception:\n    ") << message << "\n" << endl; break;
        case 'z':
            cout << "\a\n" << redText("    Division by Zero Exception:\n    ") << message << "\n" << endl; break;
        default:
            cout << "\a\n" << redText("    Exception:\n    ") << message << "\n" << endl; break;
    }
}
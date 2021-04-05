#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include "stack.h"

using namespace std;

void printTop(const Stack<double> &s);
void printAndPopTop(Stack<double>& s);
void printAll(Stack<double> s);
void makeEmpty(Stack<double>& s);
void duplicateTop(Stack<double>& s, int& total);
void swapTop(Stack<double>& s);
void help();
string yellowText(const string &m);

void getInput(string& i);
void populate(Stack<double>& s, string i, int& total);
void operate(Stack<double>& s, char o);
bool isOperator(char o);
bool isCommand(char c);
bool isAnythingElse(char r);

void checkSize(Stack<double>& s, int& t);

void err(char t, const string &m);
string redText(const string &m);


int main() {
    Stack<double> s;
    string i;
    int t = 10;
    while(true) {
        getInput(i);
        populate(s, i, t);
    }
}

void getInput(string& i) {
    cout << "\033[0;32m"; getline(cin, i); cout << "\033[0m";
}

void checkSize(Stack<double>&s, int& t) {
    try {
        if(s.isFull()) throw Overflow(1);
    }
    catch(Overflow& e) {
        if(t == 10) {
            err(e.type, e.explanation);
        }
        double ta[t];
        Stack<double> ts(t * 2);
        int pos = 0;
        while(pos < t) {
            ta[pos] = s.topAndPop();
            pos++;
        }
        while(pos > 0) {
            ts.push(ta[pos - 1]);
            pos--;
        }
        s = ts;
        t *= 2;
    }
}

void printTop(const Stack<double> &s) {
    try {
        if(s.isEmpty()) throw Underflow(1);
        cout << s.top() << endl;
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

void printAndPopTop(Stack<double>& s) {
    try {
        if(s.isEmpty()) throw Underflow(2);
        cout << s.top() << " "; s.pop();
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

void printAll(Stack<double> s) {
    try {
        if(s.isEmpty()) throw Underflow(3);
        cout << s.topAndPop() << endl;
        while(!s.isEmpty()) {
            cout << s.topAndPop() << endl;
        }
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

void makeEmpty(Stack<double>& s) {
    try {
        if(s.isEmpty()) throw Underflow(4);
        Stack<double> ts;
        s = ts;
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

void duplicateTop(Stack<double>& s, int& total) {
    try {
        if(s.isEmpty()) throw Underflow(5);
        checkSize(s, total);
        s.push(s.top());
    }
    catch(Underflow& e) {
        err(e.type, e.explanation);
    }
}

void swapTop(Stack<double>& s) {
    double tempA = 0, a = 0, b = 0;
    bool aValid = true;
    bool bValid = true;
    try {
        if(s.isEmpty()) throw Underflow(6);
        tempA = s.top();
        a = s.topAndPop();
    }
    catch(Underflow& e) {
        aValid = false;
        err(e.type, e.explanation);
    }
    try {
        if(aValid) {
            if(s.isEmpty()) throw Underflow(7);
            b = s.topAndPop();
        }
    }
    catch(Underflow& e) {
        bValid = false;
        err(e.type, e.explanation);
    }
    if(aValid && bValid) {
        s.push(a);
        s.push(b);
    }
    if(aValid && !bValid) {
        s.push(tempA);
    }
}

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

void operate(Stack<double>& s, char o) {
    double tempA = 0, tempB = 0, a = 0, b = 0, c = 0;
    bool aValid = true;
    bool bValid = true;
    bool valid = true;
    try {
        if(s.isEmpty()) throw Underflow(8);
        tempA = s.top();
        a = s.topAndPop();
    }
    catch(Underflow& e) {
        aValid = false;
        err(e.type, e.explanation);
    }
    try {
        if(aValid) {
            if(s.isEmpty()) throw Underflow(9);
            tempB = s.top();
            b = s.topAndPop();
        }
    }
    catch(Underflow& e) {
        bValid = false;
        err(e.type, e.explanation);
    }
    switch(o) {
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
        s.push(c);
    }
    if(!bValid) {
        s.push(tempA);
    }
    if(aValid && bValid && !valid) {
        s.push(tempB);
        s.push(tempA);
    }
}

void populate(Stack<double>& s, string i, int& total) {
    int pos = 0;

    // While we have not reached the end of the string...
    while(i[pos] != '\0') {

        // If character is a space, go to next character.
        if(i[pos] == ' ') pos++;

        // If character is a '.', double starting with '.' has been found.
        if(i[pos] == '.') {
            bool valid = true;
            string t;
            t.append(string(1, i[pos]));
            pos++;
            while(i[pos] == '.') {
                pos++;
            }
            try {
                if(!isdigit(i[pos])) throw DataError(4);
            }
            catch(DataError& e) {
                valid = false;
                err(e.type, e.explanation);
                pos++;
            }
            while(isdigit(i[pos]) && valid) {
                t.append(string(1, i[pos]));
                pos++;
            }
            if(valid) {
                checkSize(s, total);
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end);
                s.push(td);
            }
        }

        // If character is a digit, double has been found.
        if(isdigit(i[pos])) {
            bool point = false;
            bool valid = true;
            string t;
            while((isdigit(i[pos]) || i[pos] == '.') && !point) {
                if(i[pos] == '.') point = true;
                t.append(string(1, i[pos]));
                pos++;
            }
            while(i[pos] == '.') {
                pos++;
            }
            if(point) {
                try {
                    if(!isdigit(i[pos])) throw DataError(4);
                }
                catch(DataError& e) {
                    valid = false;
                    err(e.type, e.explanation);
                    pos++;
                }
            }
            while(isdigit(i[pos]) && valid) {
                t.append(string(1, i[pos]));
                pos++;
            }
            if(valid) {
                checkSize(s, total);
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end);
                s.push(td);
            }
        }

        // If character is '_', negative double has been found.
        if(i[pos] == '_') {
            bool valid = true;
            bool point = false;
            string t;
            pos++;
            while(i[pos] == '_' || i[pos] == '.') {
                if(i[pos] == '.' && !point) {
                    t.append(string(1, i[pos]));
                    point = true;
                }
                pos++;
            }
            if(point) {
                try {
                    if(!isdigit(i[pos])) throw DataError(1);
                }
                catch(DataError& e) {
                    valid = false;
                    err(e.type, e.explanation);
                }
            }
            while((isdigit(i[pos]) || i[pos] == '.') && !point) {
                if(i[pos] == '.') point = true;
                t.append(string(1, i[pos]));
                pos++;
            }
            while(isdigit(i[pos])) {
                t.append(string(1, i[pos]));
                pos++;
            }
            if(valid) {
                const char* p = t.c_str(); char* end;
                double td = strtod(p, &end) * -1.0;
                if(td == -0) td*=-1;
                s.push(td);
            }
        }

        // If character is an operator, operate then move to next character.
        if(isOperator(i[pos])) {
            operate(s, i[pos]);
            pos++;
        }

        // If character is a command, call specific command then move to next character.
        if(isCommand(i[pos])) {
            switch(i[pos]) {
                case 'p': printTop(s); break;
                case 'n': printAndPopTop(s); break;
                case 'f': printAll(s); break;
                case 'c': makeEmpty(s); total = 10; break;
                case 'd': duplicateTop(s, total); break;
                case 'r': swapTop(s); break;
                case 'h': help(); break;
                case 'e': exit(0);
                case 'w': cout << "\033[2J\033[1;1H"; break;
                default: break;
            }
            pos++;
        }
        try {
            // If character is anything else, erroneous character has been found. Throw error.
            if(isAnythingElse(i[pos])) throw DataError(2);
        }
        catch(DataError& e) {
            err(e.type, e.explanation);
            pos++;
        }
    }
}

bool isOperator(char o) {
    return o == '+' || o == '-' || o == '*' || o == '/' || o == '%';
}

bool isCommand(char c) {
    return c == 'p' || c == 'n' || c == 'f' || c == 'c' || c == 'd' || c == 'r' || c == 'e' || c == 'h' || c == 'w';
}

bool isAnythingElse(char r) {
    return !isdigit(r) && !isCommand(r) && !isOperator(r) && r != '_' && r != ' ' && r != '\0' && r != '.';
}

string redText(const string &m) {
    return "\033[0;31;1m" + m + "\033[0m";
}

string yellowText(const string &m) {
    return "\033[0;33;1m" + m + "\033[0m";
}

void err(char t, const string &m) {
    switch(t) {
        case 'u':
            cout << "\a\n" << redText("    Underflow Exception:\n    ") << m << "\n" << endl; break;
        case 'o':
            cout << "\a\n" << redText("    Overflow Exception:\n    ") << m << "\n" << endl; break;
        case 'd':
            cout << "\a\n" << redText("    Data Error Exception:\n    ") << m << "\n" << endl; break;
        case 'z':
            cout << "\a\n" << redText("    Division by Zero Exception:\n    ") << m << "\n" << endl; break;
        default:
            cout << "\a\n" << redText("    Exception:\n    ") << m << "\n" << endl; break;
    }
}

#pragma clang diagnostic pop
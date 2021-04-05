#ifndef DESK_CALCULATOR_DSEXCEPTIONS_H
#define DESK_CALCULATOR_DSEXCEPTIONS_H

#include <utility>

class Underflow {
public:
    explicit Underflow();
    explicit Underflow(int e);
    char type;
    std::string explanation;
};

Underflow::Underflow() {
    this->type = 'u';
}

Underflow::Underflow(int e) {
    this -> type = 'u';
    switch(e) {
        case 1: explanation = "Can't print the top of an empty stack."; break;          // printTop error
        case 2: explanation = "An empty stack cannot be printed or popped."; break;     // printAndPopTop error
        case 3: explanation = "An empty stack cannot be printed."; break;               // printAll error
        case 4: explanation = "An empty stack cannot be emptied."; break;               // makeEmpty error
        case 5: explanation = "Can't duplicate the top of an empty stack."; break;      // duplicateTop error
        case 6: explanation = "Can't swap the top of an empty stack."; break;           // swapTop error 1
        case 7: explanation = "Missing values, can't swap the top of stack."; break;    // swapTop error 2
        case 8: explanation = "Stack empty, can't complete operation."; break;          // operate error 1
        case 9: explanation = "Missing values, can't complete operation."; break;       // operate error 2
        default: explanation = ""; break;
    }
}

class Overflow  {
public:
    explicit Overflow();
    explicit Overflow(int e);
    char type;
    std::string explanation;
};

Overflow::Overflow() {
    this -> type = 'o';
}

Overflow::Overflow(int e) {
    this -> type = 'o';
    switch(e) {
        case 1: explanation = "Stack is full. Doubling size. This is not really\n    an error, just wanted to show you how I handled\n    overflow. The program continues as normal."; break;
        default: explanation = ""; break;
    }
};

class OutOfMemory { };
class BadIterator { };

class DataError {
public:
    explicit DataError();
    explicit DataError(int e);
    char type;
    std::string explanation;
};

DataError::DataError() {
    this -> type = 'd';
}

DataError::DataError(int e) {
    this -> type = 'd';
    switch(e) {
        case 1: explanation = "Rogue \'_\' without an number concluding it. Ignored."; break;
        case 2: explanation = "Unrecognized character encountered. Ignored."; break;
        case 3: explanation = "Stack is full. Doubling size. This is not really\n    an error, just wanted to show you how I handled\n    overflow. The program continues as normal."; break;
        case 4: explanation = "Rogue \'.\' without a number concluding it. Ignored."; break;
        default: explanation = ""; break;
    }
};

class DivisionByZero {
public:
    explicit DivisionByZero();
    explicit DivisionByZero(int e);
    char type;
    std::string explanation;
};

DivisionByZero::DivisionByZero() {
    this -> type = 'z';
}

DivisionByZero::DivisionByZero(int e) {
    this -> type = 'z';
    switch(e) {
        case 1: explanation = "Can't divide a number by zero. Operation skipped."; break;
        case 2: explanation = "Can't compute the remainder. Operation skipped."; break;
        default: explanation = ""; break;
    }
}


#endif //DESK_CALCULATOR_DSEXCEPTIONS_H
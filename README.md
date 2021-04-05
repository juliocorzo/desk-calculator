# desk-calculator

Simple calculator with prefix notation, (`1 1 +` equals `2` as opposed to the familiar 
infix notation `1 + 1`) emulating one of the oldest Unix utilities created by Robert 
Morris from Bell Labs in the 70s. 

While this calculator isn't a copy of the original, (it's very simple compared to the 
original,) it provided valuable learning experiences about how data structures and 
algorithms work, and it also started my journey into C++.

The calculator is implemented using a stack, where values are pushed and then operated on 
depending on user input. 

Errors are handled to make sure the user cannot make invalid operations, for example, 
dividing a number by zero or attempting to multiply a number when the stack only has one 
number. 

### Algorithm outline

1. The program first attempts to get user input. Once characters are input, the second 
phase of the algorithm starts.
   
2. Input is sent to a function that goes through it on a character-by-character basis. 
The character that it encounters dictates what the program does.
   
3. Once the character encountered is `/0`, we have reached the end of the user input, and 
the program goes back to its original state.
   
### Commands

The application can take commands related to the calculator, those being: 
* `p` prints the result of the last operation to the screen.
* `n` prints the topmost number and pops it from the stack.
* `f` prints the entire stack.
* `c` clears the entire stack.
* `d` duplicates the last number input.
* `r` swaps the top number and the one proceeding it. 

It also comes with useful commands that provide information or clear the command line.
* `h` provides the user a list of possible commands.
* `e` exits the program.
* `w` clears the screen.

### Example

A simple example of how the program works. 

| Input   | Actions                                                 |
| :------ | :------------------------------------------------------ |
| `1_0.2` | Push `1`, `-0.2`                                        |
| `p`     | Prints `-0.2`                                           |
| `10*p`  | Push `10` -> pop and multiply `-0.2`, `10` -> push `-2` |
| `f`     | Prints `-2`, `1`                                        |

### Improvements

1. The stack was originally a fixed size. This program automatically doubles the size 
   of the stack it becomes larger than it is.
    
2. The program was originally only able to handle integers. This was reworked to be 
   able to receive decimal numbers. 

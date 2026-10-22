This project is going to be over the development of a compiler for a C-like programming language guided by our professor for 4318, called mC. 


# Phase1 

The process for this project starts with writing/completion of a scanner to recognize the tokens in mC. Tokens that are required to be recognized are:

1. Identifiers - begin with upper/lower case letter. The first letter can be followed by any number alphanumeric. No restrictions on the length of identifiers

2. Reserved words/Keywords - {if, else, while, int, string, char, return, void}

3. Integer Constants - unsigned dequence of digits representing a base-10 numer, with no leading zeroes allowed.
   
4. Character constants - a single character enclosed in single quotes

5. String constants - A sequence of characters enlosed in double quotes (ie. "Hello World"). Cannot cross line boundaries and give an error when it does. Quatations are not part of the string length. CAN containt {\n, \t, \\", \\\\} for newline, tab, double quotes, backslash itself

6. Escape sequences - throw errors and exits when "\\" is followed by an unknown escape character, e.g. "\\b"

7. Operators and special symbols - List of operations and symbols allowed. Seperate token per return for each {+, *, /, %, <, >, <=, >=, ==, !=, =, [, ], {, }, (, ), ',', ';', @, ++, --, &&, ||, !}

8. Comments - any squence enclosed within "/\*" and "*/" but return an error for incomplete comments

9. Whitespace - all whitespace is ignored, this includes newline, tab, or space

10. Error messages - Errors should report the line and column number where error occured for each. For comment and string, the position indicated should correspond to the starting position of the unterminated comment or string. {'Illegal token', 'Unterminated comment', 'Unterminated string constant', 'Unrecognized escape character in String', 'String spans multiple lines'}

**********************************
# Running the scanner:
This is all to be implemented using either lex or flex for the scanner implementation. 
Ran using a makefile, that calls on 'scanner.l', 'tokendef.h' and 'driver.c'

To use within the linux server:
```
[]$ cd Phase1
[Phase1]$ make clean
[Phase1]$ make
[Phase1]$ cd obj

[Phase1/obj]$ ./scanner ../src/test.txt
```

Optionally, from the Phase1 folder:
```
[Phase1]$ make clean
[Phase1]$ make
[Phase1]$ ./obj/scanner < ./src/test.txt
```

#### Note: you can replace test.txt with whatever .txt file you wish to test against.
#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
string input = "A2 + B3 * (C4 - D5)";
size_t currentPos = 0;

void addChar();  // Add nextChar to lexeme
void getChar();  // Get nextChar and determine its class
void getNonBlank();  // Skip over whitespace
int lex();  // Main lexeme analysis function
int lookup(char ch);  // Lookup operators and parentheses and return their tokens

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define EOF_TOKEN -1

int main() {
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);
    return 0;
}

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF_TOKEN;
        break;
    }
    return nextToken;
}

void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

void getChar() {
    if (currentPos < input.size()) {
        nextChar = input[currentPos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF_TOKEN;
        nextChar = '\0';
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF_TOKEN:
        nextToken = EOF_TOKEN;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = '\0';
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
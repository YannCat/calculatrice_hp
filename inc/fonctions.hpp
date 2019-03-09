#include <iostream>     // cout, endl
#include <string>	// string ; string::find ; stoi ; stod ; to_string
#include <stack>        // stack - LIFO
#include <queue>        // queue - FIFO
#include <utility>	// pair
#include <algorithm>    // min_element
#include <locale>       // isdigit
#include <exception>	// try {instructions} ; throw (type) ; catch{type const& name}

using namespace std;

pair<stack<string>, queue<string> > resultByStack(string const userInput);
string evaluate_A_B_op(string operandA, string operandB, string operatorUsed);
string calculation(pair<stack<string>, queue<string> > myPair);
int checkInput(string const& userInput);

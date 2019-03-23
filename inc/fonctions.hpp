#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <iostream>     // cout, endl
#include <string>	// string ; string::find ; stoi ; stod ; to_string
#include <stack>        // stack - LIFO
#include <queue>        // queue - FIFO
#include <utility>	// pair
#include <algorithm>    // min_element
#include <locale>       // isdigit
#include <exception>	// try {instructions} ; throw (type) ; catch{type const& name}


/* author : Maxime BELAVAL
 * ON NE MODIFIE PAS MON CODE SANS ME PREVENIR ET SANS MON AUTORISATION.
 * ON N'UTILISE PAS DE NAMESPACE STD.
 */

// prototypes à mettre dans une classe, en privé
std::pair<std::stack<std::string>, std::queue<std::string> > resultByStack(std::string const userInput);
std::string evaluate_A_B_op(std::string operandA, std::string operandB, std::string operatorUsed);
std::string calculation(std::pair<std::stack<std::string>, std::queue<std::string> > myPair);
int checkInput(std::string const& userInput);

#endif // FONCTIONS_HPP

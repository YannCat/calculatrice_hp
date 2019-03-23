#include "fonctions.hpp"


/* author : Maxime BELAVAL
 * ON NE MODIFIE PAS MON CODE SANS ME PREVENIR ET SANS MON AUTORISATION.
 * ON N'UTILISE PAS DE NAMESPACE STD.
 */

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input into a string
 * @return : the result of the calculation
 */
std::pair<std::stack<std::string>, std::queue<std::string> > resultByStack(std::string const userInput) {
    std::stack<std::string> calculStack;                            // LIFO - must be an attribut of the class in the real code -- just set here to test the method on my own
    std::queue<std::string> operatorsQueue;                         // FIFO - must be an attribut of the class in the real code -- just set here to test the method on my own
    std::string acquisitionString;

    for (unsigned int i(0); i != userInput.size(); ++i) {
        if( isdigit(userInput[i]) != 0 ) {
            acquisitionString += userInput[i];
        } // end if 1

        if( (userInput[i] == ' ') || (userInput[i] == '\0') ) {     // if we reached a separator, then we clear the acquisition string
            if( isdigit(acquisitionString[0]) != 0 ) {
                calculStack.push(acquisitionString);                // digit successfully reconstituted
                acquisitionString.clear();                          // clear of the acquisition string
            } // end if 3
        } // end if 2

        else {
            std::string tmp; tmp += userInput[i];                   // if it is neither a separator nor a digit, so we match an operator and push it into the queue
            if(
                tmp.find('+') != std::string::npos ||
                tmp.find('-') != std::string::npos ||
                tmp.find('*') != std::string::npos ||
                tmp.find('/') != std::string::npos
                ) {
                    acquisitionString.clear();
                    acquisitionString += userInput[i];
                    operatorsQueue.push(acquisitionString);
            } // end if 4
        } // end else
    } // end for

    std::pair<std::stack<std::string>, std::queue<std::string> > p;
    p.first = calculStack;
    p.second = operatorsQueue;

    return p;
} // end method

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : two operands, A and B, as well as the operator that suits
 * @return : a string that contains the calculation
 * @obj    : template for all types
 */
std::string evaluate_A_B_op(std::string operandA, std::string operandB, std::string operatorUsed) {
    double opA(0.0), opB(0.0);

    // first, we have to use the same basis, ie double to include all possible case
    if( operandA.find('.') != std::string::npos )   opA = std::stod(operandA, nullptr);
    else                                            opA = std::stod(operandA+".0", nullptr);
    if( operandB.find('.') != std::string::npos )   opB = std::stod(operandB, nullptr);
    else                                            opB = std::stod(operandB+".0", nullptr);

    // final result
    double result(0);

    // switch...case with std::string doesn't work well, that's why we use an int instead
    int operatorInt(0);
    (operatorUsed=="+")?(operatorInt=1):( (operatorUsed=="-")?(operatorInt=2):( (operatorUsed=="*")?(operatorInt=3):operatorInt=4  ) );

        switch(operatorInt) {
                case 1 :
                            result = opA + opB;
                            break;
                case 2 :
                            result = opA - opB;
                            break;
                case 3 :
                            result = opA * opB;
                            break;
                case 4 :
                            try {
                                if(opB == 0.0) throw std::string("Div. par zéro impossible");
                                else result = opA / opB;
                            } // end try
                            catch(std::string const& chaine) {
                               std::cerr << chaine << std::endl;
                            } // end catch
                            break;
                default: break;
            } // end switch

            return std::to_string(result);
} // end method

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : a pair whose the first is the stack of operands and the second is the queue with operators
 * @return : the calculation with a string type
 */
std::string calculation(std::pair<std::stack<std::string>, std::queue<std::string> > myPair) {
    if( myPair.second.size() > myPair.first.size() )	return "Erreur trop d'opérateurs";
    if( myPair.second.empty() )                         return "Erreur pas d'opérateurs";
    if( myPair.first.empty() )							return "Erreur pas d'opérandes";

    std::string tmpResult, operandA, operandB, operatorUsed;

    while( myPair.first.size() > 1 ) {	// as long as we do not have the final result
        try {	// if we have to solve (ie if there are 2 or more elements in the stack, we have to take an operator from the queue)
            if( (myPair.first.size() >= 2) && (myPair.second.size() >= 1) ) {
                operatorUsed = myPair.second.front();
                               myPair.second.pop();
            }
        } catch(std::exception const& e) {
            std::string erreur1("Erreur pas assez d'opérateurs : ");
                                                        return erreur1 + e.what();
        }
        try {	// if we have to solve (ie if we got the operator for, we need 2 operands from the stack)
            if( (myPair.first.size() >= 2) && (myPair.second.size() >= 1) ) {
                operandA = myPair.first.top();
                           myPair.first.pop();
                operandB = myPair.first.top();
                           myPair.first.pop();
            }
        } catch(std::exception const& e) {
            std::string erreur2("Erreur pas assez d'opérandes : ");
                                                        return erreur2 + e.what();
        }

        // here, we should have operandA, operandB, operatorUsed filled with conforming values
        tmpResult = evaluate_A_B_op(operandA, operandB, operatorUsed);
        myPair.first.push(tmpResult);
    } // end while

    // leaving the while means myPair->first.siez() == 1, ie the final result is the only element inside the stack
    std::string result(myPair.first.top());
    myPair.first.pop();
                                                        return result;
} // end function

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input with a std::string type
 * @return : 0 = good, -1 or -2 = not good
 */
int checkInput(std::string const& userInput) {
    std::size_t foundP = userInput.find("+");
    std::size_t foundM = userInput.find("-");
    std::size_t foundF = userInput.find("*");
    std::size_t foundD = userInput.find("/");

    std::size_t position[4] = {foundP, foundM, foundF, foundD};
    unsigned int operatorPosition = *std::min_element(position, position+4);

    // I want to check from the beginning to (operatorPosition - 1) we only have digits, and from operatorPosition to the end, we only have operators (both including spaces as separators)
    for(unsigned int i(0); i <= operatorPosition; ++i) {
        if( !(isdigit(userInput[i]) != 0) || !(userInput[i] == ' ') )                               return -1; // not good for the operands
    }

    for(unsigned int i(operatorPosition); i <= userInput.size(); ++i) {
        if( !(isdigit(userInput[i]) != 0) || !(userInput[i] == ' ') || !(userInput[i] == '\0') )    return -2; // not good for the operators
    }

                                                                                                    return 0;  // good
}

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
/*
            STACK : (operands)                                                                          QUEUE : (operators)
            Last In First Out                                                                           First In First Out
    --> push(8)	  --> top() & pop() = 8                                                             --> push(8)
                8												  8
                5												  5
                12												  12
                4												  4
                23												  23
                                                                                                                --> front() & pop() = 23
*/
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

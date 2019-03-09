#include "fonctions.hpp"

using namespace std;

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input into a string
 * @return : the result of the calculation
 */
pair<stack<string>, queue<string> > resultByStack(string const userInput) {
    stack<string> calculStack;                            // LIFO - must be an attribut of the class in the real code -- just set here to test the method on my own
    queue<string> operatorsQueue;                         // FIFO - must be an attribut of the class in the real code -- just set here to test the method on my own
    string acquisitionString;

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
            string tmp; tmp += userInput[i];                   // if it is neither a separator nor a digit, so we match an operator and push it into the queue
            if(
                tmp.find('+') != string::npos ||
                tmp.find('-') != string::npos ||
                tmp.find('*') != string::npos ||
                tmp.find('/') != string::npos
                ) {
                    acquisitionString.clear();
                    acquisitionString += userInput[i];
                    operatorsQueue.push(acquisitionString);
            } // end if 4
        } // end else
    } // end for

    pair<stack<string>, queue<string> > p;
    p.first = calculStack;
    p.second = operatorsQueue;

    return p;
} // end method

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : two operands, A and B, as well as the operator that suits
 * @return : a string that contains the calculation
 * @obj    : template for all types
 */
string evaluate_A_B_op(string operandA, string operandB, string operatorUsed) {
    double opA(0.0), opB(0.0);

    // first, we have to use the same basis, ie double to include all possible case
    if( operandA.find('.') != string::npos )   opA = stod(operandA, nullptr);
    else                                            opA = stod(operandA+".0", nullptr);
    if( operandB.find('.') != string::npos )   opB = stod(operandB, nullptr);
    else                                            opB = stod(operandB+".0", nullptr);

    // final result
    double result(0);

    // switch...case with string doesn't work well, that's why we use an int instead
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
                                if(opB == 0.0) throw string("Div. par zéro impossible");
                                else result = opA / opB;
                            } // end try
                            catch(string const& chaine) {
                               cerr << chaine << endl;
                            } // end catch
                            break;
                default: break;
            } // end switch

            return to_string(result);
} // end method

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : a pair whose the first is the stack of operands and the second is the queue with operators
 * @return : the calculation with a string type
 */
string calculation(pair<stack<string>, queue<string> > myPair) {
    if( myPair.second.size() > myPair.first.size() )	return "Erreur trop d'opérateurs";
    if( myPair.second.empty() )                         return "Erreur pas d'opérateurs";
    if( myPair.first.empty() )							return "Erreur pas d'opérandes";

    string tmpResult, operandA, operandB, operatorUsed;

    while( myPair.first.size() > 1 ) {	// as long as we do not have the final result
        try {	// if we have to solve (ie if there are 2 or more elements in the stack, we have to take an operator from the queue)
            if( (myPair.first.size() >= 2) && (myPair.second.size() >= 1) ) {
                operatorUsed = myPair.second.front();
                               myPair.second.pop();
            }
        } catch(exception const& e) {
            string erreur1("Erreur pas assez d'opérateurs : ");
                                                        return erreur1 + e.what();
        }
        try {	// if we have to solve (ie if we got the operator for, we need 2 operands from the stack)
            if( (myPair.first.size() >= 2) && (myPair.second.size() >= 1) ) {
                operandA = myPair.first.top();
                           myPair.first.pop();
                operandB = myPair.first.top();
                           myPair.first.pop();
            }
        } catch(exception const& e) {
            string erreur2("Erreur pas assez d'opérandes : ");
                                                        return erreur2 + e.what();
        }

        // here, we should have operandA, operandB, operatorUsed filled with conforming values
        tmpResult = evaluate_A_B_op(operandA, operandB, operatorUsed);
        myPair.first.push(tmpResult);
    } // end while

    // leaving the while means myPair->first.siez() == 1, ie the final result is the only element inside the stack
    string result(myPair.first.top());
    myPair.first.pop();
                                                        return result;
} // end function

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input with a string type
 * @return : 0 = good, -1 or -2 = not good
 */
int checkInput(string const& userInput) {
    size_t foundP = userInput.find("+");
    size_t foundM = userInput.find("-");
    size_t foundF = userInput.find("*");
    size_t foundD = userInput.find("/");

    size_t position[4] = {foundP, foundM, foundF, foundD};
    unsigned int operatorPosition = *min_element(position, position+4);

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
void Calculatrice::s_button0() {
    if(ms_resultat->text() != "0") ms_resultat->setText(ms_resultat->text()+"0");
} // end slot


void Calculatrice::s_button1() {
    if(ms_resultat->text() == "0") ms_resultat->setText("1");
    else ms_resultat->setText(ms_resultat->text()+"1");
} // end slot


void Calculatrice::s_button2() {
    if(ms_resultat->text() == "0") ms_resultat->setText("2");
    else ms_resultat->setText(ms_resultat->text()+"2");
} // end slot


void Calculatrice::s_button3() {
    if(ms_resultat->text() == "0") ms_resultat->setText("3");
    else ms_resultat->setText(ms_resultat->text()+"3");
} // end slot


void Calculatrice::s_button4() {
    if(ms_resultat->text() == "0") ms_resultat->setText("4");
    else ms_resultat->setText(ms_resultat->text()+"4");
} // end slot


void Calculatrice::s_button5() {
    if(ms_resultat->text() == "0") ms_resultat->setText("5");
    else ms_resultat->setText(ms_resultat->text()+"5");
} // end slot


void Calculatrice::s_button6() {
    if(ms_resultat->text() == "0") ms_resultat->setText("6");
    else ms_resultat->setText(ms_resultat->text()+"6");
} // end slot


void Calculatrice::s_button7() {
    if(ms_resultat->text() == "0") ms_resultat->setText("7");
    else ms_resultat->setText(ms_resultat->text()+"7");
} // end slot


void Calculatrice::s_button8() {
    if(ms_resultat->text() == "0") ms_resultat->setText("8");
    else ms_resultat->setText(ms_resultat->text()+"8");
} // end slot


void Calculatrice::s_button9() {
    if(ms_resultat->text() == "0") ms_resultat->setText("9");
    else ms_resultat->setText(ms_resultat->text()+"9");
} // end slot


void Calculatrice::s_buttonEgal() { /// MUST SET IN OUTPUT THE FINAL RESULT, SO HERE IS THE BIGGEST JOB TO DO
    ms_resultat->setText("Penser à coder = un jour...");
} // end slot


void Calculatrice::s_buttonPoint() {
    if(ms_pointCount == 0) {
        ms_resultat->setText(ms_resultat->text()+".");
        ++ms_pointCount;
    }
} // end slot

*/
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
/*
void Calculatrice::s_buttonEffacer() {
    ms_informations->setText("Dernière action : suppression dernier caractère");
    tmpEffacer = ms_resultat->text();

    // if I have at least 1 number or mathematical operator and I ask an erase, I set 0 as result (it's what else is doing)
    // otherwise, I just remove the last choice the user selected. We need size()-1 to find the true index position of the last input, and then, we remove 1 character
    if(tmpEffacer.size() > 1) {
        tmpEffacer.remove((tmpEffacer.size()-1), 1);        /// RAJOUTER L'EXCEPTION SI ON REMOVE UN POINT, ET DONC RESET DE L'ATTRIBUT ms_pointCount
    } else {
        tmpEffacer = "0";
    }

    ms_resultat->setText(tmpEffacer);
} // end slot


void Calculatrice::s_buttonReset() {
    ms_informations->setText("Dernière action : reset de la saisie utilisateur");
    ms_resultat->setText("0");
    ms_pointCount = 0;
} // end slot


void Calculatrice::s_buttonPlus() {
    deleteOperatorIfNeeded();
    ms_resultat->setText(ms_resultat->text()+"+");
} // end slot


void Calculatrice::s_buttonMoins() {
    deleteOperatorIfNeeded();
    ms_resultat->setText(ms_resultat->text()+"-");
} // end slot


void Calculatrice::s_buttonFois() {
    deleteOperatorIfNeeded();
    ms_resultat->setText(ms_resultat->text()+"x");
} // end slot


void Calculatrice::s_buttonDivise() {
    deleteOperatorIfNeeded();
    ms_resultat->setText(ms_resultat->text()+"/");
} // end slot


void Calculatrice::deleteOperatorIfNeeded() {
    // warning : calling the function back() on an empty string constitutes undefined behavior
    // that's why we always have at least one number in ms_resultat.text(), which is 0 if nothing has been done by the user
    if(ms_resultat->text().back() == '+' || ms_resultat->text().back() == '-' || ms_resultat->text().back() == 'x' || ms_resultat->text().back() == '/') {
        ms_informations->setText("Dernière action : remplacement du dernier opérateur par le nouveau souhaité");
        ms_resultat->setText(ms_resultat->text().remove((ms_resultat->text().size()-1), 1));
    }
} // end function
*/
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
/*
                STACK :	(operands)								QUEUE : (operators)
            Last In First Out								First In First Out

    --> push(8)	  --> top() & pop() = 8						  --> push(8)
                8												  8
                5												  5
                12												  12
                4												  4
                23												  23
                                                                      --> front() & pop() = 23
*/
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

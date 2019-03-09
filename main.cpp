#include <iostream>     // std::cout, std::endl
#include <string>	// std::string ; std::string::find ; std::stoi ; std::stod ; std::to_string
#include <stack>        // std::stack - LIFO
#include <queue>        // std::queue - FIFO
#include <utility>	// std::pair
#include <algorithm>    // std::min_element
#include <locale>       // std::isdigit
#include <exception>	// try {instructions} ; throw (type) ; catch{type const& name}

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
    if( operandB.find('.') != std::string::npos )   opB = std::stod(operandA, nullptr);
    else                                            opB = std::stod(operandA+".0", nullptr);

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

int main()
{
//    std::string result, input;
    std::cout << "Tests method : std::string resultByStack(std::string userInput)" << std::endl;

    /// ATTENTION : POUR QUE CA FONCTIONNE, FAUT METTRE UN ESPACE DANS LA SAISIE USER APRES CHAQUE OPERATEUR ET OPERANDE (sinon prend pas en compte le dernier)
    /// (d'ailleurs, quand l'user push un boutton, ca ajoutera le chiffre ou opérateur correspondant + 1 espace (vu que c'est le separateur) (si derniere saisie is digit, alors suppr l'espace d'avant ==> Et C'EST OK)
/*
        std::cout << "Input : 12 21 53 + + + " << std::endl;
            input.clear();  input = "12 21 53 + + + ";
            result.clear(); result = resultByStack(input);
        std::cout << "Result expected : 86" << std::endl;
        std::cout << "Result returned : " << result << std::endl;
        std::cout << std::endl;

        std::cout << "Input : 12 21 53 - * / " << std::endl;
            input.clear();  input = "12 21 53 - * / ";
            result.clear(); result = resultByStack(input);
        std::cout << "Result expected : -384" << std::endl;
        std::cout << "Result returned : " << result << std::endl;
        std::cout << std::endl;

        std::cout << "Input : 12 21 53 " << std::endl;
            input.clear();  input = "12 21 53 ";
            result.clear(); result = resultByStack(input);
        std::cout << "Result expected : error no operators" << std::endl;
        std::cout << "Result returned : " << result << std::endl;
        std::cout << std::endl;

        std::cout << "Input : + + + " << std::endl;
            input.clear();  input = "+ + + ";
            result.clear(); result = resultByStack(input);
        std::cout << "Result expected : error no operands" << std::endl;
        std::cout << "Result returned : " << result << std::endl;
        std::cout << std::endl;
*/
    return 0;
}

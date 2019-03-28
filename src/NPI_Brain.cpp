#include "NPI_Brain.h"

// CONSTRUCTOR
NPI_Brain::NPI_Brain()
{
    if( !this->sOperands.empty() && !this->qOperators.empty() ) this->reset();
/*
this->sOperands.push("25");
this->sOperands.push("7");
this->qOperators.push("+");
*/

}

// DESTRUCTOR
NPI_Brain::~NPI_Brain() {
}


// PUBLIC METHODS :
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input into a string
 * @return : true if reset succeed, fail if it failed
 * @use    : reset attributs
 * @class  : must be public
 */

bool NPI_Brain::reset() {
    for(unsigned int i(0); i < this->sOperands.size(); ++i) {
        this->sOperands.pop();
    }
    for(unsigned int i(0); i < this->qOperators.size(); ++i) {
        this->qOperators.pop();
    }

    return (this->sOperands.empty() && this->qOperators.empty());
}


void NPI_Brain::setCurrentInputOnDisplayer(std::string s) {
    this->currentInputOnDisplayer = s;
}

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input into a string
 * @return : the result of the calculation or the input + " " if no calculation required
 * @use    : this method can be only call thanks to the enter button
 * @class  : must be public
 * @initial conditions : user input from the GUI -> none
                         stack status			 -> empty
                         queue status			 -> empty
 */

std::string NPI_Brain::enterButton_calculation(std::string const& input) {
    // 1. Check the input and take the last
    // From input.end() to last (end - position du dernier espace)
    std::string expectedInput("");

    if( this->sOperands.empty() ) {
        expectedInput = input;
    } else {
        std::size_t found = input.find_last_of(" ");
        expectedInput = input.substr(found+1, input.length());
    }

    // 2. If I can set it as a double, then it's an operand, otherwise it's an operator
    double value(0.0);
    if( !this->getDoubleValue(expectedInput, value) ) {
        if( expectedInput != "" )
        this->qOperators.push(expectedInput);
    } else {
        this->sOperands.push(expectedInput);
    }

    // 3. If it must solve, returns the result, if not, return the input + " "
        // Case 1 : initial conditions			-> return "Nothing to do..."
        // Case 2 : the input is an operand		-> We return the input + " "
        // Case 3 : the input is an operator	-> We have to solve
            // Case 3.a : if it can solve	-> return the result
            // Case 3.b : if it cannot		-> return "Syntax Error"	--> done within the method 'evaluate_A_B_op'

    std::string operandA(""), operandB(""), operatorUsed("");

    if ( this->sOperands.empty() && this->qOperators.empty() ) {
        return "Nothing to do...";
    } else if ( this->getDoubleValue(expectedInput, value) ) {
        expectedInput = input;
        return expectedInput.append(" ");;
    } else if ( !this->getDoubleValue(expectedInput, value) ) {
        try { // operandA
            if( this->sOperands.top() != "" && !this->sOperands.empty() ) {
                operandA = this->sOperands.top();
                this->sOperands.pop();
                std::cout << "POP A '" << operandA << "'" << std::endl;
            }
        } catch ( std::exception & e ) {
            operandA = "0.0"; // in case of errors
        }

        try { // operandB
            if( this->sOperands.top() != "" && !this->sOperands.empty() ) {
                operandB = this->sOperands.top();
                this->sOperands.pop();
                std::cout << "POP B '" << operandB << "'" << std::endl;
            }
        } catch ( std::exception & e ) {
            operandB = "0.0"; // in case of errors
        }

        try { // operatorUsed
            if( this->qOperators.front() != "" && !this->qOperators.empty() ) {
                operatorUsed = this->qOperators.front();
                this->qOperators.pop();
                std::cout << "POP Op '" << operatorUsed << "'" << std::endl;
            }
        } catch ( std::exception & e ) {
            return "Error Operator";
        }

    }
    return evaluate_A_B_op(operandA, operandB, operatorUsed);
} // end method

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : none
 * @return : the result of the calculation or the input + " " if no calculation required
 * @use    : this method can be only call thanks to the enter button
 * @class  : must be public
 * @initial conditions : user input from the GUI -> none
                         stack status			 -> empty
                         queue status			 -> empty
 */

std::string NPI_Brain::enterButton_calculation_v2() {
    // Method used every time we push on the Enter button

    std::string validOutput("");

    // 1. Check the input
    //  1.a State 0 : Virgin Init
    if( this->sOperands.empty() && this->qOperators.empty() ) {
        validOutput = this->currentInputOnDisplayer;
    } else {
        std::size_t found = this->currentInputOnDisplayer.find_last_of(" ");
        validOutput = this->currentInputOnDisplayer.substr(found+1, this->currentInputOnDisplayer.length());
    }

    double value(0.0);

    //  1.b If I can set it as a double, then it's an operand, otherwise it's an operator
    if( !this->getDoubleValue(validOutput, value) ) {
        if( validOutput != "" )
        this->qOperators.push(validOutput);
    } else {
        this->sOperands.push(validOutput);
    }


    std::string operandA(""), operandB(""), operatorUsed("");

    // 2. Solve
    // Case 1 : initial conditions			-> return "Nothing to do..."
    // Case 2 : the input is an operand		-> We return the input + " "
    // Case 3 : the input is an operator	-> We have to solve
        // Case 3.a : if it can solve	-> return the result
        // Case 3.b : if it cannot		-> return "Syntax Error"	--> done within the method 'evaluate_A_B_op'
    if ( this->sOperands.empty() && this->qOperators.empty() ) {
        return "Nothing to do...";
    } else if ( this->getDoubleValue(validOutput, value) ) {
        validOutput = this->currentInputOnDisplayer;
        return validOutput.append(" ");;
    } else if ( !this->getDoubleValue(validOutput, value) ) {
        try { // operandA
            if( this->sOperands.top() != "" && !this->sOperands.empty() ) {
                operandA = this->sOperands.top();
                this->sOperands.pop();
                //std::cout << "POP A '" << operandA << "'" << std::endl;   // debug
            }
        } catch ( std::exception & e ) {
            operandA = "0.0"; // in case of errors
        }

        try { // operandB
            if( this->sOperands.top() != "" && !this->sOperands.empty() ) {
                operandB = this->sOperands.top();
                this->sOperands.pop();
                //std::cout << "POP B '" << operandB << "'" << std::endl;   // debug
            }
        } catch ( std::exception & e ) {
            operandB = "0.0"; // in case of errors
        }

        try { // operatorUsed
            if( this->qOperators.front() != "" && !this->qOperators.empty() ) {
                operatorUsed = this->qOperators.front();
                this->qOperators.pop();
                //std::cout << "POP Op '" << operatorUsed << "'" << std::endl;   // debug
            }
        } catch ( std::exception & e ) {
            return "Error Operator";
        }

    } // end 2. Solve


    // 3. Final
    return evaluate_A_B_op(operandA, operandB, operatorUsed);

} // end method


// PRIVATE METHODS :
//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

// SETTERS
void NPI_Brain::setOperands(std::string s) {
    sOperands.push(s);
}

void NPI_Brain::setOperators(std::string s) {
    qOperators.push(s);
}

// GETTERS
std::string NPI_Brain::getOperand() {
    std::string s_operand("");

    if( !this->sOperands.empty() ) {
        s_operand = this->sOperands.top();
        this->sOperands.pop();
    }
    return s_operand;
}


std::string NPI_Brain::getOperator() {
    std::string s_operator("");

    if( !this->qOperators.empty() ) {
        s_operator = this->qOperators.back();
        this->qOperators.pop();
    }
    return s_operator;
}

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : the user input into a string, the double conversion if it succeed
 * @return : true : conversion ok, it's an operand | false : conversion failed, it's an operator
 * @class  : must be protected or private
 */

bool NPI_Brain::getDoubleValue( std::string const& input, double & value ) {
    bool result = true;

    try {
        value = std::stod(input);
        //std::cout << "Conversion OK" << std::endl; // DEBUG
    } catch ( std::exception & e ) {
        //std::cerr << "Error in conversion of '" << input << "' into number: " << e.what() << std::endl; // DEBUG
        result = false;
    }
    return result;
}

//     --------------------------------------------------------------------------------------------------------------------------------------------------------------------------     //

/* @param  : two operands, A and B, as well as the operator that suits
 * @return : a string that contains the calculation
 * @obj    : template for all types
 * @class  : must be protected or private
 */

std::string NPI_Brain::evaluate_A_B_op(std::string operandA, std::string operandB, std::string operatorUsed) {
    double opA(0.0), opB(0.0);

    // first, we have to use the same basis, ie double to include all possible case
    try {
    if( operandA.find('.') != std::string::npos )   opA = std::stod(operandA, nullptr);
    else                                            opA = std::stod(operandA+".0", nullptr);
    } catch ( std::exception & e ) {
        return "Syntax Error for operand A";
    }

    try {
    if( operandB.find('.') != std::string::npos )   opB = std::stod(operandB, nullptr);
    else                                            opB = std::stod(operandB+".0", nullptr);
    } catch ( std::exception & e ) {
        return "Syntax Error for operand B";
    }

    // final result
    double result(0);

    // switch...case with std::string doesn't work well, that's why we use an int instead
    int operatorInt(0);

    (operatorUsed=="+")?(operatorInt=1):( (operatorUsed=="-")?(operatorInt=2):( (operatorUsed=="*")?(operatorInt=3):( (operatorUsed=="/")?(operatorInt=4):(operatorInt=5) ) ) );

        switch(operatorInt) {
                case 1 :
                            result = opA + opB;
                            //std::cout << "--- r : " << result << " ---" << std::endl;
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
                                //std::cerr << chaine << std::endl;
                                return chaine;
                            } // end catch
                            break;
                case 5 :
                default:
                            return "Syntax Error for operatorUsed";
                            break;
            } // end switch

            return std::to_string(result);
} // end method

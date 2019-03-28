#ifndef TMPCLASS_H
#define TMPCLASS_H

#include <string>		// std::string ; std::string::find ; std::stoi ; std::stod ; std::to_string ; std::substr ; std::append
#include <stack>		// std::stack - LIFO
#include <queue>		// std::queue - FIFO
#include <locale>		// std::isdigit
#include <exception>	// try {instructions} ; throw (type) ; catch{type const& name}

// NO USING NAMESPACE STD ! WE'RE DOING REAL CODE !

#include <iostream>     // for shield test & debug


class NPI_Brain
{
public:
    // Constructor
    NPI_Brain();

    // Destructor
    ~NPI_Brain();

    // Methods asked at every push on the specified button
    std::string enterButton_calculation(std::string const& input);
    std::string enterButton_calculation_v2();

    // Reset
    bool reset();

    // For shield test & debug only -- has to go in private when it'll be done
    void setCurrentInputOnDisplayer(std::string s);


private:
    // Setters
    inline void setOperands(std::string s);
    inline void setOperators(std::string s);

    // Getters
    inline std::string getOperand();
    inline std::string getOperator();

    // Internal Methods
    inline bool getDoubleValue( std::string const& input, double & value );
    std::string evaluate_A_B_op(std::string operandA, std::string operandB, std::string operatorUsed);

    // Attributs
    std::string currentInputOnDisplayer;    // input data on the displayer/the screen
    std::stack<std::string> sOperands;
    std::queue<std::string> qOperators;
};

#endif // TMPCLASS_H

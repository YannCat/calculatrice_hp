#include "NPI_Brain.h"

int main()
{
/*
    std::cout << "Tests methods : " << std::endl
              << "  std::string enterButton_calculation(std::string const& input);" << std::endl
              << "  bool getDoubleValue( std::string const& input, double & value );" << std::endl
              << "  std::string evaluate_A_B_op(std::string operandA, std::string operandB, std::string operatorUsed);" << std::endl
              << "          from tmpClass" << std::endl;
*/

    std::cout << "Start test NPI_Brain :" << std::endl << std::endl;

    NPI_Brain littleBrain;

    std::string newInput1("12");
    littleBrain.setCurrentInputOnDisplayer(newInput1);
    std::cout << "current input on displayer :" << newInput1 << std::endl;
    std::cout << "Check push 1 : '" << littleBrain.enterButton_calculation_v2() << "'" << std::endl << std::endl;

    std::string newInput2("3");
    littleBrain.setCurrentInputOnDisplayer(newInput2);
    std::cout << "current input on displayer :" << newInput2 << std::endl;
    std::cout << "Check push 2 : '" << littleBrain.enterButton_calculation_v2() << "'" << std::endl << std::endl;

    std::string newInput3("+");
    littleBrain.setCurrentInputOnDisplayer(newInput3);
    std::cout << "current input on displayer :" << newInput3 << std::endl;
    //std::cout << "Check result : '" << littleBrain.enterButton_calculation((newInput1+" "+newInput2+" "+newInput3)) << "'" << std::endl << std::endl;
    std::cout << "Check result : '" << littleBrain.enterButton_calculation_v2() << "'" << std::endl << std::endl;

    std::cout << "End test NPI_Brain" << std::endl << std::endl;




//    std::cout << "Check state 0 : '" << littleBrain.enterButton_calculation("") << "'" << std::endl;
/*
    NPI_Brain.enterButton_calculation("25");
    std::cout << "Check state 1 '25' : '" << littleBrain.enterButton_calculation("25") << "'" << std::endl;

    NPI_Brain.enterButton_calculation("7");
    std::cout << "Check state 2 '7' : '" << littleBrain.enterButton_calculation("7") << "'" << std::endl;

    NPI_Brain.enterButton_calculation("+");
    std::cout << "Check state 3 '+' : '" << littleBrain.enterButton_calculation("+") << "'" << std::endl;
*/

/*
    std::cout << "TEST" << std::endl;
    std::string test("test ");
    test[test.length()-1] == ' '? (std::cout << "OK" << std::endl):(std::cout << "NOK" << std::endl);
*/
    return 0;
}

#include "fonctions.hpp"
#include "affichage.hpp"

/* author : Maxime BELAVAL
 * ON NE MODIFIE PAS MON CODE SANS ME PREVENIR ET SANS MON AUTORISATION.
 * ON N'UTILISE PAS DE NAMESPACE STD.
 */

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

// #include "GUI.hpp" // GUI.hpp is a generic name to describe the main class used for the GUI
#include "fonctions.hpp"

/* author : Maxime BELAVAL
 * ON NE MODIFIE PAS MON CODE SANS ME PREVENIR ET SANS MON AUTORISATION.
 * ON N'UTILISE PAS DE NAMESPACE STD.
 */


// THIS HAS TO BE IMPLEMENT IN THE GUI AS SLOTS FOR THE BUTTON AND TO DISPLAY THE RESULT
// ADD FONCTIONS DEFINED IN fonctions.hpp


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


/*__________________________________________________________________________________
|       Disciplina de Sistemas Embarcados - 2022-1
|       Prof. Douglas Renaux
| __________________________________________________________________________________
|
|		Lab 1
| __________________________________________________________________________________
*/

/**
 * @file     main.cpp
 * @author   Douglas P. B. Renaux
 * @brief    Solution to Lab1 of ELF74/CSW41 - UTFPR. \n 
 *           Tools instalation and validation procedure.\n 
 *           Show messages on terminal using std::cout. \n 
 *           Show current value of some predefined macros (preprocessor symbols).\n 
 *           Read float value from terminal using std::cin.
 * @version  V2 -for 2022-1 semester
 * @date     Feb, 2022
 ******************************************************************************/

/*------------------------------------------------------------------------------
 *
 *      Use Doxygen to report lab results
 *
 *------------------------------------------------------------------------------*/
/** @mainpage Results from Lab1
 *
 * @section Ouput Values
 *
 * The values of ...
 *
 * @section Terminal
 *
 * @subsection Output
 *
 * etc...
 */

/*------------------------------------------------------------------------------
 *
 *      File includes
 *
 *------------------------------------------------------------------------------*/
#include <stdint.h>

#include <iostream>
using namespace std;

#include "template.h"

/*------------------------------------------------------------------------------
 *
 *      Typedefs and constants
 *
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *
 *      Global vars
 *
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *
 *      File scope vars
 *
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *
 *      Functions and Methods
 *
 *------------------------------------------------------------------------------*/
/**
 * Main function.
 *
 * @param[in] argc - not used, declared for compatibility
 * @param[in] argv - not used, declared for compatibility
 * @returns int    - not used, declared for compatibility
 */
int main(int argc, char ** argv)
{
    /* Mensagem inicial */
    cout<<("Mensagem inicial!\n");
    /* Simbolos pre-definidos */
    cout<<("__cplusplus\n");
    cout<<(__cplusplus);
    cout<<("\n");
    cout<<("__DATE__");
    cout<<("\n");
    cout<<(__DATE__);
    cout<<("\n");
    cout<<("__TIME__");
    cout<<("\n");
    cout<<(__TIME__);
    cout<<("\n");
    cout<<("__FILE__");
    cout<<("\n");
    cout<<(__FILE__);
    cout<<("\n");
    cout<<("__LINE__");
    cout<<("\n");
    cout<<(__LINE__);
    cout<<("\n");
    cout<<("__STDC__");
    cout<<("\n");
    cout<<(__STDC__);
    cout<<("\n");
    cout<<("__STDC_VERSION__");
    cout<<("\n");
    cout<<(__STDC_VERSION__);
    cout<<("\n");
    cout<<("__ARM_ARCH");
    cout<<("\n");
    cout<<(__ARM_ARCH);
    cout<<("\n");
    cout<<("__ARM_ARCH_ISA_THUMB");
    cout<<("\n");
    cout<<(__ARM_ARCH_ISA_THUMB);
    cout<<("\n");
    cout<<("__ARM_SIZEOF_MINIMAL_ENUM");
    cout<<("\n");
    cout<<(__ARM_SIZEOF_MINIMAL_ENUM);
    cout<<("\n");
    cout<<("__ARM_SIZEOF_WCHAR_T");
    cout<<("\n");
    cout<<(__ARM_SIZEOF_WCHAR_T);
    cout<<("\n");
    cout<<("__ARMVFP__");
    cout<<("\n");
    cout<<(__ARMVFP__);
    cout<<("\n");
    cout<<("__CORE__");
    cout<<("\n");
    cout<<(__CORE__);
    cout<<("\n");
    /* Ler cin um float */
    float valor;
    cin >> valor;
    /* Somar a outro valor em float */
    valor += 1.23;
    /* Apresentar o valor da soma */
    cout<<(valor);
    cout<<("\n");

    return 0;
}

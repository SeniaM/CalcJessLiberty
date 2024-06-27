#include <iostream>
#include "ErrorHandlingModule.h"

namespace SAMSErrorHandling
{
    using namespace std;
    void Initialize()
    {
        cin.exceptions(cin.failbit);
    }
    int HandleNotANumberError()
    {
        cerr << "Input error - input may not have been a number." << endl;
        cin.clear();

        char BadInput[5];
        cin >> BadInput;
        return 1;
    }
}

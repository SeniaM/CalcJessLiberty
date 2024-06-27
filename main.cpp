#include <iostream>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

float GetDividend()
{
    float Dividend = 0;
    cout << "Dividend: ";
    cin >> Dividend;
    return Dividend;
}

float GetDivisor()
{
    float Divisor = 1;
    cout << "Divisor: ";
    cin >> Divisor;
    return Divisor;
}

float Divide(const float theDividend, const float theDivisor)
{
    return (theDividend/theDivisor);
}

int main()
{
    SAMSErrorHandling::Initialize();

    int ReturnCode = 0;
     do
    {


        try
        {
            float Dividend = GetDividend();
            float Divisor = GetDivisor();

            cout << Divide(Dividend, Divisor) << endl;
        }


        catch(...)
        {
            ReturnCode = SAMSErrorHandling::HandleNotANumberError();
        };
    }
    while(SAMSPrompt::UserWantsToContinue("More Division?"));

        SAMSPrompt::PauseForUserAcknowledgement();

        return ReturnCode;

}

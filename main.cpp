#include <iostream>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

void Tape(const char theOperator, const float theOperand) {
    static const int myTapeSize = 3;
    static char myOperator[myTapeSize];
    static float myOperand[myTapeSize];

    static int myNumberOfEntries = 0;

    if(theOperator != '?') {
        if(myNumberOfEntries < myTapeSize) {
            myOperator[myNumberOfEntries] = theOperator;
            myOperand[myNumberOfEntries] = theOperand;
            ++myNumberOfEntries;
        }
        else {
            throw std::runtime_error("Error - out of room on the tape.");
        }
    }
    else {
        for(int Index = 0; Index < myNumberOfEntries;++Index) {
            std::cout << myOperator[Index] << ", " << myOperand[Index] << endl;
        }
    }
}

float Accumulate(const char theOperator, const float theOperand) {
    static float myAccumulator = 0;

    switch(theOperator) {
    case '+':
        myAccumulator += theOperand;
        break;
    case '-':
        myAccumulator -= theOperand;
        break;
    case '*':
        myAccumulator *= theOperand;
        break;
    case '/':
        myAccumulator /= theOperand;
        break;
     case '?':
        break;
    default:
        throw runtime_error("Error - Invalid operator");
    }

    Tape(theOperator, theOperand);
    return myAccumulator;
}

float GetOperator() {
    char Operator = ' ';
    cout << "Operator: ";
    cin >> Operator;
    return Operator;
}

float GetOperand() {
    float Operand = 1;
    cout << "Operand: ";
    cin >> Operand;
    return Operand;
}

float Divide(const float theDividend, const float theDivisor) {
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
            float Operator = GetOperator();
            float Operand = GetOperand();

            cout << Accumulate(Operator, Operand) << endl;
        }

        catch(runtime_error RuntimeError)
        {
            SAMSErrorHandling::HandleRuntimeError(RuntimeError);
        }

        catch(...)
        {
            ReturnCode = SAMSErrorHandling::HandleNotANumberError();
        };
    }
    while(SAMSPrompt::UserWantsToContinue("More?"));

        SAMSPrompt::PauseForUserAcknowledgement();

        return ReturnCode;

}

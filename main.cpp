#include <iostream>
#include "PromptModule.h"
#include "ErrorHandlingModule.h"

using namespace std;

void Tape(const char theOperator, const float theOperand) {
    static const int myTapeChunk = 3;
    static char *myOperator = new char[myTapeChunk];
    static int *myOperand = new int[myTapeChunk];

    static int myTapeSize = myTapeChunk;
    static int myNumberOfEntries = 0;

    switch(theOperator) {
    case '?':
        for(int Index = 0; Index < myNumberOfEntries; ++Index) {
           std::cout << myOperator[Index] << " , "
                     << myOperand[Index] << std::endl;
        }
        break;

    case '.':
        delete [] myOperator;
        delete [] myOperand;

        break;
    default:
        if(myNumberOfEntries == myTapeSize) {
            char *ExpandedOperator = new char[myNumberOfEntries + myTapeChunk];
            int *ExpandedOperand =new int[myNumberOfEntries + myTapeChunk];

            char *FromOperator = myOperator;
            int *FromOperand = myOperand;

            char *ToOperator = ExpandedOperator;
            int *ToOperand = ExpandedOperand;

            for(int Index = 0; Index < myNumberOfEntries; ++Index) {
                *ToOperator++ = *FromOperator++;
                *ToOperand++ = *FromOperand++;
            }
            delete [] myOperator;
            delete [] myOperand;

            myOperator = ExpandedOperator;
            myOperand = ExpandedOperand;

            myTapeSize += myTapeChunk;
        }
        myOperator[myNumberOfEntries] = theOperator;
        myOperand[myNumberOfEntries] = theOperand;
        ++myNumberOfEntries;
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

        catch (const std::runtime_error &RuntimeError)
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

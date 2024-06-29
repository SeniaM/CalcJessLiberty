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
        if (myNumberOfEntries == myTapeSize) {
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

float Accumulator(const char theOperator, const float theOperand = 0) {
    static float myAccumulator = 0;

    switch(theOperator) {
    case '+':
        myAccumulator += theOperand;
        Tape(theOperator, theOperand);
        break;
    case '-':
        myAccumulator -= theOperand;
        Tape(theOperator, theOperand);
        break;
    case '*':
        myAccumulator *= theOperand;
        Tape(theOperator, theOperand);
        break;
    case '/':
        myAccumulator /= theOperand;
        Tape(theOperator, theOperand);
        break;
    case '@':
        myAccumulator = theOperand;
        Tape(theOperator, theOperand);
        break;
    case '=':
        std::cout << std::endl << myAccumulator << std::endl;
        break;
    case '?':
        Tape(theOperator, theOperand);
        break;
    default:
        throw runtime_error("Error - Invalid operator");
    }

    return myAccumulator;
}

float GetOperator() {
    char Operator;
    cin >> Operator;

    return Operator;
}

float GetOperand() {
    float Operand;
    cin >> Operand;

    return Operand;
}

float Divide(const float theDividend, const float theDivisor) {
    return (theDividend/theDivisor);
}

bool TestOk(const char theOperator, const float theOperand, const float theExpectedResult) {
    float Result = Accumulator(theOperator, theOperand);
    if (Result == theExpectedResult) {
        std::cout << theOperator << theOperand << " - succeeded." << std::endl;
        return true;
    }
    else {
        std::cout << theOperator << theOperand << " - failed." << "Expected " << theExpectedResult << ", got " << Result << std::endl;
        return false;
    }
}

void SelfTest() {
    float OldValue = Accumulator('=');

    try {
        if (TestOk('@', 0, 0) &&
           TestOk('+', 3, 3) &&
           TestOk('-', 2, 1) &&
           TestOk('*', 4, 4) &&
           TestOk('/', 2, 2)) {
           std::cout << "Test completed successfully.";
        }
        else {
            std::cout << "Test failed" << std::endl;
        }
    }
    catch(...) {
        std::cout << "An exception occured during self test." << std::endl;
    }
    Accumulator('@', OldValue);
}

int main()
{
    SAMSErrorHandling::Initialize();

    char Operator;
     do
    {


        try
        {
            Operator = GetOperator();

            if (Operator == '+' ||
               Operator == '-' ||
               Operator == '*' ||
               Operator == '/' ||
               Operator == '@') {

               float Operand = GetOperand();
               Accumulator(Operator, Operand);
            }
            else if (Operator == '!') {
                SelfTest();
            }
            else if (Operator == '.') {

            }
            else {
                Accumulator(Operator);
            }

        }

        catch (const std::runtime_error &RuntimeError)
        {
            SAMSErrorHandling::HandleRuntimeError(RuntimeError);
        }

        catch(...)
        {
            SAMSErrorHandling::HandleNotANumberError();
        };
    }
    while(Operator != '.');
    Tape('.', 0);
        return 0;

}

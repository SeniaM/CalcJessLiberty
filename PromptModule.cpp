#include <iostream>
#include "PromptModule.h"

using namespace std;

namespace SAMSPrompt
{
   void PauseForUserAcknowledgement()
{
    char StopCharacter;
    cout << endl << "Press a key and \"Enter\": ";
    cin >> StopCharacter;
}
bool UserWantsToContinue (const char * theThingWeAreDoing)
{
    char DoneCharacter;
    cout << endl << theThingWeAreDoing << " - Press \"n\" and \"Enter\" to stop: ";
    cin >> DoneCharacter;
    return (DoneCharacter !='n');
}
bool UserWantsToContinueYOrN (const char * theThingWeAreDoing)
{
    char DoneCharacter;
    bool InvalidCharacterWasEntered = false;
    do
    {
        cout << endl << theThingWeAreDoing << " - Press \"n\" and \"Enter\" to stop: ";
        cin >> DoneCharacter;
        InvalidCharacterWasEntered = !(DoneCharacter == 'y'|| DoneCharacter == 'n');
        if(InvalidCharacterWasEntered)
        {
            cout << "...Error -" << " please enter \"y\" or \"n\"." << endl;
        }

    }
    while (InvalidCharacterWasEntered);

    return (DoneCharacter != 'n');

}
}


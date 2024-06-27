#ifndef PROMPTMODULE_H_INCLUDED
#define PROMPTMODULE_H_INCLUDED
namespace SAMSPrompt
{
   void PauseForUserAcknowledgement();
   bool UserWantsToContinue (const char * theThingWeAreDoing);
   bool UserWantsToContinueYOrN (const char * theThingWeAreDoing);
}
#endif // PROMPTMODULE_H_INCLUDED

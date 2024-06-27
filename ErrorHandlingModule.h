#ifndef ERRORHANDLINGMODULE_H_INCLUDED
#define ERRORHANDLINGMODULE_H_INCLUDED
namespace SAMSErrorHandling
{
    void Initialize();
    int HandleNotANumberError();
    int HandleRuntimeError(std::runtime_error);
}
#endif // ERRORHANDLINGMODULE_H_INCLUDED

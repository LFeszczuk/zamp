#include <iostream>
#include "Interp4Pause.hh"
#include <memory>
#include "network_sending.hh"

using std::cout;
using std::endl;

extern "C"
{
    Interp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Pause"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
    return Interp4Pause::CreateCmd();
}

/*!
 *
 */
Interp4Pause::Interp4Pause() : _time_ms(0)
{
}

/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
    /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
    cout << GetCmdName() << " " << _time_ms << " " << endl;
}

/*!
 *
 */
const char *Interp4Pause::GetCmdName() const
{
    return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Pause::ExecCmd(Scene * pScn,AccessGuard *pAccGuard) const
{
   cout<<"Zatrzymanie  ::  Pause"<<endl;
    return true;
}

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream &Strm_CmdsList)
{
    Strm_CmdsList >> _time_ms;
    return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Pause::CreateCmd()
{
    return new Interp4Pause();
}

/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
    cout << "   Pause  czas[ms]" << endl;
}

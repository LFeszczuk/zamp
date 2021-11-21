#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;

extern "C"
{
    Interp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
    return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : wspx(0), wspy(0), _axis_x(0), _axis_y(0), _axis_z(0)
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
    /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
    cout << GetCmdName() << " " << _Obj_name << " " << wspx << " " << wspy << " " << _axis_x << " " << _axis_y << " " << _axis_z << " " << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
    return "Set";
}

/*!
 *
 */
bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
{
    /*
   *  Tu trzeba napisać odpowiedni kod.
   */
    return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
    Strm_CmdsList >> _Obj_name >> wspx >> wspy >> _axis_x >> _axis_y >> _axis_z;
    return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Set::CreateCmd()
{
    return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
    cout << "   Set  NazwaObiektu  Wspx Wspy KątOX KątOY KątOZ " << endl;
}

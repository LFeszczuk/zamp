#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "network_sending.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Move"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}

/*!
 *
 */
Interp4Move::Interp4Move() : _Speed_mmS(0), _Dist_m(0)
{
}

/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName()<< "  " << _Obj_name << "  " << _Speed_mmS << "  " << _Dist_m << "  " << endl;
}

/*!
 *
 */
const char *Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Move::ExecCmd(Scene * pScn,AccessGuard *pAccGuard) const
{
 
  cout<<"Poruszanie :: Move"<<endl;
  return true;
}

/*!
 *
 */
bool Interp4Move::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _Obj_name >> _Speed_mmS >> _Dist_m;
  return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Move::CreateCmd()
{
  return new Interp4Move();
}

/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}

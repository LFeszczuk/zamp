#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"
#include "network_sending.hh"

using std::cout;
using std::endl;

extern "C"
{
    Interp4Command *CreateCmd(void);
    const char *GetCmdName() { return "Rotate"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
    return Interp4Rotate::CreateCmd();
}

/*!
 *
 */
Interp4Rotate::Interp4Rotate() : _V_ang(0), _axis_name(0), _Rot_ang(0)
{
}

/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{

    cout << GetCmdName() << " " << _Obj_name << " " << _V_ang << " " << _axis_name << " " << _Rot_ang << endl;
}

/*!
 *
 */
const char *Interp4Rotate::GetCmdName() const
{
    return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Rotate::ExecCmd(Scene *pScn, AccessGuard *pAccGuard) const
{
    std::shared_ptr<MobileObj> pObj;
    if (!pScn->FindMobileObject(_Obj_name, pObj))
    {
        // pAccGuard->UnlockAccess();
        std::cerr << "Nie znaleziono obiektu: " << '\"' << _Obj_name << '\"' << " !!!" << std::endl;
        return false;
    }
    Vector3D positionVector;
    Vector3D SizeVector;
    //positionVector[0]=wspx;
    //positionVector[1]=wspy;
    positionVector[2] = pObj->GetPosition_m()[2];
    //   SizeVector=pObj->GetSize_m();
    //   pObj->SetPosition_m(positionVector);
    //   pObj->SetAng_Yaw_deg(_axis_z);
    //AddObj Name=Podstawa.Ramie1.Ramie2 Shift=(-0.5,0,0) Scala=(0.8,0.3,0.3) Trans_m(1,0,0)\n

    std::ostringstream OStrm;
    // OStrm << "AddObj Name=Ramie Trans_m=(6,0,0)\n";
    OStrm << "AddObj Name=" << pObj->GetName() << " Trans_m=(6,0,0)\n";

    Send2Server(pAccGuard->GetSocket(), OStrm.str().c_str());
    cout << "___ Wyslane polecenie: " << OStrm.str();
    return true;
}

/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream &Strm_CmdsList)
{
    Strm_CmdsList >> _Obj_name >> _V_ang >> _axis_name >> _Rot_ang;
    return !Strm_CmdsList.fail();
}

/*!
 *
 */
Interp4Command *Interp4Rotate::CreateCmd()
{
    return new Interp4Rotate();
}

/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
    cout << "   Rotate  NazwaObiektu prędkość kątowa, nazwa osi , kąt obrotu" << endl;
}

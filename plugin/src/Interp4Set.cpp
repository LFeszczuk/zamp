#include <iostream>
//#include <sstream>
//#include <chrono>
//#include <thread>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include "network_sending.hh"

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
bool Interp4Set::ExecCmd(Scene *pScn, AccessGuard *pAccGuard) const
{

    // std::shared_ptr<MobileObj> pObj;
    // if (!pScn->FindMobileObject(_Obj_name, pObj))
    // {

    //     std::cerr << "Nie znaleziono obiektu: " << '\"' << _Obj_name << '\"' << " !!!" << std::endl;
    //     return false;
    // }
    // cout << pObj->GetStateDesc() << endl;

    //         std::lock_guard<std::mutex>  Lock(pAccGuard->UseGuard());
    //                            // modyfikacje na obiekcie.
    // //                            cout<<"fsdnfkjsdn"<<endl;
    //  std::ostringstream  OStrm;
    //   std::shared_ptr<MobileObj> pObj;
    //   if(!pScn->FindMobileObject(_Obj_name, pObj))
    //   {
    //      // pAccGuard->UnlockAccess();
    //     std::cerr << "Nie znaleziono obiektu: " <<'\"'<< _Obj_name <<'\"' << " !!!" << std::endl;
    //     return false;
    //   }
    //   Vector3D positionVector;
    //   Vector3D SizeVector;
    //   positionVector[0]=wspx;
    //   positionVector[1]=wspy;
    //   positionVector[2]=pObj->GetPosition_m()[2];
    //   SizeVector=pObj->GetSize_m();
    //   pObj->SetPosition_m(positionVector);
    //   pObj->SetAng_Yaw_deg(_axis_z);
    //   //AddObj Name=Podstawa.Ramie1.Ramie2 Shift=(-0.5,0,0) Scala=(0.8,0.3,0.3) Trans_m(1,0,0)\n
    //        OStrm << "AddObj Name="<<pObj->GetName()<< "Shift="<<positionVector<<"Scala="<<SizeVector<<"\n";

    //         Send2Server(pAccGuard->GetSocket(),OStrm.str().c_str());
    // 	cout << "___ Wyslane polecenie: " << OStrm.str();
    // // pAccGuard->UnlockAccess();
    // //  // usleep(300000);
    // #define STEP_NUM         20
    //  #define MOVE_STEP        0.2
    //     std::ostringstream  OStrm;

    //     //----------------------------------------------------------------------------
    //     // W tej pętli symulowane jest wykonywanie elementarnych kroków danego polecenia
    //     for (unsigned int StepIdx = 0; StepIdx < STEP_NUM; ++StepIdx ) {
    //       { //--- Początek lokalnego bloku, w którym zablokowany jest mutex
    // 	// Można zakomentować linię poniżej, aby zobaczyć co się dzieje,
    // 	// gdy mutex nie jest blokowany.
    // 	//
    //         OStrm.str("");
    //         std::lock_guard<std::mutex>  Lock(pAccGuard->UseGuard());
    // 	//------------------------------------------------
    // 	// Wykonujemy operację związaną z daną operacją.
    // 	//
    //         OStrm << "SetObj Name=Os Trans_m=("
    //               << MOVE_STEP*StepIdx << ",0,0)\n";

    //         Send2Server(pAccGuard->GetSocket(),OStrm.str().c_str());
    // 	cout << "___ Wyslane polecenie: " << OStrm.str();
    //   } //--- Koniec lokalnego bloku, w którym zablokowany jest mutex

    //   //---------------------------------------------------------
    //   // Na chwilę usypiamy wątek, aby dać czas wykonania się
    //   // innym wątkom.
    //   //

    //   //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //  } // for
    std::shared_ptr<MobileObj> pObj;
    if (!pScn->FindMobileObject(_Obj_name, pObj))
    {
        // pAccGuard->UnlockAccess();
        std::cerr << "Nie znaleziono obiektu: " << '\"' << _Obj_name << '\"' << " !!!" << std::endl;
        return false;
    }
    Vector3D positionVector;
    Vector3D SizeVector;
    positionVector[0] = wspx;
    positionVector[1] = wspy;
    //   positionVector[2]=pObj->GetPosition_m()[2];
    //   SizeVector=pObj->GetSize_m();
    //   pObj->SetPosition_m(positionVector);
    //   pObj->SetAng_Yaw_deg(_axis_z);
    //   //AddObj Name=Podstawa.Ramie1.Ramie2 Shift=(-0.5,0,0) Scala=(0.8,0.3,0.3) Trans_m(1,0,0)\n
    //        OStrm << "AddObj Name="<<pObj->GetName()<< "Shift="<<positionVector<<"Scala="<<SizeVector<<"\n";

    std::ostringstream OStrm;
    OStrm << "AddObj Name=Ramie Trans_m=(6,0,0)\n";

    Send2Server(pAccGuard->GetSocket(), OStrm.str().c_str());
    cout << "___ Wyslane polecenie: " << OStrm.str();
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

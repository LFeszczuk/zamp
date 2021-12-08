#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <string>
#include <cstdio>
#include <memory>
#include <unistd.h>
#include <vector>
#include <thread>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Set4Libinterfaces.hh"
#include "Scene.hh"
#include "Configuration.hh"
#include "ServerConnection.hh"
#include "XML_ReadFile.hh"
#include "network_connection.hh"
using namespace std;

#define LINE_SIZE 500

int Send(int Sk2Server, const char *sMesg)
{
  ssize_t IlWyslanych;
  ssize_t IlDoWyslania = (ssize_t)strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server, sMesg, IlDoWyslania)) > 0)
  {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0)
  {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

bool OpenConnection(int &rSocket)
{
  struct sockaddr_in DaneAdSerw;

  bzero((char *)&DaneAdSerw, sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);

  rSocket = socket(AF_INET, SOCK_STREAM, 0);

  if (rSocket < 0)
  {
    cerr << "*** Blad otwarcia gniazda." << endl;
    return false;
  }

  if (connect(rSocket, (struct sockaddr *)&DaneAdSerw, sizeof(DaneAdSerw)) < 0)
  {
    cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
    return false;
  }
  return true;
}

bool ExecPreprocesor(const char *NazwaPliku, istringstream &IStrm4Cmds)
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += NazwaPliku;
  FILE *pProc = popen(Cmd4Preproc.c_str(), "r");
  if (!pProc)
    return false;
  while (fgets(Line, LINE_SIZE, pProc))
  {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc) == 0;
}

void ExecActions(istream &AIStrm, Set4Libinterfaces &LibInterfaceSet, Scene *pScn, AccessGuard *pAccCtrl)
{
  string CmdKey;

  while (AIStrm >> CmdKey)
  {
    cout << "Polecenie: " << CmdKey << endl;

    Set4Libinterfaces::const_iterator Iter = LibInterfaceSet.find(CmdKey);
    if (Iter == LibInterfaceSet.end())
    {
      cout << "Uwaga nieznane polecenie! :  " << CmdKey << endl;
    }

    Interp4Command *pInterp = Iter->second->_pCreateCmd();
    if (!pInterp->ReadParams(AIStrm))
    {
      cout << "Nie można wczytać parametrów" << endl;
      delete pInterp;
    }
    cout << "________Parametry:________" << endl;
    pInterp->PrintCmd();

    if (!pInterp->ExecCmd(pScn, pAccCtrl))
    {
      cout << "Błąd wykonywania polecenia" << endl;
      delete pInterp;
    }
    cout << endl;

    delete pInterp;
  }
}
// void Fun4Thread_ReadProgram_ExecCmds(istream &AIStrm, Set4Libinterfaces &LibInterfaceSet, AccessGuard *pAccCtrl)
// {
//   ExecActions(AIStrm, LibInterfaceSet,  pAccCtrl);
// }

int main(int argc, char **argv)
{

  Set4Libinterfaces LibInterfaceSet;
  Configuration Config;

  if (!ReadFile("config/config.xml", Config))
  {
    return 1;
  }
  std::vector<string> LibList = Config.getLibList();
  for (const string &sLibNameI : LibList)
  {
    shared_ptr<LibInterface> pLibI = make_shared<LibInterface>(sLibNameI);
    LibInterfaceSet.insert(pair<string, shared_ptr<LibInterface>>(pLibI->GetCmdName(), pLibI));
  }
  if (argc < 2)
  {
    cerr << "Za mała ilość argumentów wywołania" << endl;
    return 1;
  }

  istringstream IStrm4Cmd;
  ExecPreprocesor(argv[1], IStrm4Cmd);
  cout << IStrm4Cmd.str() << endl;
  cout << "Port: " << PORT << endl;

  Scene Scn;
  Scn.configureScene(Config);

  //shared_ptr<MobileObj> pObj;
  //std::cout << "Check" << Scn.FindMobileObject("Podstawa", pObj) << '\n';

  int Socket4Sending;
  if (!OpenConnection(Socket4Sending))
  {
    cerr << "Nie można połączyć z serwerem!" << endl;
    return 3;
  }

  AccessGuard AccCtrl(Socket4Sending);
  const char *sConfigCmds =
      "Clear\n"
      "AddObj Name=Os RGB=(20,200,200) Scale=(0.5,0.5,2) Shift=(0,0,0.5)\n"
      "AddObj Name=Os.Wirnik RGB=(200,0,0) Scale=(3,1,0.2) Shift=(0,0,0.5) RotXYZ_deg=(0,0,0) Trans_m=(0,0,2)\n";

  std::lock_guard<mutex> Lock(AccCtrl.UseGuard());
  Send(AccCtrl.GetSocket(), sConfigCmds);
  //Sender ClientSender(Socket4Sending, &Scn);
  //thread Thread1(ExecActions, IStrm4Cmd, LibInterfaceSet, &Scn, &AccCtrl);
  //std::thread Thread1(Fun4Thread_ReadProgram_ExecCmds, IStrm4Cmd, LibInterfaceSet, &AccCtrl);
  ExecActions(IStrm4Cmd, LibInterfaceSet, &Scn, &AccCtrl);
  // std::vector<string> ObjList = Scn.getObjList();
  // ;
  // for (const string &sObjNameI : ObjList)
  // {
  //   cout << "   " << sObjNameI << "  " << endl;
  // }
  //-------------------------------------
  // Należy pamiętać o zamknięciu połączenia.
  // Bez tego serwer nie będzie reagował na
  // nowe połączenia.
  //
  Send(Socket4Sending, "Close\n");
  // ClientSender.CancelCountinueLooping();
  // Thread1.join();
  close(Socket4Sending);
  //-------------------------------------
}

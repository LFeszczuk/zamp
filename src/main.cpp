#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Set4Libinterfaces.hh"
#include "Scene.hh"
using namespace std;

#define LINE_SIZE 500
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

bool ExecActions(istream &AIStrm, Set4Libinterfaces &LibInterfaceSet)
{
  string CmdKey;

  while (AIStrm >> CmdKey)
  {
    cout << "Polecenie: " << CmdKey << endl;

    Set4Libinterfaces::const_iterator Iter = LibInterfaceSet.find(CmdKey);
    if (Iter == LibInterfaceSet.end())
    {
      cout << "Uwaga nieznane polecenie! :  " << CmdKey << endl;
      return false;
    }

    Interp4Command *pInterp = Iter->second->_pCreateCmd();
    if (!pInterp->ReadParams(AIStrm))
    {
      cout << "Nie można wczytać parametrów" << endl;
      delete pInterp;
      return false;
    }
    cout << "________Parametry:________" << endl;
    pInterp->PrintCmd();
    cout << endl;
    /*if (!pInterp->ExecCmd())
    {
      cout << "Nie można wykonaać polecenia" << endl;
      delete pInterp;
      return false;
      
    }
    */

    delete pInterp;
  }
  return true;
}

int main(int argc, char **argv)
{

  Set4Libinterfaces LibInterfaceSet;

  std::string set("libInterp4Set.so");
  std::string move("libInterp4Move.so");
  std::string pause("libInterp4Pause.so");
  std::string rotate("libInterp4Rotate.so");
  std::vector<string> Lib_Vector;
  Lib_Vector.push_back(set);
  Lib_Vector.push_back(move);
  Lib_Vector.push_back(pause);
  Lib_Vector.push_back(rotate);

  for (const string &s_LibN : Lib_Vector)
  {
    shared_ptr<LibInterface> p_Lib = make_shared<LibInterface>(s_LibN);
    LibInterfaceSet.insert(pair<string, shared_ptr<LibInterface>>(p_Lib->GetCmdName(), p_Lib));
  }

  if (argc < 2)
  {
    cerr << "Za mała ilość argumentów wywołania" << endl;
    return 1;
  }
  istringstream IStrm4Cmd;
  //Scene Scn;
  ExecPreprocesor(argv[1], IStrm4Cmd);
  cout << IStrm4Cmd.str() << endl;

  if (!ExecActions(IStrm4Cmd, LibInterfaceSet))
  {
    cerr << "Nie można wykonać akcji" << endl;
    return 2;
  }
}

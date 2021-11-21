  #include "LibInterface.hh"


LibInterface::LibInterface(const std::string LibName)
{
  void *pLibHnd = dlopen(LibName.c_str(),RTLD_LAZY);

  void *pFunCrea;

  std::cerr << "Ładowanie biblioteki: "   <<LibName<< std::endl;
  if (!pLibHnd) {
    std::cerr << "!!! Brak biblioteki: " <<LibName<< std::endl;
  }

  pFunCrea = dlsym(pLibHnd,"CreateCmd");
  if (!pFunCrea) {
    std::cerr << "!!! Nie znaleziono funkcji CreateCmd" << std::endl;
  }

  _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFunCrea);


  this->_LibHandler = pLibHnd;

  Interp4Command * pInterp= _pCreateCmd();
  this->_CmdName=pInterp->GetCmdName();
  delete pInterp;
}

LibInterface::~LibInterface()
{
  dlclose(this->_LibHandler);
}

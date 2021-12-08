#ifndef SCENE
#define SCENE
#include <vector>
#include <map>
#include <memory>
#include "SetOfMobObjects.hh"
#include "MobileObj.hh"
#include "AccessControl.hh"
#include "Configuration.hh"

typedef std::map<std::string, std::shared_ptr<MobileObj>> SetOfMobObjects;

class Scene 
{

  SetOfMobObjects _Set_of_mobile_Objects;

public:
  bool FindMobileObject(const char *sObjName, std::shared_ptr<MobileObj> &pObj)
  {
    SetOfMobObjects::const_iterator Iter = _Set_of_mobile_Objects.find(sObjName);
    if (Iter == _Set_of_mobile_Objects.end())
      return false;
    pObj = Iter->second;
    return true;
  }

  bool FindMobileObject(const std::string &rObjName, std::shared_ptr<MobileObj> &pObj)
  {
    SetOfMobObjects::const_iterator Iter = _Set_of_mobile_Objects.find(rObjName.c_str());
    if (Iter == _Set_of_mobile_Objects.end())
      return false;
    pObj = Iter->second;
    return true;
  }

  std::vector<std::string> getObjList() const
  {
    std::vector<std::string> VectorOfMobObjNames;
    for (const std::pair<std::string, std::shared_ptr<MobileObj>> &rObj : _Set_of_mobile_Objects)
    {
      VectorOfMobObjNames.push_back(rObj.first);
    }
    return VectorOfMobObjNames;
  }

    void configureScene(Configuration & rConf)
  {
    _Set_of_mobile_Objects=rConf.UseSetOfMobObjects();
  }
};

#endif
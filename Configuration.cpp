#include "Configuration.hh"

void Configuration::addMobObject(const char *pName, const char *paramShift, const char *paramScale, const char *paramRotXYZ_deg, const char *paramTrans_m, const char *paramRGB)
{
  std::shared_ptr<MobileObj> addedObj = std::make_shared<MobileObj>();
  double x, y, z, Roll, Pitch, Yaw, px, py, pz, sx, sy, sz;
  Vector3D sizeXYZ;
  Vector3D PosXYZ;
  std::string sName(pName);

  std::istringstream streamSizeXYZ;
  std::istringstream streamShiftXYZ;
  std::istringstream streamTransXYZ;
  std::istringstream streamRotXYZ;
  streamSizeXYZ.str(paramScale);
  streamTransXYZ.str(paramTrans_m);
  streamShiftXYZ.str(paramShift);
  streamRotXYZ.str(paramRotXYZ_deg);

  //Wczytanie rozmiarów obiektu
  streamSizeXYZ >> x >> y >> z;
  sizeXYZ[0] = x;
  sizeXYZ[1] = y;
  sizeXYZ[2] = z;

  streamTransXYZ >> px >> py >> pz;
  streamShiftXYZ >> sx >> sy >> sz;
  PosXYZ[0] = px + sx;
  PosXYZ[1] = py + sy;
  PosXYZ[2] = pz + sz;

streamRotXYZ >> Roll >> Pitch >> Yaw;


  addedObj->SetSize_m(sizeXYZ);
  addedObj->SetName(pName);
  addedObj->SetPosition_m(PosXYZ);
  addedObj->SetAng_Pitch_deg(Pitch);
  addedObj->SetAng_Yaw_deg(Yaw);
  addedObj->SetAng_Roll_deg(Roll);
  addedObj->SetColour(paramRGB);

  _SetMobObjects.insert(std::pair<std::string, std::shared_ptr<MobileObj>>(sName, addedObj));

}

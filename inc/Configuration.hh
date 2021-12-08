#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <memory>
#include "SetOfMobObjects.hh"
#include "MobileObj.hh"

/*!
 * \file
 * \brief Zawiera definicję klasy Configuration
 *
 * Plik zawiera definicję klasy Configuration, przechowującej
 * konfigurację wczytaną z pliku i pozwalającą ną na dostęp
 * do nich wewnątrz programu.
 */


/*!
 * \brief Klasa przechowujca konfigurację
 *
 * Przechowuje konfigurację programu, dotyczącą potrzebnych wtyczek
 * oraz parametrów obiektów na scenie, wczytaną z pliku XML
 */
class Configuration {
  /*!
   * \brief Zbiór nazw używanych bibliotek
   *
   * Pole przechowuje nazwy bibliotek, które mają być wczytane przez program
   */
  std::vector<std::string> _LibNameList;

  /*!
   * \brief Zbiór obiektów mobilnych
   *
   * Pole przechowuje obiekty mobilne wczytane ze konfiguracji,
   * które następnie zostaną przekazane do sceny.
   */
  SetOfMobObjects _SetMobObjects;


public:

  /*!
   * \brief Dodaje nazwę biblioteki do listy
   *
   * Zapisuje nową nazwę na końcu listy nazw blibliotek,
   * które mają zostać wczytane.
   * \param [in] rName - referencja do nazwy biblioteki
   */
  void addLibName(const char *pName)
  {
    std::string sName(pName);
    _LibNameList.push_back(pName);
  }

  /*!
   * \brief Dodaje obiekt mobilny do konfiguracji
   *
   * Zapisuje obiekt mobilny o wczytanych parametrach
   * do zbioru oraz wpisuje jego kolor do mapy kolorów.
   * \param [in] pName - wskaźnik na nazwę obiektu
   * \param [in] paramShift - strumień zawierający przesunięcie środka masy obiektu
   * \param [in] paramScale - strumień zawierający przeskalowanie rozmiaru obiektu
   * \param [in] paramRotXYZ_deg - strumień zawierający rotację o zadane kąty  obiektu
   * \param [in] paramTrans_m - strumień zawierający przesunięcie obiektu
   * \param [in] paramRGB - strumień zawięracjący kolor obiektu w formacie RGB
   */
  void addMobObject(const char *pName, const char * paramShift, const char * paramScale, const char * paramRotXYZ_deg ,const char * paramTrans_m,  const char * paramRGB);

  /*!
   * \brief Przekazuje listę bibliotek
   *
   * Przekazuje referencję na listę bibliotek, umożliwiając
   * tylko i wyłącznie jej odczyt
   * \return - Referencja na listę bibliotek (tylko do odczytu)
   */
  const std::vector<std::string> & getLibList() const
  {
      return _LibNameList;
  }

  /*!
   * \brief
   *
   * Przekazuje referencję do listy obiektów mobilnych.
   * Umożliwia jej modyfikację oraz skopiowanie jej
   * na potrzeby wczytania obiektów
   * \return - Referencja na zbiór obiektów mobilnych.
   */
  SetOfMobObjects & UseSetOfMobObjects()
  {
    return _SetMobObjects;
  }
};




#endif

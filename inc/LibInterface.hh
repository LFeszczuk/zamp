#ifndef LIBINTERFACE
#define LIBINTERFACE

/*!
  * \file
  * \brief Definicja klasy LibInterface
  *
  * Plik zawiera definicję klasy Libinterace, modelującej interfejs
  * dla pluginu wykonującego polecenie
  */

#include <dlfcn.h>
#include "Interp4Command.hh"

/*!
 * \brief Klasa modelująca interfejs dla pluginu
 *
 * Klasa LibInterface, służąca jako interfejs dla pluginów
 */
class LibInterface
{
  /*!
 * \brief Uchwyt do pluginów
 *
 * Wskaźnik służący jako uchwyt do pluginów
 */
  void *_LibHandler;
  /*!
 * \brief Nazwa polecenia
 *
 * Nazwa polecenia wykonywanego przez plugin
 */
  std::string _CmdName;

public:
  /*!
   * \brief Stworzenie interpretera
   *
   * Wskażnik do funkcji, tworzącej nową instancję klasy interpretera
   */
  Interp4Command *(*_pCreateCmd)(void);
  /*!
 * \brief return nazwy polecenia
 *
 * Zwraca nazwe polecenia, realizowanego przezz plugin
 */
  const std::string GetCmdName() { return _CmdName; }
  explicit LibInterface(const std::string LibPath);

  /*!
   * \brief Destruktor zamykający bibliotekę
   *
   * Zamyka wczytaną bibliotekę 
   */
  ~LibInterface();
};

#endif //LIBINTERFACE

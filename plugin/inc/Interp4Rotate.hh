#ifndef COMMAND4Rotate_HH
#define COMMAND4Rotate_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Rotate : public Interp4Command
{
  /*!
   *  \brief Nazwa objektu
   *
   *  Nazwa objektu dla którego ma zostać wykonane polecenie
   */
  std::string _Obj_name;
  /*!
   *  \brief Prędkość kątowa
   *
   *  Prędkość z jaką ma się poruszać obiekt 
   */
  double _V_ang;
  /*!
   *  \brief Nazwa osi
   *
   *  Oś wokół której ma się obracać obiekt
   */
  double _axis_name;
  /*!
   *  \brief Kąt obrotu
   *
   *  Kąt o jaki ma się obracać obiekt
   */
  double _Rot_ang;

public:
  /*!
   * \brief
   */
  Interp4Rotate();
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char *GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd(Scene *pScn, AccessGuard *pAccGuard) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream &Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command *CreateCmd();
};

#endif

#ifndef COMMAND4Set_HH
#define COMMAND4Set_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Set
 *
 * Plik zawiera definicję klasy Interp4Set ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Set : public Interp4Command
{
    /*!
   *  \brief Nazwa objektu
   *
   *  Nazwa objektu dla którego ma zostać wykonane polecenie
   */
    std::string _Obj_name;
    double wspx;
    double wspy;
    double _axis_x;
    double _axis_y;
    double _axis_z;

public:
    /*!
   * \brief
   */
    Interp4Set();
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
    virtual bool ExecCmd(Scene * pScn,AccessGuard *pAccGuard) const;
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

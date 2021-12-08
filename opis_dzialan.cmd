#define ROTATE_SPEED     30
/*
 *  Przykładowy zestaw poleceń
 */
  //Set   Podstawa 2 0 30 0 0   // Polozenie obiektu A 
  //Set   Podstawa.Ramie1 10 10 0 0 0  // Polozenie obiektu B
  Rotate Podstawa ROTATE_SPEED 40 20
  Pause 1000 /* Zawieszenie na 1 sek. */
  Move  Ob_A  10 10
  Rotate Podstawa.Ramie1 ROTATE_SPEED 60 20 /* Rotate i Move wykonywane razem */
  Move  Podstawa.Ramie1 10 20            /* powoduja jazde po luku         */
  Move  Podstawa.Ramie1 10 20            /* powoduja jazde po luku         */

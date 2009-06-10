#ifndef _LOCALIZEDSTRINGS_H_
#define _LOCALIZEDSTRINGS_H_ 

#include "version.h"

// This file includes the proper header file for this locale.
#ifndef LOCALE

  #error LOCALE is not define

#elif LOCALE == 1031
  
  #include "localizedstrings-de.h"  // German
  #define  CHARSETID 1252

#elif LOCALE == 1032
  
  #include "localizedstrings-gr.h"  // Greek
  #define  CHARSETID 1253

#elif LOCALE == 1033

  #include "localizedstrings-en.h"  // English
  #define  CHARSETID 1252

#elif LOCALE == 1034

  #include "localizedstrings-es.h"  // Spanish
  #define  CHARSETID 1252

#elif LOCALE == 1036

  #include "localizedstrings-fr.h"  // French
  #define  CHARSETID 1252

#elif LOCALE == 1040

  #include "localizedstrings-it.h"  // Italian
  #define  CHARSETID 1252

#elif LOCALE == 1049

  #include "localizedstrings-ru.h"  // Russian
  #define  CHARSETID 1251

#elif LOCALE == 2070

  #include "localizedstrings-pt.h"  // Portuguese
  #define  CHARSETID 1252

#elif LOCALE == 9999

  #include "localizedstrings-ps.h"  // Pseudoloc
  #define  CHARSETID 1252

#else

  #error LOCALE is an unknown value!

#endif 

#endif //  _LOCALIZEDSTRINGS_H_

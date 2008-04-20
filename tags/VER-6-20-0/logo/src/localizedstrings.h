#ifndef _LOCALIZEDSTRINGS_H_
#define _LOCALIZEDSTRINGS_H_ 

#include "version.h"

// This file includes the proper header file for this locale.
#ifndef LOCALE

  #error LOCALE is not define

#elif LOCALE == 1031
  
  #include "localizedstrings-de.h"  // German

#elif LOCALE == 1032
  
  #include "localizedstrings-gr.h"  // Greek

#elif LOCALE == 1033

  #include "localizedstrings-en.h"  // English

#elif LOCALE == 1034

  #include "localizedstrings-es.h"  // Spanish

#elif LOCALE == 1036

  #include "localizedstrings-fr.h"  // French

#elif LOCALE == 1040

  #include "localizedstrings-it.h"  // Italian

#elif LOCALE == 2070

  #include "localizedstrings-pt.h"  // Portuguese

#elif LOCALE == 9999

  #include "localizedstrings-ps.h"  // Pseudoloc

#else

  #error LOCALE is an unknown value!

#endif 

#endif //  _LOCALIZEDSTRINGS_H_

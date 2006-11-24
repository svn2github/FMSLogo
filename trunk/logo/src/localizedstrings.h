#ifndef _LOCALIZEDSTRINGS_H_
#define _LOCALIZEDSTRINGS_H_ 


#ifndef LOCALE

  // No locale is defined
  #error LOCALE is not define

#elif LOCALE == 1033

  // English-US
  #include "localizedstrings-en.h"

#elif LOCALE == 1036

  // French-France
  #include "localizedstrings-fr.h"

#else

  // LOCALE is defined to an unknown value
  #error LOCALE is an unknown value!

#endif 

#endif //  _LOCALIZEDSTRINGS_H_

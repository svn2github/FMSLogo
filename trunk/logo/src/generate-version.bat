if exist version.h del version.h
echo #define FMSLOGO_MAJOR_VERSION %1 >> version.h
echo #define FMSLOGO_MINOR_VERSION %2 >> version.h
echo #define FMSLOGO_MICRO_VERSION %3 >> version.h
if NOT "%4"=="" (
    echo #define FMSLOGO_PRIVATE_BUILD >> version.h
)
echo #define FMSLOGO_VERSION "%1.%2.%3%4" >> version.h

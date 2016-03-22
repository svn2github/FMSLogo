if exist "%~dp0version.h" del "%~dp0version.h"
echo #define FMSLOGO_MAJOR_VERSION %1 >> "%~dp0version.h"
echo #define FMSLOGO_MINOR_VERSION %2 >> "%~dp0version.h"
echo #define FMSLOGO_MICRO_VERSION %3 >> "%~dp0version.h"
if NOT "%4"=="" (
    echo #define FMSLOGO_PRIVATE_BUILD >> "%~dp0version.h"
)
echo #define FMSLOGO_VERSION "%1.%2.%3%4" >> "%~dp0version.h"

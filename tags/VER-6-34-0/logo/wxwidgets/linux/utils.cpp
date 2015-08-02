
#include <string.h>
#include <stdio.h>

void
SetConfigurationInt(
    const char *        Name,
    int                 Value
    )
{
}

int
GetConfigurationInt(
    const char *        Name,
    int                 DefaultValue
    )
{
    return DefaultValue;
}

void
SetConfigurationString(
    const char *        Name,
    const char *        Value
    )
{
}

void
GetConfigurationString(
    const char *        Name,
    char *              Value,
    size_t              ValueLength,
    const char *        DefaultValue
    )
{
    strcpy(Value, DefaultValue);
}

void
GetConfigurationQuadruple(
    const char *        Name,
    int *               Value1,
    int *               Value2,
    int *               Value3,
    int *               Value4
    )
{
    *Value1 = 0;
    *Value2 = 0;
    *Value3 = 0;
    *Value4 = 0;
}


void
SetConfigurationQuadruple(
    const char *        Name,
    int                 Value1,
    int                 Value2,
    int                 Value3,
    int                 Value4
    )
{
    char quadruple[256];

    sprintf(
        quadruple,
        "%d,%d,%d,%d",
        Value1,
        Value2,
        Value3,
        Value4);

    // Set the quadruple in the configuration.
    SetConfigurationString(
        Name,
        quadruple);
}


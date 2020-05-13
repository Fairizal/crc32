#include "crc.h"
#ifndef WIDTH
    #define WIDTH    (8 * sizeof(crc))
#endif
#define TOPBIT   (((crc)1) << (WIDTH - 1))

#if (REVERSED_DATA == TRUE)
    #define FP_reflect_DATA(_DATO)                      ((uint8_t)(FP_reflect((_DATO), 8)&0xFF))
    #define FP_reflect_CRCTableValue(_CRCTableValue)	((crc) FP_reflect((_CRCTableValue), WIDTH))
#else
    #define FP_reflect_DATA(_DATO)                      (_DATO)
    #define FP_reflect_CRCTableValue(_CRCTableValue)	(_CRCTableValue)

#endif

#if (CALCULATE_LOOKUPTABLE == TRUE)
static crc  A_crcLookupTable[256] = {0};
#endif

 #if (REVERSED_DATA == TRUE)
static crc FP_reflect(crc VF_dato, uint8_t VF_nBits)
{
    crc VP_reflection = 0;
    uint8_t VP_Pos_bit = 0;

    for (VP_Pos_bit = 0; VP_Pos_bit < VF_nBits; VP_Pos_bit++)
    {
        if ((VF_dato & 1) == 1)
        {
            VP_reflection |= (((crc)1) << ((VF_nBits - 1) - VP_Pos_bit));
        }

        VF_dato = (VF_dato >> 1);
    }
    return (VP_reflection);
}

#endif

static crc F_CRC_ObtenValorDeTabla(uint8_t VP_Pos_Tabla)
{
    crc VP_CRCTableValue = 0;
    uint8_t VP_Pos_bit = 0;

    VP_CRCTableValue = ((crc) FP_reflect_DATA(VP_Pos_Tabla)) << (WIDTH - 8);

    for (VP_Pos_bit = 0; VP_Pos_bit < 8; VP_Pos_bit++)
    {
        if (VP_CRCTableValue & TOPBIT)
        {
            VP_CRCTableValue = (VP_CRCTableValue << 1) ^ POLYNOMIAL;
        }
        else
        {
            VP_CRCTableValue = (VP_CRCTableValue << 1);
        }
    }
    return (FP_reflect_CRCTableValue(VP_CRCTableValue));
}

#if (CALCULATE_LOOKUPTABLE == TRUE)

void F_CRC_InicializaTabla(void)
{
    uint16_t VP_Pos_Array = 0;

    for (VP_Pos_Array = 0; VP_Pos_Array < 256; VP_Pos_Array++)
    {
        A_crcLookupTable[VP_Pos_Array] = F_CRC_ObtenValorDeTabla((uint8_t)(VP_Pos_Array &0xFF));

    }

}

crc F_CRC_CalculaCheckSum(uint8_t const AF_Datos[], uint16_t VF_nBytes)
{
    crc	VP_CRCTableValue = INITIAL_VALUE;
    uint16_t VP_bytes = 0;

    for (VP_bytes = 0; VP_bytes < VF_nBytes; VP_bytes++)
    {
        #if (REVERSED_DATA == TRUE)
            VP_CRCTableValue = (VP_CRCTableValue >> 8) ^ A_crcLookupTable[((uint8_t)(VP_CRCTableValue & 0xFF)) ^ AF_Datos[VP_bytes]];
        #else
            VP_CRCTableValue = (VP_CRCTableValue << 8) ^ A_crcLookupTable[((uint8_t)((VP_CRCTableValue >> (WIDTH - 8)) & 0xFF)) ^ AF_Datos[VP_bytes]];
        #endif
    }

	if ((8 * sizeof(crc)) > WIDTH)
	{
		VP_CRCTableValue = VP_CRCTableValue & ((((crc)(1)) << WIDTH) - 1);
	}

    #if (REVERSED_OUT == FALSE)
        return (VP_CRCTableValue ^ FINAL_XOR_VALUE);
    #else
        return (~VP_CRCTableValue ^ FINAL_XOR_VALUE);
    #endif

}
#else

crc F_CRC_CalculaCheckSum(uint8_t const AF_Datos[], uint16_t VF_nBytes)
{
    crc	VP_CRCTableValue = INITIAL_VALUE;
    int16_t VP_bytes = 0;

    for (VP_bytes = 0; VP_bytes < VF_nBytes; VP_bytes++)
    {
        #if (REVERSED_DATA == TRUE)
            VP_CRCTableValue = (VP_CRCTableValue >> 8) ^ F_CRC_ObtenValorDeTabla(((uint8_t)(VP_CRCTableValue & 0xFF)) ^ AF_Datos[VP_bytes]);
        #else
            VP_CRCTableValue = (VP_CRCTableValue << 8) ^ F_CRC_ObtenValorDeTabla(((uint8_t)((VP_CRCTableValue >> (WIDTH - 8)) & 0xFF)) ^ AF_Datos[VP_bytes]);
        #endif
    }

	if ((8 * sizeof(crc)) > WIDTH)
	{
		VP_CRCTableValue = VP_CRCTableValue & ((((crc)(1)) << WIDTH) - 1);
	}

    #if (REVERSED_OUT == FALSE)
        return (VP_CRCTableValue ^ FINAL_XOR_VALUE);
    #else
        return (~VP_CRCTableValue ^ FINAL_XOR_VALUE);
    #endif

}

#endif


#ifndef _crc_h
#define _crc_h
#include <stdint.h>
#define TRUE    1
#define FALSE   0
#define CRC_32
#define CALCULATE_LOOKUPTABLE   FALSE
#if defined(CRC_8)

typedef uint8_t crc;

#define POLYNOMIAL		0x07
#define INITIAL_VALUE           0
#define FINAL_XOR_VALUE		0
#define REVERSED_DATA           FALSE
#define REVERSED_OUT            FALSE

#elif defined(CRC_CCITT)

typedef uint16_t crc;

#define POLYNOMIAL		0x1021
#define INITIAL_VALUE           0xFFFF
#define FINAL_XOR_VALUE		0
#define REVERSED_DATA           FALSE
#define REVERSED_OUT            FALSE

#elif defined(MODBUS)

typedef uint16_t crc;

#define POLYNOMIAL		0x8005
#define INITIAL_VALUE           0xFFFF
#define FINAL_XOR_VALUE		0
#define REVERSED_DATA           TRUE
#define REVERSED_OUT            FALSE



#elif defined(CRC_16)

typedef uint16_t crc;

#define POLYNOMIAL		0x8005
#define INITIAL_VALUE           0x0000
#define FINAL_XOR_VALUE		0x0000
#define REVERSED_DATA           TRUE
#define REVERSED_OUT            FALSE

#elif defined(CRC_24)
typedef uint32_t crc;

#define POLYNOMIAL		0x864CFB
#define INITIAL_VALUE           0xB704CE
#define FINAL_XOR_VALUE		0x000000
#define REVERSED_DATA           FALSE
#define REVERSED_OUT            FALSE
#define WIDTH                   (24)

#elif defined(CRC_32)

typedef uint32_t crc;

#define POLYNOMIAL		0x04C11DB7
#define INITIAL_VALUE           0xFFFFFFFF
#define FINAL_XOR_VALUE		0xFFFFFFFF
#define REVERSED_DATA           TRUE
#define REVERSED_OUT            FALSE


#elif defined(CRC_32_BZIP2)

typedef uint32_t crc;

#define POLYNOMIAL		0x04C11DB7
#define INITIAL_VALUE           0xFFFFFFFF
#define FINAL_XOR_VALUE		0
#define REVERSED_DATA           FALSE
#define REVERSED_OUT            TRUE


#elif defined(CRC_64_JONES)

typedef uint64_t crc;

#define POLYNOMIAL		0xAD93D23594C935A9
#define INITIAL_VALUE           0xFFFFFFFFFFFFFFFF
#define FINAL_XOR_VALUE		0
#define REVERSED_DATA           TRUE
#define REVERSED_OUT            FALSE


#else

#error "Debes definir un algoritmo CRC"
#error "You should define at least one algorithm"

#endif

#if (CALCULATE_LOOKUPTABLE == FALSE)
    #define F_CRC_InicializaTabla()
#else
    void F_CRC_InicializaTabla(void);
#endif
crc F_CRC_CalculaCheckSum(uint8_t const AF_Datos[], uint16_t VF_nBytes);



#endif

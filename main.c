#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crc.h"
#include "crc.c"

int main()
{

    int8_t A_Texto[40];
    crc CRC_Result = 0;

	printf("Masukan nilai yang diinginkan : ");

	fgets(A_Texto, 40, stdin);


    F_CRC_InicializaTabla();
    CRC_Result = F_CRC_CalculaCheckSum(A_Texto, strlen(A_Texto)-1);
	printf("Hasil : 0x%X", CRC_Result);
	getchar();
    return 0;
}


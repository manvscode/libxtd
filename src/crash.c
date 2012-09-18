#include "utility.h"

void crash( void )
{
	char* p_ptr = 0x00000bad;
	*p_ptr = 1234567890;
}

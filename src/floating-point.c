#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "xtd/floating-point.h"

bool float_is_equal( float a, float b )
{
	return fabsf(a - b) < FLT_EPSILON;
}

bool double_is_equal( double a, double b )
{
	return fabs(a - b) < DBL_EPSILON;
}

bool long_double_is_equal( long double a, long double b )
{
	return fabsl(a - b) < LDBL_EPSILON;
}

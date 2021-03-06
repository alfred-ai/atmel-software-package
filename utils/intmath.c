#include "intmath.h"

#ifndef HAVE_BSD_FLS
int fls(int value)
{
	int i;

	for (i = 31; i >= 0; i--)
		if (value & (1 << i))
			return i + 1;

	return 0;
}
#endif

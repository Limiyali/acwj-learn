#include "types.h"
#include "defs.h"
#include "gen.h"

int type_compatible(int *left, int *right, int onlyright)
{
	int leftsize, rightsize;

	// Same types, they are compatible
	if (*left == *right) {
		*left = *right = 0;
		return (1);
	}
	// Get the sizes for each type
	leftsize = genprimsize(*left);
	rightsize = genprimsize(*right);

	// Types with zero size are not
	// not compatible with anything
	if ((leftsize == 0) || (rightsize == 0))
		return (0);

	// Widen types as required
	if (leftsize < rightsize) {
		*left = A_WIDEN;
		*right = 0;
		return (1);
	}
	if (rightsize < leftsize) {
		if (onlyright)
			return (0);
		*left = 0;
		*right = A_WIDEN;
		return (1);
	}
	// Anything remaining is the same size
	// and thus compatible
	*left = *right = 0;
	return (1);
}
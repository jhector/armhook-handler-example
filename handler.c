#include "hook.h"

int8_t handler_get_value(struct hook_data *h_data)
{
	unsigned int dummy;

	void *data = (void*)h_data->r0; /* first argument */
	unsigned int *value = (unsigned int*)h_data->r1; /* second argument */

	/* we want the function to return 0xdeadbeef as the value */
	*value = 0xdeadbeef;

	/* reroute the first argument for the hooked function */
	h_data->r1 = (uint32_t)&dummy;
	
	/* let the hooked function continue, if we were to skip it return 1 */
	return 0;
}

#include "wavgen.h"

float	freq_swipe(uint32_t i, float low, float high)
{
	return low + ((float)i / (float)NB_SAMPLES) * (high - low);
}

float	freq_fuck(uint32_t i, float low, float high)
{
	return low + fmod((((float)i / (float)NB_SAMPLES) * 10.), 0.2) * (high - low);
}

float	phase_swipe(uint32_t i)
{
	return (-M_PI) + ((float)i / (float)NB_SAMPLES) * (M_PI * 2.);
}

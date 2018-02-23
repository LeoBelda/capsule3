#include "wavgen.h"

float	gen_sin(float t, float freq, float a, float phase)
{
	return (a * sinf(freq * 2. * M_PI * t + phase));
}

float	gen_fuck(float t, float freq, float a, float phase)
{
	return fabs(a * sinf(freq * log(fmod(t, 100.)) * M_PI * t + phase));
}

float	gen_triangle(float t, float freq, float a, float phase)
{
	(void)phase;
	return (2 * a * freq * (fabs(fmod(t, 1 / freq) - 1. / (freq * 2.)) - 1. / (freq * 4.)));
}

float	gen_square(float t, float freq, float a, float phase)
{
	return (gen_sin(t, freq, a, phase) > 0. ? a : -a);
	//return (2 *  floorf(freq * t) - floorf(2 * freq * t) + 1);
}

float	gen_sawtooth(float t, float freq, float a, float phase)
{
	(void) phase;
	return (2 * a * (t * freq - floorf(0.5 + t * freq)));
}

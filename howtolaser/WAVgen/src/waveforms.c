#include "wavgen.h"

float	gen_sin(float t, float freq, float a, float phase)
{
	return (a * sinf(freq * 2. * M_PI * t + phase));
}

float	gen_triangle(float t, float freq, float a, float phase)
{
	return (4 * a * freq * (fabs(fmod(t + 0.75 / freq + phase / (2*M_PI*freq),
					1 / freq) - 1. / (freq * 2.)) - 1. / (freq * 4.)));
}

float	gen_square(float t, float freq, float a, float phase)
{
	return (gen_sin(t, freq, a, phase) > 0. ? a : -a);
	//return (2 *  floorf(freq * t) - floorf(2 * freq * t) + 1);
}

float	gen_sawtooth(float t, float freq, float a, float phase)
{
	return (2 * a * ((t + phase / (2*M_PI*freq)) * freq -
				floorf(0.5 + (t + phase / (2*M_PI*freq)) * freq)));
}

//////////////////////// |||              ||| //////////////////////
//////////////////////// vvv refacto part vvv //////////////////////

float	curv_sin(float time, t_acurv *curv)
{
	return (curv->amp * sin(time * 2 * M_PI + curv->phase));
}

float	curv_tri(float time, t_acurv *curv)
{
	return (4 *curv->amp * curv->freq * (fabs(fmod(time + 0.75 / curv->freq + curv->phase / (2*M_PI*curv->freq),
					1 / curv->freq) - 1. / (curv->freq * 2.)) - 1. / (curv->freq * 4.)));
}

float	curv_sqr(float time, t_acurv *curv)
{
	return (gen_sin(time, curv->freq,curv->amp, curv->phase) > 0. ?curv->amp : -curv->amp);
}

float	curv_sawth(float time, t_acurv *curv)
{
	return (2 *curv->amp * ((time + curv->phase / (2*M_PI*curv->freq)) * curv->freq -
				floorf(0.5 + (time + curv->phase / (2*M_PI*curv->freq)) * curv->freq)));
}

void	waveforme_init(float (*f[NB_WAVEFORMS])(float time, t_acurv *curv))
{
	f[0] = curv_sin;
	f[1] = curv_tri;
	f[2] = curv_sqr;
	f[3] = curv_sawth;
}

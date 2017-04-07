// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#ifndef pong_rng_h
#define pong_rng_h
#include <stdint.h>

class Rng
{
public:
	Rng () : _seed(1) {}
	uint32_t random31b ()
	{
		uint32_t lo = parkmillercarta * (_seed & 0xFFFF);
		uint32_t hi = parkmillercarta * (_seed >> 16);
		lo += (hi & 0x7FFF) << 16;
		lo += hi >> 15;
		if (lo > 0x7FFFFFFF) lo -= 0x7FFFFFFF;
		return (_seed = lo);
	}
	bool random1b ()
	{
		return ((random31b() & 0x1) == 0x1);
	}
	void seed (uint32_t seed)
	{
		if (seed == 0) _seed = 1;
		else _seed = seed;
	}
private:
	uint32_t _seed;
	static uint32_t const parkmillercarta = 16807;
	// Alternaltive: 48271
};

#endif // pong_rng_h

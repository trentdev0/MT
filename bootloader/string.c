#include <stdint.h>

#include "string.h"

void *memcpy(void *Destination, const void *Source, size_t Number)
{
	uint8_t *PointerDestination = (uint8_t *)Destination;
	const uint8_t *PointerSource = (const uint8_t *)Source;

	for(size_t i = 0; i < Number; i++)
	{
		PointerDestination[i] = PointerSource[i];
	}

	return Destination;
}

void *memset(void *String, int Character, size_t Number)
{
	uint8_t *Pointer = (uint8_t *)String;

	for(size_t i = 0; i < Number; i++)
	{
		Pointer[i] = (uint8_t)Character;
	}

	return String;
}
 
void *memmove(void *Destination, const void *Source, size_t Number)
{
	uint8_t *PointerDestinatoon = (uint8_t *)Destination;
	const uint8_t *PointerSource = (const uint8_t *)Source;

	if(Source > Destination)
	{
		for(size_t i = 0; i < Number; i++)
		{
			PointerDestinatoon[i] = PointerSource[i];
		}
	}
	else if(Source < Destination)
	{
		for(size_t i = Number; i > 0; i--)
		{
			PointerDestinatoon[i - 1] = PointerSource[i - 1];
		}
	}

	return Destination;
}

int memcmp(const void *String0, const void *String1, size_t Number)
{
	const uint8_t *Pointer0 = (const uint8_t *)String0;
	const uint8_t *Pointer1 = (const uint8_t *)String1;

	for(size_t i = 0; i < Number; i++)
	{
		if(Pointer0[i] != Pointer1[i])
		{
			return Pointer0[i] < Pointer1[i] ? -1 : 1;
		}
	}

	return 0;
}
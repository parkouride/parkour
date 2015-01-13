#pragma once

#include "types.h"

namespace ledvm {

struct Color_t
{
	const uint8_t red;
	const uint8_t green;
	const uint8_t blue;

	Color_t(const uint8_t c[3])
	  : red{c[0]}
	  , green{c[1]}
	  , blue{c[2]}
	{
	}

        Color_t(const uint8_t r, uint8_t g, uint8_t b)
          : red{r}
          , green{g}
          , blue{b}
        {
        }
};

using Color = struct Color_t;

} // namespace ledvm

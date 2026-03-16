#pragma once

#define MU_ATTR(X) __attribute__((X))
#define MU_INLINE inline MU_ATTR(always_inline)

#define MU_SIZE(size, count) (size * count)

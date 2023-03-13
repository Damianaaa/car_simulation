#include "engine/math/hdr/numerical_utilities.h"

namespace math
{

static_assert(fEqual(0.f, 0.f));
static_assert(fEqual(0.01f, 0.01f));
static_assert(!fEqual(0.f, 0.01f));
static_assert(!fEqual(0.01f, 0.f));

static_assert(fGEqual(0.01f, 0.f));
static_assert(fGEqual(0.f, 0.f));
static_assert(!fGEqual(0.0f, 0.01f));

static_assert(fLEqual(0.f, 0.01f));
static_assert(fLEqual(0.f, 0.f));
static_assert(!fLEqual(0.01f, 0.f));
    
} // namespace math

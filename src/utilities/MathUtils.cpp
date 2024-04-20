#include "MathUtils.h"

float MathUtils::lerp(float start, float end, float t)
{
    return start + t * (end - start);
}

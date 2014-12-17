#pragma once

inline float lerp(float min, float max, float t)
{
	return min + t*(max-min); //min * (1 - t) + max * (t)
}
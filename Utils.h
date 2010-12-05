#ifndef UTILS_H
#define UTILS_H


class Utils
{
public:
	static const float PI = 3.14159265359;
	static inline float deg2rad(float angle)
	{
		return angle * (2 * Utils::PI) / 360.0;
	}

	static inline float rad2deg(float angle)
	{
		return (angle * 360.0) / (2 * Utils::PI);
	}
};


#endif // UTILS_H

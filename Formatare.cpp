#include "Formatare.h"
#include <math.h>

std::string Formatare::ConvertesteReal(float nr)
{
	std::string text = "";
	bool negativ = nr < 0;

	nr = abs(nr);
	int intreg = floor(nr);
	int fractional = abs(intreg - nr) * 100;

	if (negativ)
	{
		text += "-";
	}

	text += std::to_string(intreg);

	if (fractional != 0)
	{
		text += ("." + std::to_string(fractional));
	}

	return text;
}
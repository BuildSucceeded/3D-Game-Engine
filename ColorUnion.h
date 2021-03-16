#pragma once
union ColorUnion {
	int color;
	struct ColorItems {
		unsigned char blue;
		unsigned char green;
		unsigned char red;
		unsigned char alpha;
	} colorItems;

	static ColorUnion Create(int color)
	{
		ColorUnion toReturn;
		toReturn.color = color;
		return toReturn;
	}

	static ColorUnion Create(char red, char green, char blue, char alpha)
	{
		ColorUnion toReturn;
		toReturn.colorItems.red = red;
		toReturn.colorItems.green = green;
		toReturn.colorItems.blue = blue;
		toReturn.colorItems.alpha = alpha;
		return toReturn;
	}
};
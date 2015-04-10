#include "RandomColors.h"

Core::RGB RandomColors::varyColor(Core::RGB color, int variance)
{
	r=GetRValue(color);
	r=r+int(myRand.randomInRange(-(float)variance,(float)variance+1));
	r=(r<0)?0:r;
	r=(r>255)?255:r;

	g=GetGValue(color);
	g=g+int(myRand.randomInRange(-(float)variance,(float)variance+1));
	g=(g<0)?0:g;
	g=(g>255)?255:g;

	b=GetBValue(color);
	b=b+int(myRand.randomInRange(-(float)variance,(float)variance+1));
	b=(b<0)?0:b;
	b=(b>255)?255:b;

	return RGB(r,g,b);
}

Core::RGB RandomColors::brightness(Core::RGB color, float brightValue)
{
	int red = int(GetRValue(color)*brightValue);
	red=red<=0?1:red;
	red=red>255?255:red;

	int green = int(GetGValue(color)*brightValue);
	green=green<=0?1:green;
	green=green>255?255:green;

	int blue = int(GetBValue(color)*brightValue);
	blue=blue<=0?1:blue;
	blue=blue>255?255:blue;

	return RGB(red, green, blue);
}
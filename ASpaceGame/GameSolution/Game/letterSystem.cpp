#include "letterSystem.h"

void letterSystem::drawText(Core::Graphics& graphics, float thickness, Core::RGB color, 
							const char* text, float size, float gap, int currentLetter, Vector2D position)
{
	int currentLet = currentLetter;
	graphics.SetColor(color);
	for(unsigned int i=0; i < strlen(text); i++)
	{
		switch(text[i])
		{
		case('A'):
		case('a'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawHorizontalBar(graphics, thickness, size - thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness + (size-thickness*2), position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness*2, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y+thickness+(size-thickness*2)/3));
			currentLet++;
			break;
		case('B'):
		case('b'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+(size-3*thickness)/2+thickness));
			DrawVerticalBar(graphics, thickness, (size-2*thickness)/3, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+thickness));
			DrawVerticalBar(graphics, thickness, 2*(size-2*thickness)/3-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+(size-3*thickness)/2+2*thickness));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+size-thickness));
			currentLet++;
			break;
		case('C'):
		case('c'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y + size-thickness));
			currentLet++;
			break;
		case('D'):
		case('d'):
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y + size-thickness));
			DrawVerticalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y + thickness));
			currentLet++;
			break;
		case('E'):
		case('e'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size,Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size,Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('F'):
		case('f'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size,Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y ));
			currentLet++;
			break;
		case('G'):
		case('g'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y + size-thickness));
			DrawVerticalBar(graphics, thickness, size/2, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y + size/2));
			DrawHorizontalBar(graphics, thickness, size/2, Vector2D(position.x+size*currentLet+gap*currentLet+(size/2), position.y + size/2.5f));
			currentLet++;
			break;
		case('H'):
		case('h'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+(size-thickness)/2));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y));
			currentLet++;
			break;
		case('I'):
		case('i'):
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2,position.y+thickness));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+size-thickness));
			currentLet++;
			break;
		case('J'):
		case('j'):
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2,position.y+thickness));
			DrawHorizontalBar(graphics, thickness, ((size-thickness)/2)+thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y+size-thickness));
			DrawVerticalBar(graphics, thickness, size/3, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*(size/3)));
			currentLet++;
			break;
		case('K'):
		case('k'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y+size/2.5f),
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y+size/2.5f),
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+size-thickness));
			currentLet++;
			break;
		case('L'):
		case('l'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+size-thickness));
			currentLet++;
			break;
		case('M'):
		case('m'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size/2, position.y+size/2));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size/2-1.0f, position.y+size/2));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y));
			currentLet++;
			break;
		case('N'):
		case('n'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y),
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+size-thickness));
			currentLet++;
			break;
		case('O'):
		case('o'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y + size-thickness));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y + thickness));
			currentLet++;
			break;
		case('P'):
		case('p'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+(size-2*thickness)/3+thickness));
			DrawVerticalBar(graphics, thickness, (size-2*thickness)/3, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+thickness));
			currentLet++;
			break;
		case('Q'):
		case('q'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet,position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y + size-thickness));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y + thickness));
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+currentLet*size+currentLet*gap+(size-2*thickness), position.y+(size-2*thickness)),
				Vector2D(position.x+currentLet*size+currentLet*gap+size+thickness/2, position.y+size+thickness/2));
			currentLet++;
			break;
		case('R'):
		case('r'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+(size-2*thickness)/3+thickness));
			DrawVerticalBar(graphics, thickness, (size-2*thickness)/3, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+thickness));
			DrawVerticalBar(graphics, thickness, 2*(size-2*thickness)/3, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y+(size-2*thickness)/3+2*thickness));
			currentLet++;
			break;
		case('S'):
		case('s'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('T'):
		case('t'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawVerticalBar(graphics, thickness, size-thickness, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2,position.y+thickness));
			currentLet++;
			break;
		case('U'):
		case('u'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet,position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness,position.y+size-thickness));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness,position.y));
			currentLet++;
			break;
		case('V'):
		case('v'):
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet, position.y), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size/2, position.y+size-thickness));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size/2, position.y+size-thickness), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size, position.y));
			currentLet++;
			break;
		case('W'):
		case('w'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+currentLet*size+currentLet*gap, position.y));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y+size-thickness), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size/2, position.y+size/2.5f));
			DrawDiagonalBar(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size/2, position.y+size/2.5f), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y+size-thickness));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+currentLet*size+currentLet*gap+size-thickness, position.y));
			currentLet++;
			break;
		case('X'):
		case('x'):
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet, position.y), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y+size));
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+size), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y));
			currentLet++;
			break;
		case('Y'):
		case('y'):
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet, position.y), 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y+size/2));
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y+size/2), 
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y));
			DrawVerticalBar(graphics, thickness, (size/2), Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y+size/2));
			currentLet++;
			break;
		case('Z'):
		case('z'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawDiagonalBarX(graphics, thickness, Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y+thickness),
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+ size - thickness));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+size-thickness));
			currentLet++;
			break;
		case('0'):
			DrawVerticalBar(graphics, thickness, size, 
				Vector2D(position.x+currentLet*size+currentLet*gap, position.y));
			DrawVerticalBar(graphics, thickness, size, 
				Vector2D(position.x+currentLet*size+currentLet*gap+(size-thickness), position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, 
				Vector2D(position.x+currentLet*size+currentLet*gap+thickness, position.y));
			DrawHorizontalBar(graphics, thickness, size-2*thickness, 
				Vector2D(position.x+currentLet*size+currentLet*gap+thickness, position.y+(size-thickness)));
			currentLet++;
			break;
		case('1'):
			DrawHorizontalBar(graphics, thickness, (size-thickness)/4, 
				Vector2D(position.x+currentLet*size+currentLet*gap+ (size-thickness)/4, position.y+(size-thickness)/4));
			DrawVerticalBar(graphics, thickness, size-thickness, 
				Vector2D(position.x+currentLet*size+currentLet*gap+((size-thickness)/2), position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness*2,
				Vector2D(position.x+currentLet*size+currentLet*gap+(size-thickness)/4, position.y+size-thickness));
			currentLet++;
			break;
		case('2'):
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('3'):
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('4'):
			DrawVerticalBar(graphics, thickness, ((size-thickness)/2)+thickness, 
				Vector2D(position.x+currentLet*size+currentLet*gap, position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness*2, 
				Vector2D(position.x+currentLet*size+currentLet*gap+thickness, position.y+((size-thickness)/2)));
			DrawVerticalBar(graphics, thickness, size,
				Vector2D(position.x+currentLet*size+currentLet*gap+(size-thickness), position.y));
			currentLet++;
			break;
		case('5'):
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('6'):
			DrawVerticalBar(graphics, thickness, size,
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness, 
				Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness,
				Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y+((size-3*thickness)/2)+thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness,
				Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y+(size-3*thickness)+2*thickness));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2,
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y+((size-3*thickness)/2)+2*thickness));
			currentLet++;
			break;
		case('7'):
			DrawVerticalBar(graphics, thickness, size,
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness,
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			currentLet++;
			break;
		case('8'):
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+size-thickness, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness*2+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, 
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + 2*((size-3*thickness)/2)));
			currentLet++;
			break;
		case('9'):
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2+2*thickness,
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y));
			DrawHorizontalBar(graphics, thickness, size-thickness, 
				Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2,
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y+thickness));
			DrawHorizontalBar(graphics, thickness, size-thickness,
				Vector2D(position.x+size*currentLet+gap*currentLet+thickness, position.y+((size-3*thickness)/2)+thickness));
			DrawHorizontalBar(graphics, thickness, size,
				Vector2D(position.x+size*currentLet+gap*currentLet, position.y+(size-3*thickness)+2*thickness));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2,
				Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y+((size-3*thickness)/2)+2*thickness));
			currentLet++;
			break;
		case('!'):
			DrawVerticalBar(graphics, thickness, 3*size/5, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y));
			DrawVerticalBar(graphics, thickness, size/5, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y+4*(size/5)));
			currentLet++;
			break;
		case(':'):
			DrawVerticalBar(graphics, thickness, thickness, Vector2D(position.x+size*currentLet+gap*currentLet + ((size-thickness)/2), position.y + ((size-2*thickness)/3)));
			DrawVerticalBar(graphics, thickness, thickness, Vector2D(position.x+size*currentLet+gap*currentLet + ((size-thickness)/2), position.y + (2*(size-2*thickness)/3)+thickness));
			currentLet++;
			break;
		case('.'):
			DrawVerticalBar(graphics, thickness, size/5, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y+4*(size/5)));
			currentLet++;
			break;
		case('$'):
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness/2));
			DrawVerticalBar(graphics, thickness, (size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet, position.y + thickness));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+thickness+((size-3*thickness)/2)));
			DrawVerticalBar(graphics, thickness,(size-3*thickness)/2, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness), position.y + thickness*2+((size-3*thickness)/2)));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+2*thickness + (2*((size-3*thickness)/2)-thickness/2)));
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+(size/2.5f), position.y));
			currentLet++;
			break;
		case('+'):
			DrawVerticalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet+(size-thickness)/2, position.y));
			DrawHorizontalBar(graphics, thickness, size, Vector2D(position.x+size*currentLet+gap*currentLet, position.y+(size-thickness)/2));
			currentLet++;
			break;
		case(' '):
			if(currentLet != 0)
			{
				currentLet++;
			}
			break;
		}
	}
}

void letterSystem::DrawHorizontalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{

	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(startPosition.x + size, startPosition.y+i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void letterSystem::DrawVerticalBar(Core::Graphics& graphics, float thickness, float size, Vector2D startPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x + i, startPosition.y);
		Vector2D end(startPosition.x + i, startPosition.y+size);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void letterSystem::DrawDiagonalBar(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x, startPosition.y + i);
		Vector2D end(endPosition.x, endPosition.y +i);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

void letterSystem::DrawDiagonalBarX(Core::Graphics& graphics, float thickness, Vector2D startPosition, Vector2D endPosition)
{
	for(int i=0; i<thickness; i++)
	{
		Vector2D start(startPosition.x+i, startPosition.y);
		Vector2D end(endPosition.x+i, endPosition.y);
		graphics.DrawLine(start.x, start.y, end.x, end.y);
	}
}

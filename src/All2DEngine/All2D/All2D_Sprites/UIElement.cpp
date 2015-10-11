// UIElement.cpp: Implementierung der Klasse UIElement.
//
//////////////////////////////////////////////////////////////////////

#include "UIElement.h"
#include "../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIElement::UIElement() :Position()
{
	focus = false;
	mouseIn = false;
	enabled = true;
	blnAbsolutePlacing=false;
}

UIElement::~UIElement()
{

}

void UIElement::setPosition(int x, int y, int w, int h)
{
	Position.setPosition(x,y,w,h);
}

void UIElement::setPosition(Rect p)
{
	Position.setPosition(p.x1,p.y1,p.x2,p.y2);
}

Rect UIElement::getPosition()
{
	return Position;
}
//Hier wird erst gecheckt, ob das Element relativ zum Screen, oder virtuellem Desktop liegt..
bool UIElement::isInside(int x, int y)
{
	// focus is true when inside
	focus = Position.isInside(x,y);
	return focus;
}


bool UIElement::handleEvent(Event *evt)
{
	if (enabled) {
		// toggle inside depending on mousemove
		if (evt->Type == MM_MOUSEMOVE) {
			// set mouseIn according to focus, check if it is relative, or absolute positioned
			Point p = All2D_System::extractMouseCoords(evt);
			mouseIn = isInside(p.x,p.y);
		}
	}

	return true;
}

bool UIElement::getFocus() {
	return focus;
}

bool UIElement::mouseInside() {
	return mouseIn;
}

bool UIElement::isEnabled() {
	return enabled;
}

void UIElement::setEnabled(bool e) {
	enabled = e;
}


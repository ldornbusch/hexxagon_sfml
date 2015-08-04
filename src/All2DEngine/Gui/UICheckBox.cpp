// UICheckBox.cpp: Implementierung der Klasse UICheckBox.
// Die CheckBox kommt standard maessig mit dem GFX aus All2D_UI
// Kann aber einfach angepasst werden, indem ein eigenes Bild gecloned wird.
// ebenso ist das HoverImage zu klonen. DABEI ist jedoch zu BEACHTEN, dass
// die Koordinaten der SrcRects fuer beide Bilder (mit und ohne Hover) gleich sein muessen
// deswegen muss ggf. das HoverImage an die richtige Position geklont werden.
// wie im Standard Konstruktor gezeigt
//////////////////////////////////////////////////////////////////////

#include "UICheckBox.h"
#include "../All2D/All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UICheckBox::UICheckBox()
{
	cloneImage(All2D_System::UIElements);

	setPosition(Rect(0,0,8,8));
	rctCheckedArea.setPosition(8,0,8,8);
	rctUncheckedArea.setPosition(0,0,8,8);

	Image Tmp;
	Tmp.cloneImage(*this,Rect(0,16,16,16));
	setHoverImage(Tmp);
	setBlitMode(IMAGE_BLTMODE_TRANS);
	setHoverBlitMode(IMAGE_BLTMODE_TRANS);
	blnChecked=true;
}

UICheckBox::UICheckBox(bool flag)
{
	UICheckBox();
	blnChecked=flag;
}

UICheckBox::~UICheckBox()
{

}

void UICheckBox::leftClick()
{
	blnChecked=!blnChecked;
}

bool UICheckBox::paint(Image &backBuffer)
{
	if (blnChecked)
		setSrcRect(rctCheckedArea);
	else
		setSrcRect(rctUncheckedArea);

	return UIHoverButton::paint(backBuffer);
}

void UICheckBox::setSrcRect(Rect tmp)
{
	UIHoverButton::setSrcRect(tmp);
	HoverImage.setSrcRect(tmp);
}

void UICheckBox::setValue(value val)
{
	blnChecked=(val.second==1);
}

value UICheckBox::getValue()
{
	return value("",(int)blnChecked);
}
string UICheckBox::getName()
{
	return UIHoverButton::getName();
}
void UICheckBox::setCheckArea(Rect rct)
{	rctCheckedArea=rct;}

void UICheckBox::setUncheckArea(Rect rct)
{	rctUncheckedArea=rct;}

#include <All2D/All2DEngine/All2D/All2D_System.h>
#include "Hexxagon/HexxagonGameController.h"

int main()
{
	All2D_System::UIElements.loadImage("data/All2D_UI.png");
	All2D_System::SystemFont.cloneImage(All2D_System::UIElements,Rect(0,32,320,128));
	All2D_System::SystemFont.FontInit(16,16,10,"0123456789.,+-*/!?$&()§ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz:[]");

	HexxagonGameController Hexxagon;
    Image icon;
    icon.loadImage("data/icon.png");
	All2D_init(640,480,"Hexxagon by Hexerei, (c) 2002", &icon);

    All2D_main(Hexxagon);

}


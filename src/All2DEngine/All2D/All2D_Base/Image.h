// Image.h: Schnittstelle für die Klasse Image.
// Ein Image ist eine All2DBitmap  mit einem bestimmten Bildausschnitt
// die als srcRect angegeben ist.. damit ist es z.B moeglich, auf einer
// Bitmap mehrere Animationsphasen abzubilden..
// Ausserdem kann ein Image gestretcht/gespiegelt werden..
// Image ist die Hardware Kapselung der Bitmap uns sollte alle Funktionen die auf
// Bitmapebene stattfinden bereitstellen..deswegen ist CBitMap auch private und
// sollte/darf von keinem anderen Module benutzt werden
// Im Gegensatz zu einem Sprite hat ein Image keine Position, Es kann jedoch
// auf eine bestimmte Position in einem anderen Image geblittet werden
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D_HAL/Bitmap.h"
#include "../All2D_HAL/PicLoader.h" // Hinzugefügt von der Klassenansicht
#include "../../Utils/Point.h"	// Hinzugefügt von der Klassenansicht
#include "../../Utils/Rect.h" // Hinzugefügt von der Klassenansicht
#include "../includes/blitmodes.h"

#include <string>
using std::string;

class Image
{
public:
	void setTransparentColor(int col);
	int getTransparentColor();
	void cloneImage(Image& srcImage, Rect cloneRect);
	void txtMap(Image& destination, Point *vertex, int n);
	void box(int x0,int y0, int x1, int y1, int COL);
	void box(int x0,int y0, int x1, int y1, int COL, int FILL);
	void line(int x0, int y0, int x1, int y1, int COL);
	virtual void cloneImage(Image& srcImage);
	virtual void finish();
	virtual void unload();
	virtual void resize(int newWidth, int newHeight);
	void clear(int Color=0);
	void setSrcRect(Rect tmp);
	Rect getSrcRect();
	virtual int getHeight();
	virtual int getWidth();
	void setOffset(int x, int y);
	Point getOffset();

	void show(Image& Dest, int x, int y, int bltMode=IMAGE_BLTMODE_TRANS);
	void show(Image& Dest, int x, int y, int w, int h, int bltMode=IMAGE_BLTMODE_TRANS);

	bool loadImage(string fileName);

	Image();
	Image(int w, int h);
	Image(Image* clone);
	virtual ~Image();

	CBitMap* getBitMap();

	void setBitMap(CBitMap* src);

protected:
	Point offset;
	Rect srcRect;
private:
	int iTransparentCol;
	CBitMap* BitMap;
};

// GridAlign.cpp: Implementierung der Klasse GridAlign.
//
//////////////////////////////////////////////////////////////////////

#include "GridAlign.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

GridAlign::GridAlign()
{
	alignMap=NULL;
	iWidth=0;iHeight=0;
	alignRight=false;
	iRightBorder=1;
}

GridAlign::~GridAlign()
{

}

void	GridAlign::setSize(int w, int h)
{
	if (alignMap!=NULL)
		delete alignMap;

	iWidth=w;iHeight=h;

	alignMap=new int[w*h];
	clearMap();
}

void GridAlign::clearMap()
{
	for (int y=0; y<iHeight;y++)
		for (int x=0; x<iWidth;x++)
			alignMap[y*iWidth+x]=0;
}

Point GridAlign::gridPosition(int length, int xc, int yc, bool snapIt, bool alignIt)
{
	Point		retVal=Grid::gridPosition(xc,yc,snapIt);

	if (!snapIt)	// wenn SnapIt == false, dann wird die normale Posittion zurueckgegeben
	{
		int Pos = Grid::getGridPosition(retVal.x,retVal.y);
		int mx,my;
		if (iWidth!=0 && Pos>-1)	// Nur wenn die Dimensionen der alignMap schon gesetzt sind..(sonst macht es ja auch keinen Sinn..)
		{
			mx=Pos%iWidth;			// mx,my sind die Koordinaten in der alignMap
			my=(Pos-mx)/iWidth;
			mx-=abs(length)/2;

			int place;
			if (alignIt)
				place=findNextFreePlace(my,length);
			else
				place=mx;

			if (place!=-1)
			{
				moveStripe(place,my,length);
				retVal.x+=(place-mx)*xSize;
			}
		}	else {
			remove(length);	// ein Wert wurde vom Brett entfernt..(Pos==-1)
		}
	}
	return retVal;
}

// findet in der angegebenen Reihe eine Lücke der angegebenen Länge

// gibt -1 zurück, wenn keine Position gefunden wurde
int GridAlign::findNextFreePlace(int iRow, int iVal)
{
	int retVal=-1;
	int iLen=abs(iVal);
	if (!alignRight)		// hier ist die normale SuchRoutine von links nach rechts fürs AdditionsGame
	{
		for (int x=0;x<=(iWidth-iLen);x++)		// könnte auch schneller gehen..z.B als String mit find Function..
		{
			if (retVal!=-1)
				break;
			if (alignMap[iRow*iWidth+x]==0 || alignMap[iRow*iWidth+x]==iVal) // ist die Position frei?
			{
				int tmpIndex=x;							// Kandidat ueberpruefen
				for (int nl=0;nl<iLen;nl++)	{		// ist eine Stelle frei?
					if (alignMap[iRow*iWidth+x+nl]!=0 && alignMap[iRow*iWidth+x+nl]!=iVal)
						break;									// nein, abbrechen..
                    if (nl==iLen) //stelle gefunden?
					retVal=tmpIndex;
				}
			}
		}
	}	else {		// Hier ist die für Subtraktion...
		for (int x=iWidth-iRightBorder;x>=0;x--)		// könnte auch schneller gehen..z.B als String mit find Function..
		{
			if (retVal!=-1)
				break;
			if (alignMap[iRow*iWidth+x]==0 || alignMap[iRow*iWidth+x]==iVal) // ist die Position frei?
			{
				int tmpIndex=x;							// Kandidat ueberpruefen
				for (int nl=0;nl<iLen;nl++)	{		// ist eine Stelle frei?
					if (alignMap[iRow*iWidth+x-nl]!=0 && alignMap[iRow*iWidth+x-nl]!=iVal)
						break;									// nein, abbrechen..
				if (nl==iLen) //stelle gefunden?
					retVal=tmpIndex-nl+1;
				}
			}
		}
	}
	return retVal;
}

// bewegt einen Stripe
// a) von einer Position zur anderen
// b) neu auf das Brett
// dabei wird die alignMap entsprechend geUpDated..
void GridAlign::moveStripe(int col, int row, int len)
{
	int index=find(len);
	if (index==-1)			// ist dieser Stripe schon in den Vectoren?
	{		// Nein..Positionieren und in Vectoren einfügen...
		vecCoords.insert(vecCoords.begin(), new Point(col,row));
		vecLengths.insert(vecLengths.begin(),len);
	} else {	//Ja: alte Position löschen, an der neuen einfügen
		Point*	ptOld=vecCoords[index];
		allocPlace(ptOld->x,ptOld->y,abs(vecLengths[index]),0);	// alten Wert löschen
		ptOld->x=col;
		ptOld->y=row;
	}
	allocPlace(col,row,abs(len),len);
}

// setzt einen Wert(val) an eine gegebene Position(col,row) mit der laenge len
void GridAlign::allocPlace(int col, int row, int len, int val)
{
	for (int x=0;x<len;x++)
		alignMap[iWidth*row+col+x]=val;
}

void GridAlign::remove(int len)
{
	int index2Remove=find(len);
	if (index2Remove!=-1)
	{
		Point*	ptOld=vecCoords[index2Remove];
		allocPlace(ptOld->x,ptOld->y,abs(vecLengths[index2Remove]),0);	// alten Wert löschen
		delete ptOld;
		vecLengths.erase(vecLengths.begin()+index2Remove);
		vecCoords.erase (vecCoords.begin() +index2Remove);
	}
}

int GridAlign::find(int len)
{
	int retVal=-1;
	for (unsigned int x=0;x<vecLengths.size();x++)
	{
		if (vecLengths[x]==len)
		{	retVal=x;
			break;
		}
	}
	return retVal;
}

// setzt die Richtung des Alignments...true für Rechtes Alignment, false fuer links
void GridAlign::setAlign(bool blnAlignRight)
{
	alignRight=blnAlignRight;
}

void GridAlign::setRightBorder(int iB)
{
	iRightBorder=iB;
}

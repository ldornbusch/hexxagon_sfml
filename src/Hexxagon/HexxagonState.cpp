// HexxagonState.cpp: Implementierung der Klasse HexxagonState.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonState.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HexxagonState::HexxagonState()
{
	ptrBytes=new BYTE[HEX_BOARD_STONES];
	for (int x=0;x<HEX_BOARD_STONES;x++)
		ptrBytes[x]=0;
}

HexxagonState::~HexxagonState()
{
	if (ptrBytes)
		delete ptrBytes;
}
void HexxagonState::setState(vector<HexxagonStone*>& vec, BYTE Player)
{
	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		int val=vec[x]->getColor();
		if (val==-1)				// TRANSFORM, UM NEGATIVE IN POSITIVE ZAHLEN UMZUWANDELN..
			val=2;
		if (val==HEX_DISABLED)
			val=3;
		ptrBytes[x]=(BYTE)(val);
	}

	bActivePlayer=Player;
}

BYTE HexxagonState::getState(vector<HexxagonStone*>& vec)
{
	BYTE retVal=bActivePlayer;
	for (int x=0;x<HEX_BOARD_STONES;x++)
	{
		int val=(int)ptrBytes[x];
		if (val==2)
			val=-1;
		if (val==3)
			val=HEX_DISABLED;
		vec[x]->setColor(val);
	}

	return retVal;
}
void HexxagonState::save(string strFileName)
{
	FILE* saveFile=fopen(strFileName.c_str(),"wb");
	if(saveFile!=NULL)
	{
		fwrite(&bActivePlayer,sizeof(BYTE),1,saveFile);
		fwrite(ptrBytes,sizeof(BYTE),HEX_BOARD_STONES,saveFile);
		fclose(saveFile);
	}
}
void HexxagonState::load(string strFileName)
{
	FILE* loadFile=fopen(strFileName.c_str(),"rb");

	if(loadFile!=NULL)
	{
		fread(&bActivePlayer,sizeof(BYTE),1,loadFile);
		fread(ptrBytes,sizeof(BYTE),HEX_BOARD_STONES,loadFile);
		fclose(loadFile);
	}

}
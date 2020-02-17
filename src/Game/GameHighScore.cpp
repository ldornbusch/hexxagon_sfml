// GameHighScore.cpp: Implementierung der Klasse GameHighScore.
//
//////////////////////////////////////////////////////////////////////

#include "GameHighScore.h"
#include <math.h>
#define FILENAME "data/Score.txt"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

GameHighScore::GameHighScore()
{
}

GameHighScore::~GameHighScore()
{
	save();
}

void GameHighScore::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");

	load();

}
// Shows the HighScoreList
bool GameHighScore::paint(Image& backBuffer)
{
	static float alpha=0.0;
	int xco,xco2,shadow,xOff;

	shadow=-cos(alpha)*3+4;
	xco=cos(alpha)*5;
	xco2=sin(.75*alpha)*10;
	xOff=sin(.3*alpha)*5+5;
	TextFont.PrintCenter(backBuffer,70+xco+shadow,"HALL OF FAME",IMAGE_BLTMODE_HALF,-1,0,0,xco2);
	TextFont.PrintCenter(backBuffer,70+xco,"HALL OF FAME",IMAGE_BLTMODE_TRANS,-1,0,0,xco2);
	for(int x=0;x<HIGH_SCORE_ENTRIES; x++)
	{
		shadow=-cos(alpha+(x*2*PI/HIGH_SCORE_ENTRIES))*3+4;
		xco=cos(alpha+(x*2*PI/HIGH_SCORE_ENTRIES))*5;
		xco2=sin(.5*alpha+(x*2*PI/HIGH_SCORE_ENTRIES))*10;
		xOff=sin(.3*alpha)*5+5;

		char tmp[100];
		TextFont.PrintAt(backBuffer,shadow+xco+304-16*strNames[x].length(),shadow+xOff+xco2+100+34*x,strNames[x].c_str(),IMAGE_BLTMODE_HALF);
		TextFont.PrintAt(backBuffer,xco+304-16*strNames[x].length(),xOff+xco2+100+34*x,strNames[x].c_str(),IMAGE_BLTMODE_TRANS);
		sprintf(tmp," %lu",iPoints[x]);
		TextFont.PrintAt(backBuffer,shadow+xco+320,shadow+xOff+xco2+100+34*x,tmp,IMAGE_BLTMODE_HALF);
		TextFont.PrintAt(backBuffer,xco+320,xOff+xco2+100+34*x,tmp,IMAGE_BLTMODE_TRANS);
	}
		alpha+=.08;
	return true;
}

int GameHighScore::getPlace(long int iPts)
{
	if (iPts<iPoints[HIGH_SCORE_ENTRIES])
		return -1;	// Keine Plazierung!
	int x=0;
	for (; x<HIGH_SCORE_ENTRIES; x++)
	{
		if (iPts>=iPoints[x])
			break;
	}

	if (x==HIGH_SCORE_ENTRIES)
		return -1;

	return (x+1);
}

void GameHighScore::insert(string strName, long int iPts)
{
	int iPlace=getPlace(iPts);
	if (iPlace>0)
	{
		iPlace--;	//Platzierung in Index umwandeln..
		for (int x=HIGH_SCORE_ENTRIES-2;x>=iPlace; x--)	// Namensliste nach unten verschieben..
		{
			iPoints[x+1]=iPoints[x];
			strNames[x+1]=strNames[x];
		}
		iPoints[iPlace]=iPts;
		strNames[iPlace]=strName;
	}
}

void GameHighScore::save()
{
	FILE	*ScoreFile;
	ScoreFile=fopen(FILENAME,"w");

	if (ScoreFile)
	{//!!NAMES WITH NUMBERS AND SPACES WILL CORRUPT FILE!!
		for (int pos=0;pos<HIGH_SCORE_ENTRIES; pos++)
		{
			fprintf(ScoreFile,"%s\n",strNames[pos].c_str());
			fprintf(ScoreFile,"%ld\n", iPoints[pos]);
		}
		fclose(ScoreFile);
	}
}

void GameHighScore::load()
{
	FILE	*ScoreFile;
	ScoreFile=fopen(FILENAME,"r");

	if (ScoreFile)
	{
		for (int pos=0;pos<HIGH_SCORE_ENTRIES; pos++)
		{
			char	tmp[1000];	//TODO: avoid BUFFEROVERFLOW!!! !!NAMES WITH NUMBERS AND SPACES WILL CORRUPT FILE!!
			fscanf(ScoreFile,"%s\n",tmp);
			strNames[pos]=tmp;
			long l=666;
			fscanf(ScoreFile,"%ld\n", &l);
			iPoints[pos]=l;
		}
		fclose(ScoreFile);
	}	else {
		strNames[0]="COLUMNS";	iPoints[0]=10000;
		strNames[1]="CODING";	iPoints[1]=9000;
		strNames[2]="L.DORNBUSCH";	iPoints[2]=8000;
		strNames[3]="AND";	iPoints[3]=7000;
		strNames[4]="D.VORHAUER";	iPoints[4]=6000;
		strNames[5]="2002";	iPoints[5]=5000;
		strNames[6]="[C] ";	iPoints[6]=4000;
		strNames[7]="HEXEREI";	iPoints[7]=3000;
		strNames[8]="SOFTWARE";	iPoints[8]=2000;
		strNames[9]="CREATIONS";	iPoints[9]=1000;
	}
}



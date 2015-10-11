// PicLoader.cpp: Implementierung der Klasse PicLoader.
//
//////////////////////////////////////////////////////////////////////

#include "PicLoader.h"
#include "../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

#if defined(DEMO)
xZip PicLoader::xz(std::string("data\\demo"));
#else
//xZip PicLoader::xz;
//xZip PicLoader::xz(std::string(( All2D_System::fixedX < 800 ) ? "data\\640" : "data\\800" ));
//xZip PicLoader::xzs(std::string(( All2D_System::fixedX < 800 ) ? "data\\640s" : "data\\800s" ));
#endif

map<string, int> PicLoader::mapReferenceCounter;
vector<string> PicLoader::vecFileNames;
map<string, CBitMap*> PicLoader::mapBMaps;
bool PicLoader::isInitialized=false;

PicLoader::PicLoader()
{
	isInitialized = false;
}

PicLoader::~PicLoader()
{

}

void PicLoader::init()
{
	if (!isInitialized) {
#if defined(DEMO)
		isInitialized = xz.setSource(	std::string( All2D_System::loadPath + "data\\demo" ) );
#else
//		isInitialized = xz.setSource(
//			std::string(All2D_System::loadPath + (( All2D_System::fixedX < 800 ) ? "data\\640" : "data\\800") )
//		);
#endif
	}
}

CBitMap* PicLoader::loadBitMap(string fileName)
{
#if defined(_DEBUG)
//	All2D_System::Debug.Printf2("PicLoader::loadBitMap(%s)",fileName.c_str());
#endif

	if (fileName=="")
		return NULL;

	CBitMap* BitMap=new CBitMap();
	BitMap->Load(fileName);
	return BitMap;

/*
	CBitMap* BitMap;
	BitMap=new CBitMap();

	// look in xzip first
	FILE* fp = NULL;
	if (fileName.substr(0,4) == "data") {
		fp = xz.open(fileName.substr(9));
	}	else {
		fp = xz.open(fileName);
	}

	// then try opening or loading if not found in xzip
	bool retVal=false;
	if (fp!=NULL) {
		retVal = BitMap->Open(fp,IMAGETYPE_PNG);
	}	else {
#if defined(_DEBUG)
		All2D_System::Debug.Printf1("         :: try direct load %s",fileName.c_str());
#endif
		if (fileName.substr(0,4) == "data") {
			retVal = BitMap->Load(fileName);
		}	else {
			retVal = BitMap->Load(All2D_System::dataPath(fileName));
		}
	}

	// return bitmap no success or null and show errors
	if (retVal) {
		return BitMap;
	}	else {
		string strMess="FileName "+fileName+" nicht gefunden!";
//		All2D_System::Debug.Printf0(strMess);
		return NULL;
	}
*/
}

int PicLoader::loadAllBitMaps()
{
	static int Counter=0;
	vector<string>::iterator np=vecFileNames.begin();
	np+=Counter;
	if (np==vecFileNames.end()) {
		vecFileNames.clear();
		Counter=0;
		return -1;
	}

	CBitMap* t=NULL;
	t=loadBitMap(*np);
	if (t!=NULL)
		mapBMaps[*np] = t;
	Counter++;
	return (vecFileNames.size() - Counter);
}


CBitMap* PicLoader::GetBitmap(string name)
{
	CBitMap* back=NULL;
// ist die BitMap in der Map zu finden?
	if (mapReferenceCounter.find(name)!=mapReferenceCounter.end())
	{
		back=mapBMaps[name];
		mapReferenceCounter[name]--;
		if (mapReferenceCounter[name]<=0)
			mapBMaps.erase(name);
	}
	if (back==NULL)
		back=loadBitMap(name);
	return back;
}

void PicLoader::requestLoad(string strFileName)
{
	string strTemp=All2D_System::dataPath(strFileName);
	vecFileNames.insert(vecFileNames.end(), strTemp);
	if (mapReferenceCounter.find(strTemp)!=mapReferenceCounter.end())
		mapReferenceCounter[strTemp]++;
	else
		mapReferenceCounter[strTemp]=1;
	int a=mapReferenceCounter[strTemp];
}

void PicLoader::requestLoad(string FileName, int start, int end, float step)
{
	char strTemp[80];
	if (step<0)
		step=All2D_System::skipFactor;
	float index=(float)start;
	for (int x=start;x<end;x++)
	{
		if (index<end)
		{
			sprintf(strTemp,FileName.c_str(),(int)index);
			requestLoad(strTemp);
			index+=step;
		}	else
			break;
	}
}

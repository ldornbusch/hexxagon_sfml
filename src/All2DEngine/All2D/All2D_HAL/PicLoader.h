// PicLoader.h: Schnittstelle für die Klasse PicLoader.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PICLOADER_H__8A0C6236_5811_4C9A_A132_7CBA6ACA21DB__INCLUDED_)
#define AFX_PICLOADER_H__8A0C6236_5811_4C9A_A132_7CBA6ACA21DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../Utils/xzip/xzip.h"	//Das ist nicht Cool!!!

#include <map>
#include <vector>
#include <string>

using namespace std ;

#include "Bitmap.h"

typedef struct tagREQUESTEDFILENAME {
	string fileName;
	int refCount;
} REQUESTEDFILENAME;

class PicLoader
{
	public:

		static	void requestLoad(string FileName, int start, int end, float step=-1.0);
		static	void requestLoad(string strFileName);
		static  void init();
		static	int loadAllBitMaps();
		static	CBitMap* GetBitmap(string name);

		PicLoader();
		virtual ~PicLoader();

	protected:
		static	CBitMap* loadBitMap(string fileName);
		static	bool isInitialized;

	private:
		static	map<string, int> mapReferenceCounter;
		static	vector<string> vecFileNames;
		static	map<string, CBitMap*> mapBMaps;
//		static	xZip xz;
		//static	xZip xzs;
};

#endif // !defined(AFX_PICLOADER_H__8A0C6236_5811_4C9A_A132_7CBA6ACA21DB__INCLUDED_)

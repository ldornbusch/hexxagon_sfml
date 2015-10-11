// xZip.cpp: Implementierung der Klasse xZip.
//
// author: daniel vorhauer - 2001 hexerei software creations
//
//////////////////////////////////////////////////////////////////////

#include "xZip.h"
#include "../../All2D/All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/**
 * construct class and load xzip file
 * validates file and sets bInitialized accordingly
 */
xZip::xZip(std::string &xzipfile)
{
	if ( !xzipfile.empty() )
		setSource(xzipfile);
}

xZip::~xZip()
{
	if (binFile)
		fclose(binFile);
}

/**
 * set source xzip
 */
bool xZip::setSource(std::string xzipfile)
{
	// initialize member variables
	bInitialized = false;
	module = NULL;
	file = NULL;


	/*
	 * open xzip source
	 */

	// check if filename was passed
	if ( xzipfile.empty() ) {
//		All2D_System::Debug.Printf0( "ERROR: No filename passed..." );
		return false;
	}

	// load xzip file
	doc = new TiXmlDocument();
	std::string tmp = xzipfile+".xcf";
	doc->LoadFile(tmp.c_str());

	// check for any errors
	if ( doc->Error() ) {
//		All2D_System::Debug.Printf0( "Error in %s: %s.xcf", xzipfile.c_str(), doc->ErrorDesc());
		return false;
	}
//	All2D_System::Debug.Printf1( "Loaded xZip Archive %s", xzipfile.c_str() );


	/*
	 * check for correct format
	 */

	// find root node
	TiXmlNode* node = doc->FirstChild("xzip");
	if (!node) {
//		All2D_System::Debug.Printf0( "ERROR: Could not find a valid Root Node" );
		return false;
	}
	root = node->ToElement();

	/*
	 * open binary file
	 */

	xzipfile += ".bin";
	if (!(binFile=fopen(xzipfile.c_str(),"rb"))) {
//		All2D_System::Debug.Printf0( "ERROR: Could not open binary file" );
		return false;
	}

	/*
	 * get details from control file
	 */

	// get xzip name
	strName = root->Attribute("id");
	//System::Debug.Printf1( "XZIP Name: %s", strName.c_str() );

	// creator and operator
	//System::Debug.Printf1( "XZIP Created: %s", root->Attribute("created")->c_str() );
	//System::Debug.Printf1( "XZIP Operator: %s", root->Attribute("operator")->c_str() );

	// find first module and select it
	if ( root->FirstChild("mod") ) {
		bInitialized = true;
		return select(0);
	}
	return false;
}

/**
 * select module by id
 */
bool xZip::select(int iModule)
{
	// clear current module
	module = NULL;

	if ( !bInitialized )
		return false;


	/*
	 * locate modules in xzip
	 */

	TiXmlNode*		node;
	TiXmlElement*	elem;

	int iModuleCount = 0;

	// loop through modules
	for ( node=root->FirstChild("mod"); node; node=node->NextSibling("mod") ) {

		// find module by index
		if ( iModule == iModuleCount ) {
			//All2D_System::Debug.Printf1( "....... FOUND MODULE %d .......",iModule);
			module = node->ToElement();
			return true;
		}
		// increment counter
		iModuleCount++;
	}
	return true;
}


/**
 * select module by name
 */
bool xZip::select(std::string modulename)
{
	if ( !bInitialized )
		return false;

	/*
	 * locate modules in xzip
	 */

	TiXmlNode*		node;
	TiXmlElement*	elem;

	// loop through modules
	for ( node=root->FirstChild("mod"); node; node=node->NextSibling("mod") ) {

		// get element
		elem = node->ToElement();

		// find module by name
		if ( modulename.compare(elem->Attribute("id"))==0 ) {
			//All2D_System::Debug.Printf1( "....... FOUND MODULE %s .......",modulename.c_str());
			module = node->ToElement();
			return true;
		}
	}
	return false;
}

/**
 * get info abount module
 * optionally load module before
 */
bool xZip::getModuleInfo(XZMODULEINFO &xzmInfo,std::string modulename)
{
	// pessimistic approach
	xzmInfo.size = 0;

	// load module if name was passed
	if ( !modulename.empty() )
		if ( !select(modulename) )
			return false;

	// fail if not initialized
	if ( !bInitialized || module==NULL )
		return false;

	// copy attributes
	xzmInfo.name = module->Attribute("id");
	xzmInfo.source = ""; // module->Attribute("r");
	module->Attribute("d",&xzmInfo.dirs);
	module->Attribute("f",&xzmInfo.files);
	module->Attribute("s",&xzmInfo.size);

	return true;

}

FILE* xZip::open(std::string filename)
{
	XZFILEINFO finf;

	if ( !getFileInfo(finf,filename) || finf.size < 1 )
		return NULL;

	fseek(binFile,finf.offset,SEEK_SET);           // int

	if ( finf.encoding == XZEncode_Binary ) {
		// check the seven byte signature
		unsigned char xhd[7];
		int iRead = fread(xhd, 1, 7, binFile);
		if (iRead!=7||xhd[0]!='H'||xhd[1]!='E'||xhd[2]!='X'||
			xhd[3]!=0||xhd[4]!='H'||xhd[5]!='E'||xhd[6]!='X') {
			// move back to beginning of requested file
			fseek(binFile,-7,SEEK_CUR);
//			All2D_System::Debug.Printf0( "ERROR: Could not find a valid Header" );
		}
	}

	return binFile;

}

/**
 * load given file as current file
 */
bool xZip::load(std::string filename)
{
	if ( !bInitialized || module==NULL || filename.empty() )
		return false;

	/*
	 * locate files in module
	 */

	TiXmlNode*		node;
	TiXmlElement*	elem;

	// start from module root
	TiXmlElement*	searchnode = module;

	// position to requested path
	bool bValid = true;
	std::string searchname;
	int iSep = 0;
	int iRet = 0;
	while ( bValid && (iRet = filename.find_first_of('\\',iSep)) > -1 ) {
		// get directory name
		searchname = filename.substr(iSep,iRet-iSep);
		//All2D_System::Debug.Printf0("searching directory %s",searchname.c_str() );
		// loop through dirs in searchnode
		bValid = false;
		for ( node=searchnode->FirstChild("d"); node; node=node->NextSibling("d") ) {

			// get element
			elem = node->ToElement();

			// find file by name
			if ( searchname.compare(elem->Attribute("id"))==0 ) {
				//All2D_System::Debug.Printf1( "....... FOUND DIR %s .......",searchname.c_str());
				searchnode = node->ToElement();
				bValid = true;
				break;
			}
		}
		// remember last seperator position
		iSep = iRet+1;
	}
	if ( !bValid ) return false;
	searchname = filename.substr(iSep);

	// loop through files
	for ( node=searchnode->FirstChild("f"); node; node=node->NextSibling("f") ) {

		// get element
		elem = node->ToElement();

		// find file by name
		if ( searchname.compare(*elem->Attribute("id")+".png")==0 ) {
			//All2D_System::Debug.Printf1( "....... FOUND FILE %s .......",searchname.c_str());
			file = node->ToElement();
			return true;
		}
	}
	return false;
}


/**
 * get information about current file
 * optionally load file before if name is passed
 */
bool xZip::getFileInfo(XZFILEINFO &xzfInfo,std::string filename)
{
	// load file if name was passed
	if ( !filename.empty() )
		if ( !load(filename) )
			return false;

	// fail if not initialized
	if ( !bInitialized || file == NULL)
		return false;

	// temp string
	std::string tmp;

	/*
	 * copy attributes
	 */

	// filename without path
	xzfInfo.name = file->Attribute("id");

	// type of file
	if ( file->Attribute("type") ) {
		tmp = file->Attribute("type");
		if ( tmp == "image/gif" )
			xzfInfo.type = XZImage_Gif;
		else if ( tmp == "image/jpeg" )
			xzfInfo.type = XZImage_Jpeg;
		else if ( tmp == "image/pcx" )
			xzfInfo.type = XZImage_Pcx;
		else if ( tmp == "image/png" )
			xzfInfo.type = XZImage_Png;
		else if ( tmp == "audio/wave" )
			xzfInfo.type = XZAudio_Wave;
		else if ( tmp == "text/xml" )
			xzfInfo.type = XZText_Xml;
		else if ( tmp == "text/html" )
			xzfInfo.type = XZText_Html;
		else if ( tmp == "text/plain" )
			xzfInfo.type = XZText_Plain;
		else
			xzfInfo.type = XZImage_Png;
	}

	// file encoding ( text or binary )
	xzfInfo.encoding = XZEncode_Binary;
	if (file->Attribute("encoding") && strcmp(file->Attribute("encoding"),"Text")) {
		xzfInfo.encoding = XZEncode_Text;
	}

	// size and offset
	file->Attribute("s",&xzfInfo.size);
	file->Attribute("o",&xzfInfo.offset);

	// correct size if file has header
	if ( xzfInfo.encoding == XZEncode_Binary )
		xzfInfo.size -= 7;

	return true;
}

std::string xZip::getName()
{
	return strName;
}

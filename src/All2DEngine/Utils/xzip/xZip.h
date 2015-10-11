// xZip.h: Schnittstelle für die Klasse xZip.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// HOW TO USE XZIP DOCUMENTATION
//////////////////////////////////////////////////////////////////////
/**

	xZip is designed to bundle a virtual file system in a single file
	to optimize load times and optionally encrypt files.

	xZip comes along with a set of utility batches to create the needed
	xZip control and binary files. with the scripts you can select a set
	of files to be included in your xZip archive.

	xZip supports the use of multiple modules (a logical subset of dirs
	and files) in one single xZip archive.

	once the control and binary files are created, you can use an xZip
	archive in following manner:


		SAMPLE
		================================================================

		CREATING XZIP ARCHIVE
		----------------------------------------------------------------
		create an xZip archive with the given batch files including a
		set of images used for an animation, these can be structured in
		an arbitrary hierachy of directories. name the set 'animations'.

		you should have two resulting files:

							animations.xml
			-and-		animations.bin


		USING XZIP ARCHIVE
		----------------------------------------------------------------
		to open the archive in source create an xZip class with the
		full path and name of the archive without extensions

				// initialize xzip file
				xZip xz = *new xZip(std::string("xzip\\animations"));


		SELECTING A MODULE FROM THE ARCHIVE
		----------------------------------------------------------------
		by default the first module contained in the archive is
		selected. a module has to be selected in order to open files
		within this module. if you want to select a module other than
		the default module, there are two methods provided for you:

				// select module by index
				xz.select(0);

				// select module by name
				xz.select(std::string("_SetA"));

		both methods return true if successfull and false otherwise.


		RETREIVING INFORMATION ABOUT A MODULE
		----------------------------------------------------------------
		if you need to retreive information about the current module
		you can use the XZMODULEINFO structure to retreive informations
		like name, original source directory, total number of contained
		directories and files and size.

				// get info about loaded module
				XZMODULEINFO minf;
				xz.getModuleInfo(minf);

		alternativly you can pass the modulename to select a module
		before retreiving the module information structure:

				// load module and get info
				xz.getModuleInfo(minf,"_SetA");

		both methods return true if successfull and false otherwise.
		if the module infostructure could not be filled, size will be
		set to 0:

				// dump module infostructure
				if ( minf.size > 0 ) {
					printf("ModuleInfo.Name: %s",		minf.name.c_str());			// string
					printf("ModuleInfo.Source: %s",	minf.source.c_str());		// string
					printf("ModuleInfo.Dirs: %d",		minf.dirs);							// int
					printf("ModuleInfo.Files: %d",	minf.files);						// int
					printf("ModuleInfo.Size: %d",		minf.size);							// int
				} else {
					printf("No Module Loaded");
				}


		LOADING FILES FROM A MODULE
		----------------------------------------------------------------
		loading a file from a module will actually just browse the
		virtual filesystem for the existance of the given filename and
		make the file current if it exists. the actual file is not
		opened or loaded, but the file is available for processing.

				// load file from module
				xz.load("anims/frame000.jpg");

		method returns true if successfull and false otherwise.

		use open methods to get a file object to work with.


		RETREIVING INFORMATION ABOUT A FILE
		----------------------------------------------------------------
		if you need to retreive information about the current file
		you can use the XZFILEINFO structure to retreive informations
		like name, type, encoding, size and offset.

				// get info about loaded file
				XZFILEINFO finf;
				xz.getFileInfo(finf);

		alternativly you can pass the filename to load a file before
		retreiving the file information structure:

				// load file and get info
				xz.getFileInfo(finf,"anims/frame000.jpg");

		both methods return true if successfull and false otherwise.
		if the file infostructure could not be filled, size will be
		set to 0:

				// dump file infostructure
				if ( finf.size > 0 ) {
					printf("FileInfo.Name: %s",			finf.name.c_str());		// string
					printf("FileInfo.Type: %s",			finf.type);						// int
					printf("FileInfo.Encoding: %d",	finf.encoding);				// int
					printf("FileInfo.Size: %d",			finf.size);						// int
					printf("FileInfo.Offset: %d",		finf.offset);					// int
				} else {
					printf("No File Loaded");
				}


		GETTING A FILE OBJECT TO WORK WITH
		----------------------------------------------------------------

*/

#pragma once

#include "../XML/tinyxml.h"
#include <string>
#include <vector>

// module info structure
typedef struct tagXZMODULEINFO {
	std::string name;
	std::string source;
	int dirs;
	int files;
	int size;
} XZMODULEINFO;

// file info structure
typedef struct tagXZFILEINFO {
	std::string name;
	int size;
	int type;
	int encoding;
	int offset;
} XZFILEINFO;

// file type enumeration
typedef enum tagXZFILETYPES {
  XZImage_Gif,
  XZImage_Jpeg,
  XZImage_Pcx,
  XZImage_Png,
  XZAudio_Wave,
  XZText_Xml,
  XZText_Html,
  XZText_Plain
} XZFILETYPE;

// file encoding enumeration
typedef enum tagXZENCODING {
	XZEncode_Binary,
	XZEncode_Text
} XZENCODING;

class xZip
{
public:
	std::string getName();

	bool select(int iModule);
	bool select(std::string modulename);
	bool getModuleInfo(XZMODULEINFO &xzmInfo,std::string modulename);

	bool load(std::string filename);
	FILE* open(std::string filename);
	bool getFileInfo(XZFILEINFO &xzfInfo,std::string filename);

	bool setSource(std::string zipfile);
	xZip(std::string &xzipfile);
	virtual ~xZip();

private:
	FILE *binFile;
	std::string strName;

	bool bInitialized;
	bool bOpenFile;

	TiXmlDocument* doc;

	TiXmlElement* root;
	TiXmlElement* module;
	TiXmlElement* file;
};

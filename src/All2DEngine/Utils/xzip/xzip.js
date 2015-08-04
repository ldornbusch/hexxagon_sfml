/********************************************************************
* xzip.js - version 1.0
* reads xzip xml definition file, creates zip and updates definition
*
* @author dav
* @version 1.0
* @date 23.05.2001 13:11
*********************************************************************/

// === DATA =========================================================

  /*
   * set default values
   */
  var scriptPath    = WScript.ScriptFullname.substring(0,WScript.ScriptFullname.length-(WScript.ScriptName.length+1));
  var scriptDrive   = scriptPath.substring(0,1);
  var szDefPath     = scriptPath;
  var szPrefix      = '_$hex$t_';
  var szHeaderFile  = scriptPath+'\\'+szPrefix+'header.xhd';
  var szBatchFile   = scriptPath+'\\'+szPrefix+'copyxzip.bat';
  var szDefName     = 'data';
  var szDefExt      = 'xml';
  var szDefFile     = scriptPath+'\\'+szDefName+'.'+szDefExt;
  var szSourceDir   = scriptPath;
  var bRecursive    = false;
  var szTimestamp   = dateStamp();
  var szOperator    = 'def';

  // file system object and system shell
  var fso;
  var shell;
  var bat;
  var modFile;

  // xml dom object
  var xmlSource;
  var xslStyle;

  // size and offset
  var totalSize = 0;
  var fileOffset = 0;

// === MAIN =========================================================

  debug();
  main();

// === CODE =========================================================


// main function
// ------------------------------------------------------------------
// parse commandline and start building xzip definition file

function main() {

  /*
   * check commandline
   */

  parseCommandline();

  /*
   * create file system object and check path
   */

  fso = new ActiveXObject("Scripting.FileSystemObject");
  if (!fso.FolderExists(szSourceDir))
    error("Source directory does not exists!\n\n\tDirectory: "+szSourceDir+"\n");


  /*
   * create output to definition file
   */

  createDefinitionFile();


  /*
   * create xmlDOM object and open definition file
   */

  xmlSource = new ActiveXObject("Microsoft.XMLDOM");
  xmlSource.async = false;
  xmlSource.load( szDefFile );
  var state = xmlSource.readyState;
  print( "XML-ReadyState = " + state );
  if (state == 4) {
    var err = xmlSource.parseError;
    if (err.errorCode != 0) {
      print( "XML-Error: " + err.Reason );
    } else {
      print( "XML-Success: opened xzip definition file" );
    }
  }


  /*
   * update sums and offsets
   */

  updateDefinitionFile();
  xmlSource.save( szDefFile );


  /*
   * create xzip
   */

  shell = WScript.CreateObject("WScript.Shell");

  createxzip();


  /*
   * exit
   */

  WScript.Quit(0);

}


// updateDefinitionFile
// ------------------------------------------------------------------
// update sums, sizes and offsets in xzip definition file

function updateDefinitionFile() {

  // get all modules from the definition file
  var moduleList = xmlSource.documentElement.selectNodes("/xzip/module");
  print ( "\n" + moduleList.length + " modules in definition file." );

  // loop through module list
  for ( var i=0; i<moduleList.length; i++ ) {
    var module = moduleList.nextNode();
    totalSize += updateDefinitionSection( module );
    module.setAttribute("size",totalSize);
  }

  print( "==================================================");
  print( "Total Size: " + totalSize);
}

function updateDefinitionSection( section ) {

  var sectionSize = 0;
  var childList = section.childNodes;

  // loop through children
  for ( var j=0; j<childList.length; j++ ) {
    var child = childList.nextNode();
    if ( child.nodeName == 'dir' ) {
      updateDefinitionSection( child );
    } else if ( child.nodeName == 'file' ) {
      child.setAttribute("offset", fileOffset);
      var size = parseInt(child.getAttribute("size"),10);
      if ( child.getAttribute("encoding") == "Binary" ) size += 7;
      sectionSize += size;
      fileOffset += size;
    }
  }
  print( "# ------------------------------------------------");
  print( "# " + section.nodeName + ": " + section.attributes.item(0).value + " Size: " + sectionSize);

  section.setAttribute("size",sectionSize);

  return sectionSize;
}


// createxzip
// ------------------------------------------------------------------
// copy definitionfile and files to xzip archive

function createxzip() {

  // create temporary header
  var retVal = 0;
  var tmp = fso.CreateTextFile(szHeaderFile);
  tmp.Write("HEX"+String.fromCharCode(0)+"HEX");
  tmp.Close();

  // loop through module list
  var moduleList = xmlSource.documentElement.selectNodes("/xzip/module");
  for ( var i=0; i<moduleList.length; i++ ) {

    var module = moduleList.nextNode();
    var modName = module.getAttribute("name");
    var sourceDir = module.getAttribute("source");
    //var fileList = module.selectNodes("//file");
    modFile = scriptPath + '\\' + szPrefix + modName + ".bin";

    // create command batch
    bat = fso.CreateTextFile(szBatchFile);
    bat.WriteLine("cd "+szSourceDir);

    createxzipDirectory(module,sourceDir);

    bat.WriteLine("cd "+scriptPath);
    bat.Close();

    // create empty bin file
    tmp = fso.CreateTextFile(modFile);
    tmp.Close();

    retVal = shell.Run(szBatchFile, 1, true);
  }

  // kill temporary header and batch
  fso.DeleteFile(szHeaderFile);
  fso.DeleteFile(szBatchFile);
  //fso.DeleteFile(szDefFile);
  //fso.DeleteFile(szPrefix+modName+".bin");
}


// createxzipDirectory
// ------------------------------------------------------------------
// copy definitionfile and files to xzip archive

function createxzipDirectory( section, root ) {

  var childList = section.childNodes;

  // loop through children
  for ( var j=0; j<childList.length; j++ ) {
    var child = childList.nextNode();
    if ( child.nodeName == 'dir' ) {
      createxzipDirectory( child, root + "\\" + child.getAttribute("name") );
    } else if ( child.nodeName == 'file' ) {
      var fileName = fso.BuildPath(root, child.getAttribute("name"));
      fileName = fileName.substr(szSourceDir.length+1);
      print( "XZIPDIR Writing "+fileName+"..." );
      if ( child.getAttribute("encoding") == "Binary" ) fileName = szHeaderFile+"+"+fileName;
      bat.WriteLine("copy /b "+modFile+"+"+fileName+" "+modFile);
    }
  }
}


// parseCommandline
// ------------------------------------------------------------------
// parse commandline and set parameters
// Syntax: build_definition <name[.xml]> [-d sourcedir] [-r] [-t timestamp] [-o operator]

function parseCommandline() {

  // show help and quit if we have no arguments
  if ( WScript.Arguments.Count() == 0 ) showHelp();

  // get arguments
  var args = WScript.Arguments;


  /*
   * get name from commandline
   */

  // first argument must be name
  if ((args(0).substr(0,1)=='-'&&args(0).substr(2,1)==' ')||args(0).substr(0,1)=='.')
    showHelp('ERROR: no valid name specified!');
  // separate arg to path, name and extension
  var sep = args(0).lastIndexOf("\\") + 1;
  var dot = args(0).lastIndexOf(".");
  if ( sep > 0 ) szDefPath = args(0).substring(0,sep-1);
  if ( dot > sep ) {
    szDefName = args(0).substring(sep,dot);
    szDefExt = args(0).substr(dot+1);
  } else {
    szDefName = args(0).substr(sep);
  }
  szDefFile = szDefPath + "\\" + szPrefix + szDefName + '.' + szDefExt;

  print("\nPath:\t"+szDefPath+"\nName:\t"+szDefName+"\nExt:\t"+szDefExt+"\nFile:\t"+szDefFile);


  /*
   * parse the rest of the commandline
   */

  for ( var i=0; i<args.Count(); i++ ) {
    switch( args(i) ) {
      case '-d':
        if ( i + 1 < args.Count() )
          szSourceDir = args(i+1);
        break;
      case '-r':
        bRecursive = true;
        break;
      case '-t':
        if ( i + 1 < args.Count() )
          szTimestamp = args(i+1);
        break;
      case '-o':
        if ( i + 1 < args.Count() )
          szOperator = args(i+1);
        break;
    }
  }

  // cut trailing separator
  if ( szSourceDir.substr(szSourceDir.length-1,1) == "\\" )
    szSourceDir = szSourceDir.substring(0,szSourceDir.length-1);

  print("\nSrc:\t"+szSourceDir+"\nSubs:\t"+bRecursive+"\nTime:\t"+szTimestamp+"\nOp:\t"+szOperator);

}


// createDefinitionFiles
// ------------------------------------------------------------------
// create xzip definition file and parse dirs and files

function createDefinitionFile() {

  var tf = fso.CreateTextFile(szDefFile, true);

  var tnow = new Date();

  print("Started " + szDefFile);

    writeHeader(tf);

      createOutput(2, szSourceDir, tf);

    writeFooter(tf);

  tf.Close();

  print("Finished " + szDefFile + "... ( "+((new Date()-tnow)/1000)+" secs )");

}

// createOutput
// ------------------------------------------------------------------
// parse dirs and files of given directory and write xml to textfile

function createOutput(indent, dir, tf) {

  print("Parsing ["+dir+"]");

  /*
   * get files in folder
   */
  var Folder = fso.GetFolder(dir);

  // enumerate dirs
  if ( bRecursive && Folder.SubFolders.Count > 0 ) {
    var dc = new Enumerator(Folder.SubFolders);
    for (; !dc.atEnd(); dc.moveNext()) {
      var d = dc.item();
      if ( d.Files.Count > 0 || d.SubFolders.Count > 0 ) {
        tf.WriteLine(sprintl(indent, '<dir name="'+d.Name+'" dirs="'+d.SubFolders.Count+'" files="'+d.Files.Count+'">'));
          createOutput(indent+1,dc.item(),tf);
        tf.WriteLine(sprintl(indent, '</dir>'));
      } else {
        tf.WriteLine(sprintl(indent, '<dir name="'+d.Name+'"/>'));
      }
    }
  }

  // enumerate files
  var Files = Folder.Files;
  if ( Files.Count > 0 ) {
    var fc = new Enumerator(Files);
    for (; !fc.atEnd(); fc.moveNext()) {
      var f = fc.item();
      if ( f.Name.indexOf(szPrefix)!=0 ) {
        var s = '<file name="' + f.Name + '" size="'+ f.Size +'"';
        var ext = f.Name.substr(f.Name.lastIndexOf('.')+1);
        switch(ext) {
          case 'gif':
            s += ' type="image/gif" encoding="Binary"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'jpg','jpeg':
            s += ' type="image/jpeg" encoding="Binary"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'pcx':
            s += ' type="image/pcx" encoding="Binary"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'png':
            s += ' type="image/png" encoding="Binary"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'wav':
            s += ' type="audio/wave" encoding="Binary"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'xml':
            s += ' type="text/xml" encoding="Text"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'html':
            s += ' type="text/html" encoding="Text"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
          case 'txt':
            s += ' type="text/plain" encoding="Text"/>';
            tf.WriteLine(sprintl(indent,s));
            break;
        }
      }
    }
  }
}


// writeHeader
// ------------------------------------------------------------------
// write default header with module details to given textfile

function writeHeader(tf) {
  var d = fso.GetFolder(szSourceDir);
  if (!(tf && d)) return;
  tf.WriteLine('<?xml version="1.0" standalone="yes"?>');
  tf.WriteLine('<xzip name="'+szDefName+'" created="'+szTimestamp+'" operator="'+szOperator+'">');
  tf.WriteLine('  <module name="'+szDefName+'" source="'+szSourceDir+'" dirs="'+d.SubFolders.Count+'" files="'+d.Files.Count+'">');

}


// writeFooter
// ------------------------------------------------------------------
// write default footer to given textfile

function writeFooter(tf) {
  if (!tf) return;
  tf.WriteLine('  </module>');
  tf.WriteLine('</xzip>');
}


// sprintl
// ------------------------------------------------------------------
// add indentation to given string

function sprintl(indent, s) {
  var spc = '';
  for ( var i=0; i<indent; i++ ) spc += "  ";
  return spc + s;
}


// debug
// ------------------------------------------------------------------
// generates debug output

function debug() {

  var dbug = "";
  var wsn = WScript.CreateObject("Wscript.Network");

  dbug += "\n##################################################\n";
  dbug += "# " + WScript.ScriptName + "\n# --------------------------------------------------\n";
  dbug += "#   Running " + WScript.ScriptFullName + "\n";
  dbug += "#   with    " + WScript.Name + " " + WScript.Version + " (" + WScript.FullName + ")\n#\n";
  dbug += "#   by      " + wsn.UserName + "@" + wsn.UserDomain + " \\\\" + wsn.ComputerName + "\n#\n";

  // Display all command-line parameters
  var objArgs = WScript.Arguments;
  if ( objArgs.Count() > 0 ) {
    dbug += "# Arguments\n# --------------------------------------------------\n";
    for ( var i=0; i<objArgs.Count(); i++ ) {
      dbug += "#   (" + i + ") " + objArgs(i) + "\n";
    }
  }
  dbug += "##################################################\n";

  print( dbug );

}


// showHelp
// ------------------------------------------------------------------
// display syntax on commandline

function showHelp(msg) {
  error( ( (msg) ? msg : 'Syntax Error!' )
    + "\n\n\tSyntax: build_definition <name[.xml]> [-d sourcedir] [-r] [-t timestamp] [-o operator]\n"
  );
}


// print
// ------------------------------------------------------------------
// wrapper to make output portable to html

function print( msg ) {
  WScript.echo( msg );
}


// error
// ------------------------------------------------------------------
// wrapper to make output portable to html - prints error and dies

function error( msg ) {
  WScript.echo( "ERROR: " + msg + "\n" );
  WScript.Quit(1);
}


// dateStamp
// ------------------------------------------------------------------
// create datestamp of current date

function dateStamp(pre) {

  var date = new Date();
  var stamp = ""
  if ( pre ) stamp += pre;

  stamp += date.getFullYear()
  + digits(date.getMonth(),2)
  + digits(date.getDate(),2)
  + digits(date.getHours(),2)
  + digits(date.getMinutes(),2)
  + digits(date.getSeconds(),2);

  return stamp;
}

// digits
// ------------------------------------------------------------------
// return given number source in string
// with n characters and leading zeros

function digits( source, n ) {
  var result = '0';
  for ( var i=1; i<n; i++ ) result += '0';
  result += source;
  if ( result.length <= n ) return result;
  return result.substring(result.length-n,result.length);
}

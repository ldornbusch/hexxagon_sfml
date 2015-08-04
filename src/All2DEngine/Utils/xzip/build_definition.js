/********************************************************************
* build_definition.js - version 1.0
* dumps given directory into a xzip xml definition file
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
  var szDefName     = 'data';
  var szDefExt      = 'xml';
  var szDefFile     = scriptPath+'\\'+szDefName+'.'+szDefExt;
  var szSourceDir   = scriptPath;
  var bRecursive    = false;
  var szTimestamp   = '20010523131923';
  var szOperator    = 'def';

  // file system object
  var fso;



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

  if ( WScript.Arguments.Count() == 0 ) showHelp();

  // Syntax: build_definition <name[.xml]> [-d sourcedir] [-r] [-t timestamp] [-o operator]

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
  szDefFile = szDefPath + "\\" + szDefName + '.' + szDefExt;

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

  /*
   * create file system object and check path
   */
  fso = new ActiveXObject("Scripting.FileSystemObject");
  if (!fso.FolderExists(szSourceDir))
    error("Source directory does not exists!\n\n\tDirectory: "+szSourceDir+"\n");

  /*
   * create output file
   */
  var tf = fso.CreateTextFile(szDefFile, true);

  var tnow = new Date();

  print("Started " + szDefFile);

    writeHeader(tf);

      createOutput(2, szSourceDir, tf);

    writeFooter(tf);

  tf.Close();

  print("Finished " + szDefFile + "... ( "+((new Date()-tnow)/1000)+" secs )");

  WScript.Quit(0);

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
      var s = '<file name="' + f.Name + '" size="'+ f.Size +'"';
      var ext = f.Name.substr(f.Name.lastIndexOf('.')+1);
      switch(ext) {
        case 'gif':
          s += ' type="image/gif" encoding="Binary"';
          break;
        case 'jpg','jpeg':
          s += ' type="image/jpeg" encoding="Binary"';
          break;
        case 'pcx':
          s += ' type="image/pcx" encoding="Binary"';
          break;
        case 'png':
          s += ' type="image/png" encoding="Binary"';
          break;
        case 'wav':
          s += ' type="audio/wave" encoding="Binary"';
          break;
        case 'xml':
          s += ' type="text/xml" encoding="Text"';
          break;
        case 'html':
          s += ' type="text/html" encoding="Text"';
          break;
        case 'txt':
          s += ' type="text/plain" encoding="Text"';
          break;
      }
      s += '/>';
      tf.WriteLine(sprintl(indent,s));
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


// print error
// ------------------------------------------------------------------
// wrapper to make output portable to html - prints error and dies

function error( msg ) {
  WScript.echo( "ERROR: " + msg + "\n" );
  WScript.Quit(1);
}

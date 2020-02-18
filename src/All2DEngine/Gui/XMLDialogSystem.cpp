// XMLDialogSystem.cpp: implementation of the XMLDialogSystem class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <sstream>

#include "XMLDialogSystem.h"
#include "../All2D/All2D_System.h"
#include "../All2D/All2D_Events/MessageManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// static Members
int XMLDialogSystem::iIDMessageCounter=0x00;	// above UserMessageArea

XMLDialogSystem::XMLDialogSystem(std::string fileName)
{
	strFileName=fileName;
	xmlDoc.LoadFile(strFileName.c_str());
}

XMLDialogSystem::~XMLDialogSystem()
{
	save();
	for (unsigned int x=0; x<vecDialogs.size();x++)
	{
		vecDialogs[x]->deleteElements();
		delete(vecDialogs[x]);
	}
}

void XMLDialogSystem::init(Image& imgElements)
{
	setTextFont(All2D_System::SystemFont);
	int iDialogIndex=0;

	iActiveDialog=-1;	// No active Dialog as init

	imgUIImage.cloneImage(imgElements);

	TiXmlElement* root= xmlDoc.RootElement();
	if(root!=NULL)
	{
		TiXmlElement* dlg=root-> FirstChildElement();
		while (dlg!=NULL){
			UILayouter* tmp=initDialog(dlg);
			if (tmp!=NULL)
			{
				vecDialogs.push_back(tmp);
				mapName2Index.insert(map<string,int>::value_type(tmp->getName(),iDialogIndex));
				if (dlg->Attribute("parent")!=NULL)
				{
					string strParent=dlg->Attribute("parent");
					mapIndex2Parent.insert(map<int, string>::value_type(iDialogIndex , strParent));
				}
				iDialogIndex++;
			}
			dlg=dlg->NextSiblingElement();
		}

		load();
		blnInitialized=true;
	}
}

UILayouter* XMLDialogSystem::initDialog(TiXmlElement* DialogNode)
{
	UILayouter*	retVal=NULL;
	if (DialogNode!=NULL)
	{
		retVal=new UILayouter();
		retVal->setName(DialogNode->Attribute("name"));
		retVal->setPosition(ConvertXML2Rect(DialogNode,"position"));

		TiXmlElement* child=DialogNode->FirstChildElement();
		while(child!=NULL){
			UIElement* tmp=initUIElement(child, retVal);
			if (tmp!=NULL)
				retVal->add(*tmp);
			child=child->NextSiblingElement();
		}
		retVal->layout();
	}
	return retVal;
}
UIElement* XMLDialogSystem::initUIElement(TiXmlElement* UINode, UILayouter* Dialog)
{
	UIElement* retVal=NULL;
	if (UINode!=NULL)
	{
		string strType=UINode->Value();
		if (strType=="button")
			retVal=createButton(UINode);
		if (strType=="check")
			retVal=createCheckBox(UINode);
		if (strType=="radio")
			retVal=createRadioButton(UINode);
		if (strType=="label")
			retVal=createLabel(UINode);
		if (strType=="textfield")
			retVal=createTextfield(UINode);
		if (strType=="scrollbar")
			retVal=createScrollBar(UINode);
		if (strType=="keyrecorder")
			retVal=createKeyRecorder(UINode);
		if (strType=="scrollarea")
			retVal=createScrollArea(UINode);
		if (strType=="background")
		{
			UISprite* bckgrnd=createLabel(UINode);
			if (bckgrnd!=NULL)
				Dialog->setBackground(*bckgrnd);
		}

		if (retVal!=NULL && UINode->Attribute("name")!=NULL)
			retVal->setName(UINode->Attribute("name"));
	}
	return retVal;
}


UIHoverButton* XMLDialogSystem::createButton(TiXmlElement* UINode)	// ToDo put this as a Constructor in UIHoverbutton...
{
	UIHoverButton* retVal=new UIHoverButton();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);

	retVal->cloneImage(imgUIImage);

	retVal->setSrcRect(ConvertXML2Rect(UINode,"srcrect"));

	retVal->setPosition(Rect(0,0,retVal->getSrcRect().x2,retVal->getSrcRect().y2));
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));

	if (UINode->Attribute("hoversrcrect")!=NULL)	//setting the HoverSrcRect
	{
		imgUIImage.setSrcRect(ConvertXML2Rect(UINode,"hoversrcrect"));
		retVal->setHoverImage(imgUIImage);
	}else {	// else set the same like original Image only addBlitmode
		retVal->setHoverImage(*retVal);
	}

	if (UINode->Attribute("hoverblitmode"))
		retVal->setHoverBlitMode(ConvertXML2Blit(UINode,"hoverblitmode"));
	else
		retVal->setHoverBlitMode(IMAGE_BLTMODE_ADD);

	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));

	Point off=ConvertXML2Point(UINode,"offset");
	retVal->setOffset(-off.x,-off.y);

	if (UINode->Attribute("function")!=NULL)
	{
		string strFunction=UINode->Attribute("function");
		if(strFunction=="escape")
			retVal->setSendFlag(MM_KEYUP,sf::Keyboard::Escape);
	}

	if (UINode->Attribute("target")!=NULL)
	{
		retVal->setSendFlag(A3D_XMLMENU_NAVIGATION, iIDMessageCounter);
		string strTarget=UINode->Attribute("target");
		mapMessage2Target.insert(map<int, string>::value_type(iIDMessageCounter , strTarget));
		iIDMessageCounter++;
	}

	return retVal;
}
UIKeyRecorder* XMLDialogSystem::createKeyRecorder(TiXmlElement* UINode)
{
	UIKeyRecorder* retVal=new UIKeyRecorder();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	unsigned char key = *UINode->Attribute("value");
	if (key>='A' && key<='Z'){
        key-='A';
	}
	if (key>='a' && key<='z'){
        key-='a';
	}
	if (key>='0' && key<='9'){
        key-='0';
        key+=sf::Keyboard::Num0;
	}
	Event tmp (MM_KEYDOWN,(int)key,0);
	retVal->setRecordedKey(&tmp);
	if (UINode->Attribute("hoverblitmode"))
		retVal->setHoverBlitMode(ConvertXML2Blit(UINode,"hoverblitmode"));
	if (UINode->Attribute("blitmode"))
		retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));

	vecValueObjs.push_back(retVal);
	return retVal;
}

UISprite* XMLDialogSystem::createLabel(TiXmlElement* UINode)
{
	UISprite* retVal=new UISprite();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	retVal->cloneImage(imgUIImage);
	if (UINode->Attribute("srcrect"))
	{
		retVal->setSrcRect(ConvertXML2Rect(UINode,"srcrect"));
	}else{
		if (UINode->Attribute("text")){
			string strLabel=UINode->Attribute("text");
			int wid=strLabel.length()*fntTextFont.getFontWidth();
			int hei=fntTextFont.getFontHeight();
			retVal->resize(wid, hei);
			fntTextFont.PrintAt(*retVal,0,0,strLabel.c_str());
		}else{	// Fals weder text noch srcrect Attribut vorhanden ist, initialisiere leeres Object
			retVal->resize(0,0);// geht hier (0,0)?
			retVal->setSrcRect(Rect(0,0,0,0));
		}
	}
	retVal->setPosition(RECT_INVALID,RECT_INVALID,retVal->getSrcRect().x2,retVal->getSrcRect().y2);
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	Point off=ConvertXML2Point(UINode,"offset");
	retVal->setOffset(-off.x,-off.y);
	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));
	return retVal;
}
UITextField* XMLDialogSystem::createTextfield(TiXmlElement* UINode)
{
	UITextField* retVal=new UITextField();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	retVal->setSize(ConvertXML2Int(UINode,"maxlength",10));
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));
	retVal->ActiveBackground=ConvertXML2Color(UINode,"background",0x888888);
	retVal->inActiveBackground=ConvertXML2Color(UINode,"inactivebackground",0x444444);
	retVal->CursorColor=ConvertXML2Color(UINode,"Cursor",0xFFFFFF);
	retVal->BlinkFreq=ConvertXML2Int(UINode,"blinkfreq",500);
	if (UINode->Attribute("value"))
		retVal->setValue(value(UINode->Attribute("value"),0));

	vecValueObjs.push_back(retVal);
	return retVal;
}
UICheckBox* XMLDialogSystem::createCheckBox(TiXmlElement* UINode)
{
	UICheckBox* retVal=new UICheckBox();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));
	retVal->setValue(value("",(int)ConvertXML2Bool(UINode,"checked")));
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	Point off=ConvertXML2Point(UINode,"offset");
	retVal->setOffset(-off.x,-off.y);
	vecValueObjs.push_back(retVal);
	return retVal;
}

UISprite* XMLDialogSystem::createScrollArea(TiXmlElement* UINode)
{
    // TODO: need to build a GUICLass for (optional) scroll a bitmap (horizontally / vertically)
	UIScrollArea* retVal=new UIScrollArea();
	Image content;
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	Rect tmpPosition = ConvertXML2Rect(UINode,"position");
    retVal->resize(tmpPosition.getWidth(), tmpPosition.getHeight());
	retVal->setPriority(20);
	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));
    using std::pair;
    auto allText = vector<pair<string,string>>();
    int internalHeight=0;
    ImageText* currentFont = &fntTextFont;;
    TiXmlNode* child=UINode->FirstChild();
	while(child!=NULL){
        pair<string, string> entry;
        switch(child->Type()){
            case TiXmlNode::NodeType::ELEMENT:{
                string nodename = child->Value();
                if (nodename=="headline"){
                    string title = child->FirstChild()->ToText()->Value();
                    entry = std::make_pair("headline", title);
                    currentFont = &fntTitleFont;
                }
                break;
            }
            case TiXmlNode::NodeType::TEXT:{
                string text = child->ToText()->Value();
                entry = std::make_pair("text", text);
                break;
            }
            default:{
                string error = "Not Found:";
                error.append(child->Value());
                entry = std::make_pair("text",error);
                break;
            }
        }
        int msgHeight = UILayouter::formatText(entry.second, retVal->getWidth(), *currentFont).size();
        internalHeight += msgHeight * (currentFont->getFontHeight()+2);

        allText.push_back(entry);
	    child=child->NextSibling();
	}
	content.resize(tmpPosition.getWidth(), internalHeight);
	retVal->setPosition(tmpPosition);
	//content.setSrcRect(Rect(0,0, tmpPosition.getWidth(), tmpPosition.getHeight()));
	int yco = 0;
	for(pair<string, string> paragraph : allText){
        string lineType = paragraph.first;
        string lineText = paragraph.second;
        currentFont = &fntTextFont;
        if (lineType=="headline"){
            currentFont = &fntTitleFont;
        }
        for(auto line:UILayouter::formatText(lineText, retVal->getWidth(), *currentFont)){
            currentFont->PrintAt(content,1,yco+1,line.c_str(), IMAGE_BLTMODE_SUB);
            currentFont->PrintAt(content,0,yco+0,line.c_str(), IMAGE_BLTMODE_TRANS);
            yco += currentFont->getFontHeight()+2;
        }
	}
	retVal->setImage(content);
    return retVal;
}

UIScrollBar* XMLDialogSystem::createScrollBar(TiXmlElement* UINode)
{
	UIScrollBar* retVal;
	if (UINode->Attribute("type")!=NULL)
	{
		string strType=UINode->Attribute("type");
		if (strType=="vertical")
			retVal=new UIScrollBar(UIScrollBar::VERTICAL);
		else
			retVal=new UIScrollBar(UIScrollBar::HORIZONTAL);
	}else{
		retVal=new UIScrollBar(UIScrollBar::HORIZONTAL);
	}
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	if (UINode->Attribute("position")!=NULL)
	{
		retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	}
	int min,max,val, buttonspeed,pagespeed, buttonsize;
	min			=ConvertXML2Int(UINode,"min",0);
	max			=ConvertXML2Int(UINode,"max",100);
	val			=ConvertXML2Int(UINode,"value",0);
	buttonspeed	=ConvertXML2Int(UINode,"buttonspeed",1);
	pagespeed	=ConvertXML2Int(UINode,"pagespeed",(max-min)/4);
	buttonsize	=ConvertXML2Int(UINode,"buttonsize",max/10+1);

	retVal->setButtonProperties(max, min,buttonspeed, pagespeed, buttonsize);
	retVal->setValue(value("",val));

	retVal->setBlitMode(ConvertXML2Blit(UINode, "blitmode"));
	vecValueObjs.push_back(retVal);
	return retVal;
}

UIRadioButton* XMLDialogSystem::createRadioButton(TiXmlElement* UINode)
{
	static int iRadioID=1;
	UIRadioButton* retVal=new UIRadioButton();
    if (UINode->Attribute("name")!=NULL){
        retVal->setName(UINode->Attribute("name"));
    }
	retVal->setPriority(20);
	retVal->setRadioGroup(ConvertXML2Int(UINode,"group"));
	retVal->setValue(value("",(int)(ConvertXML2Bool(UINode,"checked"))));
	retVal->setPosition(ConvertXML2Rect(UINode,"position"));
	retVal->setRadioID(iRadioID++);
	retVal->setBlitMode(ConvertXML2Blit(UINode,"blitmode"));
	Point off=ConvertXML2Point(UINode,"offset");
	retVal->setOffset(-off.x,-off.y);
	vecValueObjs.push_back(retVal);
	return retVal;
}

Rect XMLDialogSystem::ConvertXML2Rect(TiXmlElement* Node,string strAttr)
{
	Rect retVal;
	int x=0,y=0,w=0,h=0;

	if (Node->Attribute(strAttr.c_str())!=NULL)
		if (sscanf(Node->Attribute(strAttr.c_str()),"%d,%d,%d,%d",&x,&y,&w,&h)!=EOF)
			retVal.setPosition(x,y,w,h);

	return retVal;
}
Point XMLDialogSystem::ConvertXML2Point(TiXmlElement* Node,string strAttr)
{
	Point retVal;

	if (Node->Attribute(strAttr.c_str())!=NULL)
		sscanf(Node->Attribute(strAttr.c_str()),"%d,%d",&(retVal.x),&(retVal.y));

	return retVal;
}
bool XMLDialogSystem::ConvertXML2Bool(TiXmlElement* Node,string strAttr)
{
	bool retVal=false;
	if (Node->Attribute(strAttr.c_str())!=NULL)
	{
		string Attr=Node->Attribute(strAttr.c_str());
		retVal=(Attr=="true");
	}

	return retVal;
}
int XMLDialogSystem::ConvertXML2Blit(TiXmlElement* Node,string strAttr)
{
	int retVal=IMAGE_BLTMODE_TRANS;

	if (Node->Attribute(strAttr.c_str())!=NULL)
	{
		string Attr=Node->Attribute(strAttr.c_str());
		if (Attr=="fast")
			retVal=IMAGE_BLTMODE_FAST;
		if (Attr=="half")
			retVal=IMAGE_BLTMODE_HALF;
		if (Attr=="add")
			retVal=IMAGE_BLTMODE_ADD;
		if (Attr=="sub")
			retVal=IMAGE_BLTMODE_SUB;
	}

	return retVal;
}
int XMLDialogSystem::ConvertXML2Int(TiXmlElement* Node,string strAttr, int iDefault)
{
	int retVal=iDefault;
	if (Node->Attribute(strAttr.c_str())!=NULL)
		sscanf(Node->Attribute(strAttr.c_str()),"%d",&retVal);

	return retVal;
}
int XMLDialogSystem::ConvertXML2Color(TiXmlElement* Node,string strAttr, int iDefault)
{
	int retVal=iDefault;
	if (Node->Attribute(strAttr.c_str())!=NULL)
		sscanf(Node->Attribute(strAttr.c_str()),"%x",&retVal);

	return retVal;
}

void XMLDialogSystem::displayDialog(std::string strName)
{
	map<string, int>::iterator ilt=mapName2Index.find(strName);
	if (ilt!=mapName2Index.end())
	{
		iActiveDialog=(*ilt).second;

	} else {
		iActiveDialog=-1;
		MessageManager::handleEvent(new Event(A3D_XMLMENU_DISAPPEAR,0,0));
	}
}

void XMLDialogSystem::setTextFont(ImageText &newFont)
{
	fntTextFont.cloneFont(newFont);
}

void XMLDialogSystem::setTitleFont(ImageText &newFont)
{
	fntTitleFont.cloneFont(newFont);
}

UIElement* XMLDialogSystem::getElement(std::string strName)
{
	UIElement*	retVal=NULL;
	for (unsigned int x=0;x<vecDialogs.size();x++)
	{
		retVal=vecDialogs[x]->getElement(strName);
		if(retVal!=NULL)
			break;
	}
	return retVal;
}

bool XMLDialogSystem::paint(Image& backBuffer)
{

	if (iActiveDialog>-1)
		return vecDialogs[iActiveDialog]->paint(backBuffer);
	else
		return true;
}

bool XMLDialogSystem::handleEvent(Event* evt)
{
	if (evt->Type==MM_KEYUP && evt->wData==sf::Keyboard::Escape)	// Escape Key will toggle the Menu...or jumps one Level up
	{
		if (iActiveDialog==-1)	// Bei Escape activiere das Menu
		{
			iActiveDialog=0;
			evt->Type=MM_MOUSEMOVE;		// Das Event umbauen zu MouseMove(0/0)
			evt->lData=0;
			MessageManager::handleEvent(new Event(A3D_XMLMENU_APPEAR,0,0));
			return true;				// Und an alle nachfolgenden Komponenten schicken(disable Hovers)
		}else{	//falls aktiviert aktiviere das ParentMenu
			map<int, string>::iterator ilt=mapIndex2Parent.find(iActiveDialog);
			if (ilt!=mapIndex2Parent.end())	// Key found?
			{
				string strParentName=(*ilt).second;
				displayDialog(strParentName);
			}else{	// not found--> Do not display any Dialog
				iActiveDialog=-1;
				MessageManager::handleEvent(new Event(A3D_XMLMENU_DISAPPEAR,0,0));
			}
		}
	}

	if (evt->Type==A3D_XMLMENU_NAVIGATION)		// Button to Submenu pressed?
	{
		map<int, string>::iterator ilt=mapMessage2Target.find(evt->wData);
		if (ilt!=mapIndex2Parent.end())	// Key found?
		{
			string strTargetName=(*ilt).second;
			displayDialog(strTargetName);
			evt->Type=MM_MOUSEMOVE;		// Das Event umbauen zu MouseMove(0/0)
			evt->lData=0;
			vecDialogs[iActiveDialog]->handleEvent(evt);	// an aktiven Dialog schicken
			return false;	// nicht weiterreichen
		}
	}

	if (iActiveDialog>-1)
		vecDialogs[iActiveDialog]->handleEvent(evt);

	if (iActiveDialog==-1)
		return true;

	if (evt->Type==MM_MOUSEMOVE || evt->Type==MM_LBUTTONDOWN || evt->Type==MM_RBUTTONDOWN)
		return false;

	return true;
}


value XMLDialogSystem::getValue(std::string strName)
{
	value	retVal("",-1);
	for (unsigned int x=0;x<vecValueObjs.size();x++)
	{
		if (vecValueObjs[x]->getName()==strName)
		{
			retVal=vecValueObjs[x]->getValue();
			break;
		}
	}
	return retVal;
}
void XMLDialogSystem::setValue(std::string strName, value val)
{
	for (unsigned int x=0;x<vecValueObjs.size();x++)
	{
		if (vecValueObjs[x]->getName()==strName)
		{
			vecValueObjs[x]->setValue(val);
			break;
		}
	}
}

void XMLDialogSystem::load()
{
	string strLoadFile=strFileName.substr(0,strFileName.length()-3)+"dat";
	FILE* loadFile=fopen(strLoadFile.c_str(),"rb");
	if(loadFile!=NULL)
	{
		bool another=true;
		while(another)
			another=readValue(loadFile);
		fclose(loadFile);
	}

}

void XMLDialogSystem::save()
{
	string strSaveFile=strFileName.substr(0,strFileName.length()-3)+"dat";
	FILE* saveFile=fopen(strSaveFile.c_str(),"wb");
	if(saveFile!=NULL)
	{
		for (unsigned int x=0;x<vecValueObjs.size();x++)
		{
			value val=vecValueObjs[x]->getValue();
			string strName=vecValueObjs[x]->getName();
			writeValue(strName, val, saveFile);
		}
		fclose(saveFile);
	}
}

void XMLDialogSystem::writeValue(string strName, value val, FILE *stream)
{
	int iType=VALUE_NAME;
	fwrite(&iType,sizeof(int),1,stream);
	iType=strName.length()+1;
	fwrite(&iType,sizeof(int),1,stream);
	fwrite(strName.c_str(),sizeof(char),strName.length(),stream);
	iType=0;
	fwrite(&iType,sizeof(char),1,stream);
	iType=VALUE_INT;
	fwrite(&iType,sizeof(int),1,stream);
	fwrite(&val.second,sizeof(int),1,stream);
	iType=VALUE_STRING;
	fwrite(&iType,sizeof(int),1,stream);
	iType=val.first.length()+1;
	fwrite(&iType,sizeof(int),1,stream);
	fwrite(val.first.c_str(),sizeof(char),val.first.length(),stream);
	iType=0;
	fwrite(&iType,sizeof(char),1,stream);
}
bool XMLDialogSystem::readValue(FILE *stream)
{
	bool retVal=false;	// if everything runs fine, return true
	bool first,second, third;
	value	myVal;
	unsigned int iType=0, iSize=0;
	string strName;
	char* cpMem=NULL;

	first=second=third=false;

	if (fread(&iType,sizeof(int),1,stream)==1)	// read first DWORD ?
	{
		if (iType==VALUE_NAME)					// is it A VALUE_NAME ?
		{
			if (fread(&iSize,sizeof(int),1,stream)==1) // READ THE SIZE
			{
				cpMem=new char[iSize];
				if (fread(cpMem,sizeof(char), iSize,stream)==iSize)
				{
					strName=cpMem;	// OK..Everything is fine
					first=true;
				}
				delete cpMem;
			}
		}
	}
	if (fread(&iType,sizeof(int),1,stream)==1)	// read first DWORD ?
	{
		if (iType==VALUE_INT)					// is it A VALUE_INT ?
		{
			if (fread(&iSize,sizeof(int),1,stream)==1) // READ THE VALUE OF INT
			{
				myVal.second=iSize;	// OK everything is fine
				second=true;
			}
		}
	}
	if (fread(&iType,sizeof(int),1,stream)==1)	// read first DWORD ?
	{
		if (iType==VALUE_STRING)					// is it A VALUE_NAME ?
		{
			if (fread(&iSize,sizeof(int),1,stream)==1) // READ THE SIZE
			{
				cpMem=new char[iSize];
				if (fread(cpMem,sizeof(char), iSize,stream)==iSize)
				{
					myVal.first=cpMem;	// OK..Everything is fine
					third=true;
				}
				delete cpMem;
			}
		}
	}
	retVal=first&& second&& third;

	if (retVal)	// if reading all parameters is fine.. finally set the UIElement to the Value!
		setValue(strName,myVal);


	return retVal;
}

std::vector<std::string> XMLDialogSystem::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

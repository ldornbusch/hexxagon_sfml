// XMLDialogSystem.h: interface for the XMLDialogSystem class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UILayouter.h"
#include "UIRadioButton.h"
#include "UIScrollBar.h"
#include "UITextfield.h"
#include "UIKeyRecorder.h"
#include "hasValue.h"
#include "../All2D/All2D_Base/ImageText.h"

// TODO: create Enum
#define VALUE_NAME		0xAAAAAAAA
#define VALUE_STRING	0xFF00FF00
#define VALUE_INT		0x00FF00FF

class XMLDialogSystem  : public xElement
{
public:
	void save();
	void load();
	value getValue(std::string strName);
	void setValue(std::string strName, value val);
	void setFont(ImageText& newFont);
	bool paint(Image& backBuffer);
	bool handleEvent(Event* evt);
	void displayDialog(std::string strName);
	void init(Image& imgElements);
	UIElement* getElement(std::string strName);
	XMLDialogSystem(std::string fileName);
	virtual ~XMLDialogSystem();
//	virtual void getGFX(Image& imgGFX);
private:
	UILayouter* initDialog(TiXmlElement* dialogNode);
	UIElement* initUIElement(TiXmlElement* UINode, UILayouter* Dialog);
	UIHoverButton* createButton(TiXmlElement* UINode);
	UISprite* createLabel(TiXmlElement* UINode);
	// These UIElements will be additional hold in the vecValueObjs Vector, the values of them will be loaded/saved to disk
	UITextField* createTextfield(TiXmlElement* UINode);
	UICheckBox* createCheckBox(TiXmlElement* UINode);
    UISprite* createScrollArea(TiXmlElement* UINode);
	UIScrollBar* createScrollBar(TiXmlElement* UINode);
	UIRadioButton* createRadioButton(TiXmlElement* UINode);
	UIKeyRecorder* createKeyRecorder(TiXmlElement* UINode);

	Rect ConvertXML2Rect(TiXmlElement* Node,string strAttr);
	Point ConvertXML2Point(TiXmlElement* Node,string strAttr);
	bool ConvertXML2Bool(TiXmlElement* Node,string strAttr);
	int  ConvertXML2Blit(TiXmlElement* Node,string strAttr);
	int  ConvertXML2Int(TiXmlElement* Node,string strAttr, int iDefault=0);
	int  ConvertXML2Color(TiXmlElement* Node,string strAttr, int iDefault=0);
	static int iIDMessageCounter;
	TiXmlDocument	xmlDoc;
	bool blnInitialized;
	int	iActiveDialog;

	std::vector<UILayouter*>	vecDialogs;
	std::vector<hasValue*>		vecValueObjs;	// to Load or Save the Settings...
	std::map<string,int>	mapName2Index;	// Linkt TargetNamen->DialogIndex
	std::map<int,string>	mapMessage2Target;	// To find an Target to a Message
	std::map<int,string>	mapIndex2Parent;	// To find the Parent of an Index
	std::map<string, value>	mapKeyValue;	// for every UIElement except buttons and labels it saves the value..in a string(?)
	Image imgUIImage;	//Bild mit den Buttons
	ImageText fntDialogFont;
protected:
	bool readValue(FILE *stream);
	void writeValue(string strName, value val, FILE* stream);
	string strFileName;
};

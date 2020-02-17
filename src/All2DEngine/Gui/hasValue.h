// hasValue.h: Schnittstelle für die Klasse hasValue.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <string>
using std::pair;

typedef  pair<string, int> value;

class hasValue
{
public:
	virtual std::string getName()=0;
	virtual value getValue()=0;
	virtual void setValue(value)=0;
	hasValue(){};
	virtual ~hasValue(){};

};


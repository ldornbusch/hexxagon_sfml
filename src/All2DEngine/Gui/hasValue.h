// hasValue.h: Schnittstelle für die Klasse hasValue.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASVALUE_H__C5535092_77E9_4604_8D48_3EB4B0DDF6D9__INCLUDED_)
#define AFX_HASVALUE_H__C5535092_77E9_4604_8D48_3EB4B0DDF6D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>

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

#endif // !defined(AFX_HASVALUE_H__C5535092_77E9_4604_8D48_3EB4B0DDF6D9__INCLUDED_)

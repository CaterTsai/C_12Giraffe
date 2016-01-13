#ifndef CT_12GIRAFFE_COLORMGR
#define CT_12GIRAFFE_COLORMGR

#include "ofMain.h"

class colorMgr
{
public:

#pragma region get & set
	void setForeColor(ofColor& c)
	{
		_fore = c;
	}

	void setBackColor(ofColor& c)
	{
		_back = c;
	}

	ofColor&	getForeColor()
	{
		return _fore;
	}

	ofColor& getBackColor()
	{
		return _back;
	}
#pragma endregion

	void changeColor()
	{
		swap(_fore, _back);
	}

private:
	ofColor	_fore, _back;
//-------------------
//Singleton
//-------------------
public:
	static colorMgr* GetInstance()
	{
		if(pInstance == 0)
		{
			pInstance = new colorMgr;
		}
		return pInstance;
	};
	static void Destroy()
	{
		if(pInstance != 0)
		{
			delete pInstance;
		}
	}

private:
	colorMgr()
		:_fore(0)
		,_back(255)
	{};
	colorMgr(colorMgr const&);
	void operator=(colorMgr const&);
	static colorMgr *pInstance;
};

#endif // !CT_12GIRAFFE_COLORMGR

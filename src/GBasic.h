#ifndef CT_12GIRAFFE_GBASIC
#define CT_12GIRAFFE_GBASIC

#include "constParameter.h"
#include "GParameter.h"
#include "drawMgr.h"

#pragma region IGBasic
class IGBasic
{
public:
	virtual void setup() = 0;
	virtual void update(float fDelta) = 0; 
	virtual void draw() = 0;
	virtual void reset() = 0;
	virtual void add(int node, int key) = 0;
};
#pragma endregion

#pragma region GBasic
template<class T>
class GBasic : public IGBasic
{
public:
	GBasic()
		:_eType(eGiraffeType::eGiraffeNum)
		,_fDuration(0.0)
	{}

	GBasic(eGiraffeType eType, float fDuration)
		:_eType(eType)
		,_fDuration(fDuration)
	{};

	virtual void setup(){};
	virtual void update(float fDelta)
	{
		auto Iter_ = _elementList.begin();
		while(Iter_ != _elementList.end())
		{
			Iter_->update(fDelta);
			if(Iter_->canRemove())
			{
				Iter_ = _elementList.erase(Iter_);
			}
			else
			{
				Iter_++;
			}
		}
	};
	virtual void draw()
	{
		for(auto& Iter_ : _elementList)
		{
			Iter_.draw();
		}
	};
	virtual void reset()
	{
		_elementList.clear();
	};

	virtual void add(int node, int key)
	{
		_elementList.push_back(T(_fDuration));
	};

	//--------------------------------------------
	eGiraffeType getType() const
	{
		return _eType;
	}

	float getDuration() const
	{
		return _fDuration;
	}

	void setDuration(const float duration)
	{
		_fDuration = duration;
	}

protected:
	eGiraffeType	_eType;
	float					_fDuration;

	list<T>				_elementList;
};
#pragma endregion

#pragma region IBasicUnit
class IBasicUnit
{
public:
	virtual void update(float fDelta) = 0;
	virtual void draw() = 0;
	virtual bool canRemove() = 0;
};
#pragma endregion

#endif // !CT_12GIRAFFE_GBASIC

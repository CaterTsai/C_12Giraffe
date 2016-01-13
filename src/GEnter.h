#ifndef CT_12GIRAFFE_GENTER
#define CT_12GIRAFFE_GENTER

#include "GBasic.h"
#include "ofxAnimatableFloat.h"

class EnterUnit : public IBasicUnit
{
public:
	EnterUnit(float fduration, int iside = 0);

	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;
private:
	enum eEnterState
	{
		eState_Enter	=	0
		,eState_Wait
		,eState_Exit
		,eState_Finish
	} _eUnitState;

	float								_fWaitTimer;
	float								_swingDegree;
	ofxAnimatableFloat	_animSwing, _animTongue;
	stSwingGiraffeP			_Giraffe;
};

class GEnter : public GBasic<EnterUnit>
{
public:
	GEnter()
		:GBasic(eGiraffe_Enter, 0.0)
		,_sideIdx(0)
	{
		for(int idx_ = 0; idx_ < 4; idx_++)
		{
			_sideList.push_back(idx_);
		}
	}

	GEnter(float fDuration)
		:GBasic(eGiraffe_Enter, fDuration)
		,_sideIdx(0)
	{
		for(int idx_ = 0; idx_ < 4; idx_++)
		{
			_sideList.push_back(idx_);
		}
	}

	 void add(int node, int key) override;
private:
	int							_sideIdx;
	vector<int>			_sideList;
};
#endif // !CT_12GIRAFFE_GENTER

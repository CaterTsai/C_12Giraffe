#ifndef CT_12GIRAFFE_GPOKEMON
#define CT_12GIRAFFE_GPOKEMON

#include "GBasic.h"
#include "ofxAnimatableFloat.h"
#include "ofxAnimatableOfPoint.h"
#include "ofxAnimatableOfColor.h"

class PokemonUnit : public IBasicUnit
{
public:
	PokemonUnit(float fduration);
	void update(float fDelta) override;
	void draw() override;
	bool canRemove() override;

private:
	enum ePokemonState
	{
		eState_BallIn	=	0
		,eState_Summon
		,eState_Open
		,eState_Waiting
		,eState_Close
		,eState_Back
		,eState_Ballout
		,eState_Finish
	}_eUnitState;

	float	_fWaitT, _fSummonT;
	stGiraffeP		_Giraffe;
	stOpenGiraffeP	_OpenGiraffe;
	stPokeBallP	_Pokeball;

	ofxAnimatableFloat	_animBallX, _animBallRotate, _animBallOpen;
	ofxAnimatableFloat	_animGiraffeScale, _animGiraffeOpen;
	ofxAnimatableOfPoint	_animGiraffePos;
	ofxAnimatableOfColor	_animGiraffeColor;
};

class GPokemon : public GBasic<PokemonUnit>
{
public:
	GPokemon()
		:GBasic(eGiraffe_Pokemon, 0.0)
	{}

	GPokemon(float fduration)
		:GBasic(eGiraffe_Pokemon, fduration)
	{}
};

#endif // !CT_12GIRAFFE_GPOKEMON

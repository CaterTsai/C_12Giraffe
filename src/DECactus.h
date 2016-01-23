#ifndef CT_12GIRAFFE_DECACUTS
#define CT_12GIRAFFE_DECACUTS

#include "DEParameter.h"

class DECacuts : public DEBasic<stCactusP>
{
public:
	static void draw(const stCactusP& param)
	{
		beginDraw(param);
		{
			ofPath outline_;
			CreateOutline(outline_, param);

			outline_.draw();

		}
		endDraw();
	}

private:
	static void CreateOutline(ofPath& path, const stCactusP& param)
	{
		path.clear();
		path.setFillColor(ofColor(param.fillcolor, param.falpha));
		path.setFilled(param.bFill);
		path.setStrokeWidth(param.flineWidth);
		path.setStrokeColor(ofColor(param.linecolor, param.falpha));

		float fBasic_ = param.fsize / 6.5;

		path.moveTo(-fBasic_, fBasic_ * 1.5);
		path.lineTo(-fBasic_, -fBasic_ * 1.5);
		path.arc(0, -fBasic_ * 1.5, fBasic_, fBasic_, 180, 0);
		path.lineTo(fBasic_, fBasic_ * 2.0);

		path.lineTo(fBasic_ * 2.0, fBasic_ * 2.0);
		path.arc(fBasic_ * 2.0, fBasic_ * 2.5, fBasic_ * 0.3, fBasic_ * 0.5,270, 90);
		path.lineTo(fBasic_, fBasic_ * 3.0);
		path.arc(fBasic_, fBasic_ * 2.5, fBasic_, fBasic_ * 0.5, 90, 180);
		path.lineTo(0 , fBasic_ * 2.0);


	}
};

#endif // !CT_12GIRAFFE_DECACUTS

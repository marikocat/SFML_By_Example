#pragma once

#include "Directions.h"
#include "Anim_Base.h"

class Anim_Directional : public Anim_Base
{
protected:
	void FrameStep();
	void CropSprite();
	void ReadIn(std::stringstream& l_stream);
};
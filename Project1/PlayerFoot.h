#pragma once
#include "PlayerBody.h"
#include "Vector3.h"
#include "Easing.h"
#include "Sprite.h"

class PlayerFoot
{
public: //�����o�֐�
	PlayerFoot();
	~PlayerFoot();

	void Init();
	void Set();
	void Update(RVector3& FaceCenterPos, bool IsDownBody, int BodyDis);
	void Draw(int offsetX, int offsetY, bool isleft, bool isright);

public: //�����o�ϐ�
	Vector3 FootLeftUpPosition;
	Easing ease;

	bool FootIsAction;
	bool IsFootUp;

	//�摜�n���h��
	UINT FootHandle;
	Sprite FootSprite;
};
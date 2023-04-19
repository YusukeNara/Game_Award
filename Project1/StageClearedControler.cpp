#include "StageClearedControler.h"
#include "InputManger.h"
#include "SChangeDir.h"

namespace
{
InputManger* inputManger = InputManger::Get();
}

void StageClearedControler::Init(StageSelecter *ptr)
{
	//���o������
	goalEffect.reset(new GoalEffects);
	goalEffect->Init();

	//UI������
	_go_select_button.Init(60, TexManager::LoadTexture("Resources/back.png"), 360, 90);
	x1 = 1280.0f * (1.0f / 4.0f);
	y1 = 720 * (8.0f / 9.0f);
	_go_next_button.Init(60, TexManager::LoadTexture("Resources/next.png"), 200, 90);
	x2 = 1280.0f * (3.0f / 4.0f);
	y2 = 720 * (8.0f / 9.0f);

	clearedBackSprite.Create(TexManager::LoadTexture("Resources/stageClear.png"));

	if (ptr != nullptr) {
		selecter = ptr;
	}

	//���͋֎~
	ctrl_state = CONTROL_NOT_ALLOW;
	//�ŏ��Ƀ��[�U�[���I��ł���
	_user_selecting = USER_SELECT_NEXT;
	if (selecter->SelectStageNum == 20) {
		_user_selecting = USER_SELECT_BACK;
	}

	frameCount = 0;

	isAllowSwitching = false;

	gameMainSprite.CreateRtexSprite(0);




	sepiaRate = 0.0f;
}

void StageClearedControler::Update()
{
	Update_CheckControlStates();

	Update_ControlMain();

	//�I�����m�F�ł�����A���o��؂�

}

void StageClearedControler::Draw(int rtHandle)
{
	//�w�i�`�悵�Ă���
	clearedBackSprite.DrawExtendSprite(0, 0, 1280, 720);
	clearedBackSprite.Draw();

	//�Q�[���{�҂̉摜��`�悷��
	gameMainSprite.DrawRTexSprite(rtHandle, LT.x, LT.y, RB.x, RB.y, 0, DirectX::XMFLOAT4{ 0.9f,0.9f,0.8f,sepiaRate });

	if (ctrl_state == CONTROL_NOT_ALLOW) { return; }

	//���̃N���X���̕`�惊�\�[�X�́A���삪�֎~����ĂȂ��Ƃ��͏�ɕ`�悳���

	//�S�[�����o�`��
	goalEffect->Draw();

	//UI�`��
	Draw_UI();

}

void StageClearedControler::ControlActivate()
{

	if (ctrl_state != CONTROL_NOT_ALLOW) { return; }

	Init(nullptr);

	//���o��ԂɈڍs
	ctrl_state = CONTROL_DIRECING;

	goalEffect->Play();
}

void StageClearedControler::ControlDisable()
{
	//�R���g���[��������
	ctrl_state = CONTROL_NOT_ALLOW;
}

void StageClearedControler::Update_CheckControlStates()
{
	//�L���X�g���Ă��̃^�C�~���O�ł͐����ň����悤�ɂ���
	int user_selecting = static_cast<int>(_user_selecting);

	//���[�g
	float rate = static_cast<float>(frameCount) / static_cast<float>(DIRECTING_FRAME);
	//�`����W�C�[�W���O���s
	LT = Rv3Ease::OutQuad(drawLT, targetLT, rate);
	RB = Rv3Ease::OutQuad(drawRB, targetRB, rate);

	//��ԑJ�ڂ̔�����s��
	switch (ctrl_state)
	{
	case StageClearedControler::CONTROL_NOT_ALLOW:
		//���ɂȂ��iActive�֐����Ă΂��܂Łj
		break;
	case StageClearedControler::CONTROL_DIRECING:
		//�K��t���[���o�߁A�܂��͓��͂����m
		frameCount++;

		sepiaRate = rate;
		if (frameCount > DIRECTING_FRAME)
		{
			sepiaRate = 1.0f;
			//UI�I��L����
			ctrl_state = CONTROL_ACTIVE;
		}
		if (inputManger->DecisionTrigger())
		{
			frameCount = DIRECTING_FRAME;
		}

		break;
	case StageClearedControler::CONTROL_ACTIVE:
		//UI�I���̓��́i�ǂ�����I�����Ă邩�H�j
		if (inputManger->LeftTrigger() && selecter->SelectStageNum != 20) { user_selecting = 0; }
		if (inputManger->RightTrigger()) { user_selecting = 1; }
		_user_selecting = static_cast<STAGE_CLEARED_USER_SELECTING>(user_selecting);

		//UI�I�����ꂽ
		if (inputManger->DecisionTrigger())
		{
			//�{�^��������
			if (user_selecting == 0) { _go_next_button.UI_Push(); }
			if (user_selecting == 1) { _go_select_button.UI_Push(); }

			ctrl_state = CONTROL_UI_SELECTED;
			SChangeDir::Get()->PlayChangingDirection();
		}

		break;

	case StageClearedControler::CONTROL_UI_SELECTED:

		break;

	default:
		break;
	}
}

void StageClearedControler::Update_ControlMain()
{
	switch (ctrl_state)
	{
	case StageClearedControler::CONTROL_NOT_ALLOW:
		//�������Ȃ�
		break;

	case StageClearedControler::CONTROL_DIRECING:
		//�C�[�W���O����Ȃ炱����



		break;

	case StageClearedControler::CONTROL_ACTIVE:
		//�I�𒆁A���͈ȊO�X�V


		break;

	case StageClearedControler::CONTROL_UI_SELECTED:
		//UI�I����X�V����

		if (SChangeDir::Get()->isChangeActivate) {
			isAllowSwitching = true;
		}

		break;

	default:
		break;
	}

	//UI�X�V
	_go_next_button.Update();
	_go_select_button.Update();

}

void StageClearedControler::Draw_UI()
{
	switch (_user_selecting)
	{
	case StageClearedControler::USER_SELECT_NEXT:
		if (selecter->SelectStageNum != 20) {
			_go_next_button.Draw(x1, y1, SELECTING_SCALE, SELECTING_SCALE);
		}
		_go_select_button.Draw(x2, y2);
		break;
	case StageClearedControler::USER_SELECT_BACK:
		if (selecter->SelectStageNum != 20) {
			_go_next_button.Draw(x1, y1);
		}
		_go_select_button.Draw(x2, y2, SELECTING_SCALE, SELECTING_SCALE);
		break;
	default:
		break;
	}
}
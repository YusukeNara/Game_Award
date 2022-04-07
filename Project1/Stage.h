#pragma once
#include <vector>
#include "Vector3.h"
#include "Easing.h"

/*���������傫���Ȃ肷���錜�O������ӏ���char�^�ɂ��Ă��܂�*/

enum MapchipData
{
	EMPTY_STAGE = 0,
	NONE = 1,
	BLOCK = 2,
	GOAL = 3,
	START = 4
};

class Stage final
{
public: //�V���O���g����
	static Stage* Get();
private:
	Stage();
	Stage(const Stage&) = delete;
	~Stage();
	Stage operator=(const Stage&) = delete;

public: //�T�u�N���X
	struct StageTileData
	{
		char* mapchip = nullptr;
		char stageNumber = 0;
		char offsetX = 0;
		char offsetY = 0;
		std::vector<Vector3> drawLeftUp = {};
		std::vector<Vector3> drawRightDown = {};
		size_t size = 1;
		unsigned char width = 1;
		unsigned char height = 1;
		unsigned char direction = 0;
		bool isFold = false;

		Easing stageEase = {};
		std::vector<Vector3> startPos = {};
		std::vector<Vector3> endPos = {};
		std::vector<Vector3> easePos = {};

		bool isTop = true;
	};
	struct StageData
	{
		char* stageTile = nullptr;
		char offsetX = 0;
		char offsetY = 0;
		unsigned char width = 1;
		unsigned char height = 1;
		std::vector<StageTileData> stageTileData;
		std::vector<char> stageOffsetX;
		std::vector<char> stageOffsetY;
	};

public: //�萔
	static const int blockSize;
	static const int halfBlockSize;

	Vector3 offset = { 0,0,0 };

private: //�ÓI�����o�ϐ�
	static int startPlayerPosX;
	static int startPlayerPosY;
	static unsigned char initFoldCount[4];

public: //�����o�֐�
	// ������
	void Init();
	// �X�V
	void Updata();
	// �`��
	void Draw(int offsetX, int offsetY);

	/// <summary>
	/// �X�e�[�W�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="foldCount"> �v���C���[���܂���(0�Ԃ����A���A���A�E) </param>
	/// <param name="fileHandle"> �X�e�[�W�t�@�C���̃p�X </param>
	/// <returns> 0�Ő����A0�ȊO�Ŏ��s </returns>
	int LoadStage(const char* fileHandle, unsigned char playerTileArray[4]);

	// �X�e�[�W��܂�E�J��
	int FoldAndOpen(const Vector3& playerPos, unsigned char foldCount[4]);
	// ���Z�b�g
	void Reset();
	// �����f�[�^�S�폜
	void DataClear();

	// �v���C���[��x����̊J�n�ʒu���擾
	inline static int GetStartPlayerPosX() { return startPlayerPosX; }
	// �v���C���[��x����̊J�n�ʒu���擾
	inline static int GetStartPlayerPosY() { return startPlayerPosY; }
	// �v���C���[�̐܂��񐔂̏�����Ԃ��擾
	static void GetInitFoldCount(unsigned char foldCount[4]);
	// �X�e�[�W�^�C���̃f�[�^���擾
	inline StageTileData* GetStageTileData(const short& stageNumber, const short& stageTileNumber);
	// �X�e�[�W�̃f�[�^���擾
	inline StageData* GetStageData(const short& stageNumber);
	// �S�X�e�[�W�̃f�[�^���擾
	inline StageData* GetAllStageData();
	// Stagedata�̃T�C�Y���擾
	size_t GetStageDataSize();
	// Stagetiledata�̃T�C�Y���擾
	size_t GetStageTileDataSize(int i);
	// �X�e�[�W�̉������擾
	char GetStageWidth(int i);
	// �X�e�[�W�̏c�����擾
	char GetStageHeight(int i);
	// �C�ӂ�StageTile�̍������擾
	char GetStageTileHeight(int i, int j);
	// �C�ӂ�StageTile�̕����擾
	char GetStageTileWidth(int i, int j);
	// �C�ӂ̏ꏊ�̃}�b�v�`�b�v�����擾
	char GetStageMapchip(int i, int j, int mapchipPos);
	// �C�ӂ̍��W����ǂ�StageTile�ɂ��邩���擾
	bool GetPositionTile(Vector3 center, int i, int j);
	// �X�e�[�W�^�C����X���̃I�t�Z�b�g��Ԃ�
	int GetStageTileOffsetX(int i, int j);
	// �X�e�[�W�^�C����Y���̃I�t�Z�b�g��Ԃ�
	int GetStageTileOffsetY(int i, int j);
	//�C�ӂ̕����ɓ���̃}�b�v�`�b�v�����邩�ǂ���
	bool IsNeighberMapchip(int i, int j, int MapchipPos, MapchipData mapchipData);

private:
	// �X�e�[�W��܂�
	int Fold(unsigned char playerTile[4], const unsigned char& direction, const size_t& onPlayerStage, const size_t& onPlayerStageTile, const size_t& moveStageData);
	// �X�e�[�W���J��
	int Open(unsigned char playerTile[4], const unsigned char& direction, const size_t& onPlayerStage, const size_t& moveStageTile, const size_t& moveStageData);

	// �C�[�W���O�̏�����
	void EaseingInit(const size_t& onPlayerStage, const size_t& moveStageData, const int& direction);
	// �C�[�W���O�̍X�V
	void EaseingUpdate();
	// ��ԏ�̃X�e�[�W�^�C����T��
	int SearchTopStageTile();

private: //�����o�ϐ�
	std::vector<StageData> stageData;
	std::vector<StageData> initStageData;
};
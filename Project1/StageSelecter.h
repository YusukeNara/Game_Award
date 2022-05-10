#pragma once
#include <memory>
#include <array>
#include <TexManager.h>
#include <Sprite.h>
#include <Raki_Input.h>

//ステージ選択を管理する
class StageSelecter 
{
private:
	//ステージ本編を管理するクラスのポインタ（参照しているだけなのでweak_ptrにしたい）

public:
	StageSelecter();
	~StageSelecter();

	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();
	//終了
	void Finalize();

	//ゲーム本編へ遷移するフラグ
	bool GetMoveGameMain() { return isChanging_GameMain; }

private:
	//ステージ選択画面のリソース
	std::array<Sprite, 20> selectImg_1_4;
	std::array<Sprite, 20> selectImg_5_8;
	std::array<Sprite, 20> selectImg_9_12;

	//現在表示するステージのページ
	enum STAGE_PAGE
	{
		page_1_4,
		page_5_8,
		page_9_12,
	};
	STAGE_PAGE nowpage;		//現在のページ
	STAGE_PAGE nextpage;	//前のページ
	STAGE_PAGE displayPage;	//表示するページ

	enum PAGE_MOVE_DIR
	{
		is_front,
		is_back,
	};
	PAGE_MOVE_DIR pageMoveDir;

	//現在の状態
	enum NOW_SELECTER_STATE
	{
		is_selecting,				//選択中（ステージ番号の入力を受け付ける）
		is_pageChange_waiting,		//ページチェンジ演出中
		is_stageSelected_waiting,	//ステージ選択完了、遷移演出実行中
	};
	NOW_SELECTER_STATE state;

	//表示番号
	int nowDisplayNum = 0;

	//ゲームメインへ遷移するフラグ
	bool isChanging_GameMain = false;

	//ロード関数（連番画像のためにint -> string変換）
	void LoadSprite();

	//ページ遷移のための入力検知、ページ状態切替
	void CheckToPageChangeInput();

	//ページ状態に応じた処理
	const int PAGECHANGE_FRAME_TIME = 19;
	void PageChange();

	//ステージ遷移のための入力検知
	const int NUMBOX_START_X = 325;
	const int NUMBOX_START_Y = 285;
	const int NUMBOX_SIZE = 130;
	const int NUMBOX_SPACE = 60;
	void CheckLoadStage(int boxnum);
	void CheckToStageChangeInput();

};


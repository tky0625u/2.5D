#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Character/Player/Player.h"

void GameScene::Event()
{
	//カメラ　更新===============================================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));  //角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_player->GetPos() + m_pos);          //座標 (プレイヤーの少し前)
	Math::Matrix Mat = RotX * Trans;                                                           //行列合成
	m_camera->SetCameraMatrix(Mat);                                                            //行列セット
	//===========================================================================================================================
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 20;
	m_ViewingAngle = 60;
	m_pos = { 0,3,-7 };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
	//===========================================================================================================================

	//地面　生成＆初期化=========================================================================================================
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();  //メモリ確保
	m_objList.push_back(ground);                                  //リストに追加
	//===========================================================================================================================

	//プレイヤー=================================================================================================================
	std::shared_ptr<Player>player = std::make_shared<Player>();
	m_player = player;
	m_objList.push_back(player);
	//===========================================================================================================================
}

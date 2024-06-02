﻿#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Ground/Ground.h"
#include"../../Object/Character/Player/Magic/Magic.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/Character/Enemy/EnemyManager/EnemyManager.h"

void GameScene::Event()
{

	//カメラ　更新===============================================================================================================
	
	//プレイヤー情報取得===================================
	static float playerAngleY = 0;
	static Math::Vector3 playerPos = {};
	if (m_player.expired() == false)
	{
		playerAngleY = m_player.lock()->GetAngle();
		playerPos = m_player.lock()->GetPos();
		m_EnemyManager.lock()->SetPlayerPos(playerPos);
	}
	//=====================================================

	//行列更新=================================================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));      //角度
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(playerAngleY));  //角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                                   //座標 (プレイヤーの少し前)
	Math::Matrix PlayerTrans = Math::Matrix::CreateTranslation(playerPos);                         //プレイヤー座標
	Math::Matrix Mat = RotX * Trans * RotY * PlayerTrans;                                          //行列合成
 	m_camera->SetCameraMatrix(Mat);                                                                //行列セット
	//=========================================================================================================================

	//===========================================================================================================================
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 20;
	m_angleY = 0;
	m_ViewingAngle = 60;
	m_pos = { 0,5,-5 };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
	//===========================================================================================================================

	//地面　生成＆初期化=========================================================================================================
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();  //メモリ確保
	m_objList.push_back(ground);                                  //リストに追加
	//===========================================================================================================================

	//プレイヤー=================================================================================================================
	std::shared_ptr<Magic>magic = std::make_shared<Magic>();  //メモリ確保
	m_player = magic;                                         //プレイヤー変数に格納
	m_objList.push_back(magic);                               //リストに追加
	//===========================================================================================================================

	//敵=========================================================================================================================
	std::shared_ptr<EnemyManager>enemy = std::make_shared<EnemyManager>();  //メモリ確保
	m_EnemyManager = enemy;                                                 //敵変数に格納
	m_objList.push_back(enemy);                                             //リストに追加
	//===========================================================================================================================

	//タイマー===================================================================================================================
	std::shared_ptr<TimerManager>timer = std::make_shared<TimerManager>();  //メモリ確保
	m_objList.push_back(timer);                               //リストに追加
	//===========================================================================================================================
}

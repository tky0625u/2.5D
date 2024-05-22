﻿#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Ground/Ground.h"

void GameScene::Event()
{
	//カメラ　更新===============================================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));  //角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                               //座標
	Math::Matrix Mat = RotX * Trans;                                                           //行列合成
	m_camera->SetCameraMatrix(Mat);                                                            //行列セット
	//===========================================================================================================================
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 30;
	m_ViewingAngle = 60;
	m_pos = { 0,3,-5 };
	m_camera = std::make_unique<KdCamera>();  //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);        //視野角設定
	//===========================================================================================================================

	//地面　生成＆初期化=========================================================================================================
	std::shared_ptr<Ground> ground = std::make_shared<Ground>();  //メモリ確保
	ground->Init();                                               //初期化
	m_objList.push_back(ground);                                  //リストに追加
	//===========================================================================================================================
}
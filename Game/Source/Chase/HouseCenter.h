//--------------------------------------------------------------
//クラス名：HousePoint.h
//概要	  ：椅子の距離によって、得点をつけるクラス（Chairクラスの継承クラス）
//作成日　：2021/04/29
//作成者　：19CU0228 野田八雲
//更新履歴：2021/04/29 作成
//--------------------------------------------------------------

//インクルードカード
#pragma once

//インクルード
#include "CoreMinimal.h"
#include "Chair.h"
#include "HouseCenter.generated.h"

/**
 * 
 */
UCLASS()
class CHASE_API AHouseCenter : public AChair
{
	GENERATED_BODY()

public:
	//コンストラクタ
	AHouseCenter();

public:
	//椅子がすべて止まった時の処理
	void StopChair();

protected:
	//ゲームスタート時、または起動時に発動する処理
	virtual void BeginPlay() override;

public:
	//毎フレーム更新処理
	virtual void Tick(float DeltaTime) override;

protected:
	//確認用メッシュコンポーネント
	UPROPERTY(EditAnyWhere, BluePrintReadWrite)
		UStaticMeshComponent* m_pConfirmMesh;

private:

	//得られるポイント
	int m_getPoint;

	//自分自身の座標
	FVector m_thisLocation;

	//椅子(Chairクラス)の座標取得用
	FVector m_ChairLocation;

	//ハウスの中心座標と椅子の座標の差を格納する座標
	//計算する方法は中心から椅子のX,Y軸の面積をつかって距離を計算する
	float m_differenceLocation;
	
};

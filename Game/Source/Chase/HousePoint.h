//--------------------------------------------------------------
//クラス名：HousePoint.h
//概要	  ：椅子の距離によって、得点をつけるクラス
//作成日　：2021/04/23
//作成者　：19CU0228 野田八雲
//更新履歴：2021/04/23 作成
//--------------------------------------------------------------

//インクルードカード
#pragma once

//インクルード
#include"Engine/Engine.h"			// スクリーンログ出力用
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HousePoint.generated.h"

//前方宣言
class UStaticMeshComponent;

UCLASS()
class CHASE_API AHousePoint : public AActor
{
	GENERATED_BODY()
	
public:	
	//コンストラクタ
	AHousePoint();

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
	UPROPERTY(EditAnyWhere,BluePrintReadWrite)
		UStaticMeshComponent* m_pConfirmMesh;

private:

	//得られるポイント
	int m_getPoint;

	//自分自身の座標
	FVector m_thisLocation;

	//椅子(Chairクラス)の座標取得用
	FVector m_ChairLocation;

	//自分自身の座標と椅子の座標の差を取得する変数(発射する前)
	FVector m_prevdifferenceLocation;

	//した後の座標
	FVector m_differenceLocation;

};

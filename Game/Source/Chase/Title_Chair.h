//------------------------------------------------------------------
//クラス名：Title_Chair.h
//概要	  ：タイトルの椅子の動き制御
//作成日　：2021/05/11
//作成者　：19CU0228 野田八雲
//概要	　：2021/05/11 クラス作成
//------------------------------------------------------------------

//インクルードカード
#pragma once

//インクルード
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Title_Chair.generated.h"

//前方宣言
class UBoxComponent;
class USkeltalMeshComponent;
class USceneComponent;

UCLASS()
class CHASE_API ATitle_Chair : public AActor
{
	GENERATED_BODY()
	
public:	
	//コンストラクタ
	ATitle_Chair();

protected:
	//ゲームスタート時、または生成時に呼ばれる処理
	virtual void BeginPlay() override;

public:	
	//毎フレーム更新処理
	virtual void Tick(float DeltaTime) override;

private:

	//椅子移動
	void MoveChair(float deltaTime_);

	//椅子を消す処理
	void DestroyChair();

	//時間取得
	float m_movetime_;

	//表示時間（現在）
	float m_visibletime_;

	//この時間を超えたら表示させる時間（椅子ごとに設定できる）
	UPROPERTY(EditAnywhere)
	    float m_visibletimemax_;

	//この時間を超えたら止める
	UPROPERTY(EditAnywhere)
		float m_stopchairtime_;

	UPROPERTY(EditAnywhere)
		float m_location_x_;

	//椅子カウント
	float m_chaircnt_;

	UPROPERTY(EditAnywhere)
	float m_chaircntmax_;

public:

	UPROPERTY()
		USceneComponent* m_pbase_;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		UBoxComponent* m_pboxcomponent_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* m_pstaticmeshcomp_;

};

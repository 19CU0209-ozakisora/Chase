// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "HouseCenter.h"
#include "Instance.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

// 2021/05/10 尾崎 コメント化(試作で作ったもの)
/*struct FChair
{
	AChair* chair_obj_;

	//2点間の距離を格納する変数
	float Vectormeter_;
};
*/

UCLASS(BluePrintable)
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


//---------------------------------------------------------
// 尾崎 蒼宙
private:

	bool TimeCheck(float _deltatime);

	float time_cnt_;

	void AddScore();

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<APlayerchara*> m_players_;		// Player管理用

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<AChair*> m_chairs_;				// Chair管理用(得点計算処理があるので構造体の方が良いかも)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_event_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_chair_create_time_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		float m_switch_level_time;			// レベル遷移の時間

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		int m_event_cnt_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		int m_nowroundnum_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		int m_maxroundnum_;					// 椅子を投げる最大の数

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		TArray<int> m_event_round_;

	UFUNCTION(BluePrintCallable)
		void NextRound();

//---------------------------------------------------------
//2021/05/06:　野田　変数、関数追加
public:
	//椅子がすべて止まった時の処理
	void StopChair();

	//椅子の距離ソート用
	void ChairSort();

	//得点計算
	void SetPoint();

	//ウィジェット出力1P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint1P()const { return m_teamPoint1P; }

	//ウィジェット出力2P
	UFUNCTION(BlueprintCallable, Category = "My Functions")
		int GetPoint2P()const { return m_teamPoint2P; }

	//チームポイント（1P用）
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint1P;

	//チームポイント（2P用）]
	UPROPERTY(EditAnyWhere, BlueprintReadOnly)
		int m_teamPoint2P;

private:

	//自分自身の座標
	FVector m_thisLocation;

	//カウント用変数
	bool m_bFunctionCheck;

//-------------------------------------------------------

	// 2021 05/10 尾崎  m_chairs_に変更
	// AChair* m_pAChair[10] = {NULL};

	float m_ChairDistance[10] = {0.f};

	bool m_Check[10] = { false };

//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
// 青木追加
	// GameInstance
	UInstance* Instance;

public:
	// Player1のターン数
	UPROPERTY(BlueprintReadOnly)
		int m_Player1Turn;
	// Player2のターン数
	UPROPERTY(BlueprintReadOnly)
		int m_Player2Turn;
//☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆☆
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

struct FChair
{
	AChair* chair_obj_;
	FVector location_;

	//2点間の距離を格納する変数
	float Vectormeter_;
};

UCLASS()
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int nowroundnum_;
	float time_cnt_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int maxroundnum_;

	UPROPERTY(EditAnywhere)
		int player_num_;

	UPROPERTY(EditAnywhere)
		AChair* control_chair_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float chair_create_time;

	UPROPERTY(EditAnywhere)
		TArray<APlayerchara*> players_;

	UPROPERTY(EditAnywhere)
		TArray<AChair*> chairs_;

	bool TimeCheck(float _deltatime);

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

private:

	//チームポイント（1P用）
	int m_teamPoint1P;

	//チームポイント（2P用）
	int m_teamPoint2P;

	//自分自身の座標
	FVector m_thisLocation;

	//カウント用変数
	bool m_bFunctionCheck;

//-------------------------------------------------------

	// 2021 04/30 尾崎 構造体の宣言追加
	TArray<FChair*> chairs;

	AChair* m_pAChair[10] = {NULL};

	float m_ChairDistance[10] = {0.f};

	bool m_Check[10] = { false };

};

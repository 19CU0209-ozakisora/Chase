// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Engine/SkeletalMesh.h"	// Playerメッシュ
#include "Engine/Engine.h"			// スクリーンログ出力用
// #include "Components/PrimitiveComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chair.generated.h"

// 椅子のフェーズの列挙型
UENUM(BlueprintType)
enum class EPhase : uint8
{
	kMove UMETA(DisplayName = "Move"),				// 移動状態
	kRotation UMETA(DisplayName = "Rotation"),		// 回転状態
	kSlip UMETA(DisplayName = "Slip"),				// 滑り状態
	kEnd UMETA(DisplayName = "End"),				// 行動終了
};

UCLASS()
class CHASE_API AChair : public APawn
{
	GENERATED_BODY()

public:
	// コンストラクタ
	AChair();

protected:
	// 生成時に呼ばれる
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	USceneComponent* m_proot_;						// ルートコンポーネント用(メッシュの親)
	float player_rotation_;							// 
	int phase_cnt_;									// フェーズのカウント用変数
	float player_location;
	float input_value_;

	void SetInputValue(const float _axisval);
	void PlayerMove(const float _deltatime);
	void PlayerRotation(const float _deltatime);		// 
	void PlayerSlip(const float _deltatime);
	void DeleteArrow();								// ガイドを消す関数
	void NextPhase();

public:

	UPROPERTY(EditAnywhere, Category = "Player")	// デバッグモードをONにするかどうか
		bool debugmode_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// 椅子のメッシュ
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;

	UPROPERTY(EditAnywhere, Category = "Player")	// 回転入力倍率
		float input_rotation_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// 移動の倍率
		float speed_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// 移動の倍率
		float slip_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// 当たったかどうか
		bool hit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// 当たったかどうか
	EPhase phase_;									// 現在のフェーズ格納用

	// BPで初期設定出来ない不具合あり -> 再度BPを作り直すことで解消
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		class UStaticMeshComponent* m_parrow_;

	// カプセルコンポーネントを参照している為同じものをBPに追加
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

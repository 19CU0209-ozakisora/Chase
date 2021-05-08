
#pragma once

#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Engine/SkeletalMesh.h"	// Playerメッシュ
#include "Engine/Engine.h"			// スクリーンログ出力用
// #include "Components/PrimitiveComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chair.generated.h"

// 椅子のフェーズの列挙型
UENUM(BlueprintType)
enum class EPhase : uint8
{
	kStay UMETA(DisplayName = "Stay"),				// 待機状態
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
	float player_rotation_;							// 回転量
	float player_location_;							// 移動量
	float input_value_;								// 入力値
	int phase_cnt_;									// フェーズのカウント用変数
	float def_maxspeed;								// 初期状態の最高速度

	void SetInputValue(const float _axisval);		// 入力された値
	void PlayerMove(const float _deltatime);		// プレイヤーの移動
	void PlayerRotation(const float _deltatime);	// プレイヤーの回転
	void PlayerSlip(const float _deltatime);		// プレイヤーが滑る処理
	void DeleteArrow();								// ガイドを消す関数
	void NextPhase();								// 次の状態に変更する関数
	void SwitchSlipPowerLv1();
	void SwitchSlipPowerLv2();
	void SwitchSlipPowerLv3();

	// カプセルコンポーネントを参照している為同じものをBPに追加
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

public:

	UPROPERTY(EditAnywhere, Category = "Default Setting")	
		bool debugmode_;												// デバッグモードをONにするかどうか
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")	
		bool is_movement_;												// 当たったかどうか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		EPhase phase_;													// 現在のフェーズ格納用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float input_speed_scale_;										// 移動の倍率

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float input_rotation_scale_;									// 回転入力倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float input_slip_scale_;										// 滑りの倍率
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float hitstop_scale_;											// ヒット時の減速の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float is_movement_scale_;										// ヒット時の速度の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString name_;													// 椅子の名前を入れる変数(P1 or P2しか入れないけど)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovementコンポーネント

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// 椅子のメッシュ

	// BPで初期設定出来ない不具合あり -> 再度BPを作り直すことで解消
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// ガイドのメッシュ
};
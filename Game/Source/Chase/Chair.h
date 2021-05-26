// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Engine/SkeletalMesh.h"	// Playerメッシュ
#include "Engine/Engine.h"			// スクリーンログ出力用
// #include "Components/PrimitiveComponent.h"
#include "Math/Vector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chair.generated.h"

//前方宣言
class UAudioComponent;

// 椅子のフェーズの列挙型
UENUM(BlueprintType)
enum class EPhase : uint8
{
	kStay UMETA(DisplayName = "Stay"),					// 待機状態
	kMove UMETA(DisplayName = "Move"),					// 横移動状態
	kRotation UMETA(DisplayName = "Rotation"),			// 投げる方向の変更状態
	kSpin UMETA(DisplayName = "Spin"),					// スピン状態
	kPawerChange UMETA(DisplayName = "PawerChange"),	// パワー変更
	kSlip UMETA(DisplayName = "Slip"),					// 滑り状態
	kEnd UMETA(DisplayName = "End"),					// 行動終了
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
	bool m_first_player_spin_input_flag_;			// 初めてスティックを倒したか否かのフラグ用
	bool m_slip_curve_;								//
	bool is_hit_wall_;
	float m_wall_time;
	float m_angle_corection_;						// スピン時の補正用の変数
	float m_player_rotation_;						// 回転量
	float m_player_location_;						// 移動量
	float m_player_spin_value_;						// スピン量
	float m_player_spin_angle_;						// スティックを回した角度
	float m_preb_player_spin_input_;				// スピン時の前回の入力
	float m_first_player_spin_input_angle_;			// 初めてスティックを倒した角度の保存用
	int m_player_spin_cnt_;							// 何回転したか
	int m_power_level_;								// パワーのレベルのカウント用
	FVector m_forward_vec_;							// 前方向ベクトル
	FVector2D m_input_value_;						// 入力値
	int m_phase_cnt_;								// フェーズのカウント用変数
	float m_def_maxspeed_;							// 初期状態の最高速度

	UAudioComponent* m_audiocomponent_;				//音楽を入れるコンポーネント

	void SetInputValue_X(const float _axisval);		// 入力された値_X
	void SetInputValue_Y(const float _axisval);		// 入力された値_Y
	void PlayerMove(const float _deltatime);		// プレイヤーの横移動
	void PlayerRotation(const float _deltatime);	// プレイヤーの投げる方向の変更
	void PlayerSpin(const float _deltatime);		// プレイヤーの回転
	void PlayerSlip(const float _deltatime);		// プレイヤーが滑る処理
	void DeleteArrow();								// ガイドを消す関数
	void NextPhase();								// 次の状態に変更する関数
	void SwitchSlipPowerLv1();
	void SwitchSlipPowerLv2();
	void SwitchSlipPowerLv3();
	void SwitchSlipPower();
	void SetSlipCurve();

	// カプセルコンポーネントを参照している為同じものをBPに追加
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

public:
	UPROPERTY(EditAnywhere, Category = "Default Setting")
	USceneComponent* m_proot_;						// ルートコンポーネント用(メッシュの親)

	UPROPERTY(EditAnywhere, Category = "Default Setting")	
		bool m_debugmode_;												// デバッグモードをONにするかどうか

	bool m_ishit_;									// 椅子に衝突されたらtrueに
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")	
		bool m_is_movement_;											// 当たったかどうか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		EPhase m_phase_;												// 現在のフェーズ格納用

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_input_speed_scale_;										// 移動の倍率

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_input_rotation_scale_;									// 角度を決めるときの入力倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_powerchange_scale_;								// 力の変更の倍率(どの位上げるか/下げるか)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_spin_scale_;										// スピンの倍率(スティック一回転辺り何度回転させるか)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_input_slip_scale_;										// 滑りの倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_slip_curve_;										// 滑っているときに曲がる量
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_hitstop_scale_;											// ヒット時の減速の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_is_movement_scale_;										// ヒット時の速度の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString m_name_;												// 椅子の名前を入れる変数(P1 or P2しか入れないけど)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// 椅子のメッシュ

	// BPで初期設定出来ない不具合あり -> 再度BPを作り直すことで解消
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// ガイドのメッシュ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovementコンポーネント

	UPROPERTY()
		USoundBase* m_deside_sound_;									//サウンドを入れるコンポーネント
																		//決定音
	UPROPERTY()
		USoundBase* m_chair_roll_sound_;								//椅子の転がる音

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void Ragdoll();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void DestroyHuman();
};
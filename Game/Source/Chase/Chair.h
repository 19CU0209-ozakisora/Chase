
#pragma once

#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Engine/SkeletalMesh.h"	// Playerメッシュ
#include "Engine/Engine.h"			// スクリーンログ出力用
#include "Math/Vector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"		// FindLookAtRotationを使うため
#include "Components/BoxComponent.h"
#include "AddScoreTrigger.h"
#include "Kismet/KismetSystemLibrary.h"
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
	//kMove UMETA(DisplayName = "Move"),				// 横移動状態									
	kRotation UMETA(DisplayName = "Rotation"),			// 角度調整状態								
	kPowerChange UMETA(DisplayName = "PowerChange"),	// パワー調整状態								
	kEntrance UMETA(DisplayName = "Entrance"),			// 助走状態										
	kRide UMETA(DisplayName = "Ride"),					// 乗り状態		(2021/06/23 追加)				
	//kSpin UMETA(DisplayName = "Spin"),				// スピン状態	(2021/06/23 コメント化)
	kSlip UMETA(DisplayName = "Slip"),					// 滑り状態										
	kEnd UMETA(DisplayName = "End"),
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

	bool m_is_input_add_slip_power_;				// 速度を増やすボタンが押されたかどうか
	bool m_slip_curve_;								// 曲がるボタンを押されたかどうか
	bool is_hit_wall_;								// 壁に当たったかどうか
	bool m_is_sweep_;								// スウィープボタンを押したかどうか
	EPhase m_phase_;								// 現在のフェーズ格納用
	float m_wall_time;								// 壁に当たった時間
	float m_angle_corection_;						// スピン時の補正用の変数
	float m_player_rotation_;						// 回転量
	float m_player_location_;						// 移動量
	float m_player_spin_value_;						// 現在何度分の回転量が入っているか
	float m_preb_player_spin_input_;				// スピン時の前回の入力
	float m_first_player_spin_input_angle_;			// 初めてスティックを倒した角度の保存用
	int m_player_spin_cnt_;							// 何回転したか
	FVector m_forward_vec_;							// 前方向ベクトル
	FVector m_target_point_location_;				// 目標地点の座標
	float temp;

	UAudioComponent* m_audiocomponent_;				//音楽を入れるコンポーネント

	void SetInputValue_X(const float _axisval);		// 入力された値_X
	void SetInputValue_Y(const float _axisval);		// 入力された値_Y
	void PlayerMove(const float _deltatime);		// プレイヤーの横移動
	void PlayerEntrance(const float _deltatime);	// 助走の処理
	void PlayerRotation(const float _deltatime);	// プレイヤーの投げる方向の変更
	void PlayerSpin(const float _deltatime);		// プレイヤーの回転
	void PlayerSlip(const float _deltatime);		// プレイヤーが滑る処理
	void DeleteArrow();								// ガイドを消す関数
	void PlayerhSlipPower();						// 助走処理(過去の)
	void SetSlipCurve() { m_slip_curve_ = !m_slip_curve_; }	// 曲がるボタンが押されたら/離されたら処理
	void Deceleration(const float _deltatime);		// 減速処理
	void PlayerSweep(const float _deltatime);		// deltatime処理はしています
	void SetPlayerSweepFlag();	// スウィープボタンが押されたら処理
	void PlayerPowerChange(const float _deltatime);	// 助走自のパワー変更処理
	void InputDecide();

	// カプセルコンポーネントを参照している為同じものをBPに追加
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		bool m_debugmode_;							// デバッグモードをONにするかどうか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		bool m_is_jumpanimation_end_;				// ジャンプアニメーションが終わったかどうか(ジャンプアニメーションが終わるまではスウィープ処理を行わせない)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_ishit_;														// 椅子に衝突されたらtrueに

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool is_entrance_;												// 助走中か

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_in_ride_flag_;						// BP_Ride内に入ったかどうかの変数

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_input_ride_;	// ride状態の時に決定キーを押してslip状態に変更されたかどうか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_speed_scale_;										// 移動の倍率

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_input_rotation_scale_;									// 角度を決めるときの入力倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_max_speed_;												// 椅子の最高速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_min_speed_;												// 椅子の最低速度

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_add_speed_val_;									// 力の変更の倍率(どの位上げるか)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_deceleration_val_;										// 減速量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_sweep_scale_;											// スウィープ時の減速の軽減具合

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_slip_curve_;										// 滑っているときに曲がる量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_hitstop_scale_;											// ヒット時の減速の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_is_movement_scale_;										// ヒット時の速度の倍率

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_rotation_max_val;									// 横移動の最大量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_max_move_val_;								// 前後の移動の最大量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		float m_speed_percent_;						// 椅子に乗るときの押したタイミングの割合を保有する変数

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_min_ride_percent_;		// 乗る状態の最小%

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_ride_percent_;		// 乗る状態の最大% (m_max_ride_percent_ 以上なら100%とする)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_movement_max_val_;												// パワー変更時の移動できる量

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_velocity_val_;													// パワー変更時にどれだけ速度の変更をかけるか(座標が1ずれると m_powerchange_velocity_val_ 分変更)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_def_player_posX_;															// デフォルトの座標(X軸のみ)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		FVector2D m_input_value_;						// 入力値

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString m_name_;												// 椅子の名前を入れる変数(P1 or P2しか入れないけど)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		int m_pummeled_frame_;											// ボタンを押したとき何F判定を持続させるか

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// 椅子のメッシュ

	// BPで初期設定出来ない不具合あり -> 再度BPを作り直すことで解消
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// ガイドのメッシュ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_target_point_mesh_;					// 目標地点のメッシュ

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovementコンポーネント

	UPROPERTY()
		USoundBase* m_deside_sound_;									//サウンドを入れるコンポーネント
																		//決定音
	UPROPERTY()
		USoundBase* m_chair_roll_sound_;								//椅子の転がる音

	UPROPERTY()
		USoundBase* m_chair_collide_sound_;								//椅子がぶつかった時の音

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void Ragdoll();													// ラグドール化させる関数

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void DestroyHuman();											// Humanメッシュを削除する関数

	UFUNCTION(BlueprintCallable, Category = "MyF")
		void SetPhase(const EPhase _phase);								// 次の状態に変更する関数

	UFUNCTION(BlueprintCallable, Category = "MyF")
		EPhase GetPhase() { return m_phase_; }

	UFUNCTION(BlueprintCallable, Category = "MyF")
		bool GetIsSweep() { return m_is_sweep_; }

	void EnableTargetCollision(bool _flag);

	float m_def_speed_;

	UPROPERTY(EditAnywhere)
		AAddScoreTrigger* m_pscore_obj_[2];

	float m_before_slip_rotation_;
	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_spin_add_rotation_value_;		// 毎フレーム加算する角度の上限
	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float input_spin_scale_;
};
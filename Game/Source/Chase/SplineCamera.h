//--------------------------------------------------------------
//クラス名：SplineCamera.h
//概要	  ：プレイヤーの周囲を回るカメラを制御するクラス
//作成日　：2021/07/12
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/07/19 尾崎蒼宙 GameManager.hをインクルード
//								FChangeDirection構造体(どのphase時にどの向きにカメラを移動させるか)の追加
//								m_change_direction_の追加
//			2021/08/20 尾崎蒼宙 GameFramework/SpringArmComponent.hの追加
//								m_pspring_arm_(スプリングアーム格納用)を追加
// 			2021/08/21 尾崎蒼宙 m_out_range_(無効範囲)の追加
//								↑スプリングアームコンポーネントをしようしてもこのCPPで壁の外まで移動させているので範囲を設定する必要あり
//			2021/08/25 尾崎蒼宙 Kismet/KismetSystemLibrary.h(デバッグ用のレイ)のインクルード
//								m_offset_player_height_(Playerの中心点とカメラの高さを同時に上げる)の追加
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameManager.h"
#include "Engine/Engine.h"			// スクリーンログ出力用
#include "Kismet/KismetMathLibrary.h"
#include "GameManager.h"
#include "GameFramework/SpringArmComponent.h"	// スプリングアーム
#include "Kismet/KismetSystemLibrary.h"	// レイ
#include "Chair.h"
#include "SplineCamera.generated.h"

// 椅子のフェーズの列挙型
UENUM(BlueprintType)
enum class EDirection : uint8
{
	kfront UMETA(DisplayName = "Front"),					// 正面(X+, 0, 0)
	kfrontright UMETA(DisplayName = "FrontRight"),			// 右前(X+, Y+, 0)
	kright UMETA(DisplayName = "Right"),					// 右(0, Y+, 0)
	kbackright UMETA(DisplayName = "BackRight"),			// 右後ろ(X- Y+, 0)
	kback UMETA(DisplayName = "Back"),						// 背面(X-, 0, 0)
	kbackleft UMETA(DisplayName = "BackLeft"),				// 左後ろ(X-, Y-, 0)
	kleft UMETA(DisplayName = "Left"),						// 左(0, Y-, 0)
	kfrontleft UMETA(DisplayName = "FrontLeft"),			// 左前(X+, Y-, 0)
	ktop UMETA(DisplayName = "Top"),						// 上(0, 0, Z+)
	kunder UMETA(DisplayName = "Under"),					// 下(0, 0, Z-)
};

USTRUCT(BlueprintType)
struct FChangeDirection
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
		EPhase phase_;
	UPROPERTY(EditAnywhere)
		EDirection change_direction_;
};

UCLASS()
class CHASE_API ASplineCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	EDirection m_preb_edirection_;
	// EPhase m_prebphase_;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "camera")
		EPhase m_prebphase_;
	UPROPERTY(EditAnywhere, Category = "camera")
		UCameraComponent* m_pcamera_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		EDirection m_edirection_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		AGameManager* m_pgamemanager_;

	UPROPERTY(EditAnywhere, Category = "rad")
		float radius_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,  Category = "Enum")
		FVector m_before_change_camera_location_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		FVector m_goal_location_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
		float m_leap_alpha_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		FVector m_now_location_;

	UPROPERTY(EditAnywhere, Category = "Enum")
		float m_end_move_time_;

	UPROPERTY(EditAnywhere, Category = "camera")
		float m_offset_location_z;

	UPROPERTY(EditAnywhere, Category = "camera")
		float m_offset_player_height_;

	FVector SetGoalLocation();
	float SetLeapAlpha(float _deltatime);
	FVector SetCameraLocaiton();
	FRotator SetCameraRotator();
	void ResetLeap();

	UPROPERTY(EditAnywhere, Category = "camera")
		TArray<FChangeDirection> m_change_direction_;

	UPROPERTY(EditAnywhere, Category = "camera")
		USpringArmComponent* m_pspring_arm_;

	UPROPERTY(EditAnywhere, Category = "camera")
		float outrenze;

	UFUNCTION(BlueprintCallable, Category = "MyF")
		void Teleportation();
};

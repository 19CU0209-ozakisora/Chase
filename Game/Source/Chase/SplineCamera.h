// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameManager.h"
#include "Engine/Engine.h"			// スクリーンログ出力用
#include "Kismet/KismetMathLibrary.h"
#include "GameManager.h"
#include "GameFramework/SpringArmComponent.h"	// スプリングアーム
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
	ktop UMETA(DisplayName = "Top"),						// 上(Z+)
	kunder UMETA(DisplayName = "Under"),					// 下(Z-)
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
};

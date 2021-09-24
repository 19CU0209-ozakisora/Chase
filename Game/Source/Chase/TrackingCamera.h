//--------------------------------------------------------------
//クラス名：TrackingCamera.h
//概要	  ：プレイヤーの後ろを追尾するカメラを制御するクラス
//作成日　：2021/09/09
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/0
//--------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Chair.h"
#include "GameManager.h"
#include "GameFramework/SpringArmComponent.h"	// スプリングアーム
#include "Curves/CurveFloat.h"					// カーブコンポーネント追加
#include "Camera/CameraComponent.h"
#include "TrackingCamera.generated.h"

UCLASS()
class CHASE_API ATrackingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackingCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	bool m_switch_;
	bool m_ChangeFOV;
	float m_leap_alpha_;
	float m_prevFOV;
	float m_newFOV;
	float m_ChangeTimer;
	float m_ChangeTimeMax;
	FVector m_input_tracking_offset_;
	FVector m_temp_;
	float m_time_cnt_;


public:

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		float m_advance_time_;			// 前進時間

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		float m_time_;

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		float m_speed_;

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		FVector m_camera_offset_;

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		FVector m_max_recession_offset_;					// カメラの最大の引き

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		FVector m_max_advance_offset_;					// カメラの最大の引き

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		AChair* m_control_chair_;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Information")
		AGameManager* m_pgamemanager_;

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		USpringArmComponent* m_pspringarm_component_;		// スプリングアーム格納用

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		UCameraComponent* m_pcamera_component_;				// カメラのコンポーネント

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		UCurveFloat* m_padvance_curve_;		//	カーブ

	UFUNCTION(BlueprintCallable)
		void SetFOV(float _newFOV, float _changeTime = 1.0f);
};

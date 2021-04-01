// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "PlayerChara.generated.h"

UCLASS()
class CHASE_API APlayerChara : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChara();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void SwitchAccelerator();
	void CameraRotation_X(float _axisvalue_);
	void CameraRotation_Y(float _axisvalue_);

	bool is_accelerator_;
	float now_acceleration_;
	FVector2D camera_rotation;

protected:

public:

	void UpdateMove();	// 移動

	UPROPERTY(Editanywhere)
		UStaticMeshComponent* m_pstaticmesh_;
	UPROPERTY(Editanywhere)
		UCameraComponent* m_pcamera_;
		//UCameraComponent* m_pcamera_;
	UPROPERTY(Editanywhere)
		float acceleration_val_;
	UPROPERTY(Editanywhere)
		float max_acceleration_val_;
	UPROPERTY(Editanywhere, Category = "Camera")
		class USpringArmComponent* m_pSpringArm;		// スプリングアーム

};

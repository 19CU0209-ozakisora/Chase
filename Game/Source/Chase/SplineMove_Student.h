// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"			// �X�v���C��
#include "Components/ChildActorComponent.h"		// Actor�̃R���|�[�l���g�p
#include "GameFramework/Actor.h"
#include "SplineMove_Student.generated.h"

UCLASS()
class CHASE_API ASplineMove_Student : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplineMove_Student();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	float m_spline_length_;		// �X�v���C���̒���
	//UPROPERTY(meta = (ClampMax = 1))
	float m_movement_;			// �ړ���

public:

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		bool m_is_loop_;		// ���[�v�����邩�ǂ���

	UPROPERTY(EditAnyWhere, Category = "Default Setting")
		float m_speed_;			// �ړ����x

	UPROPERTY(EditAnyWhere, Category = "component" )
		UChildActorComponent* m_pchildactorcomponent_;

	UPROPERTY(EditAnyWhere, Category = "component")
		USplineComponent* m_psplinecomponent_;		// �X�v���C���̃R���|�[�l���g
};

//--------------------------------------------------------------
//�N���X���FGirl.h
//�T�v	  �F���̎q�𐧌䂷��N���X
//�쐬���@�F2021/09/03
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/0
//--------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"		// �X�P���^�����b�V��
#include "Components/StaticMeshComponent.h"			// �X�^�e�B�b�N���b�V��
#include "Girl.generated.h"

UCLASS()
class CHASE_API AGirl : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGirl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

public:

	UPROPERTY(EditAnyWhere)	
		USkeletalMeshComponent* m_pgirl_mesh_;

	/*
	UPROPERTY(EditAnyWhere)
		USkeletalMeshComponent* m_pbucket_mesh_;
	*/

};

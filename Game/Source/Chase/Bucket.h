//--------------------------------------------------------------
//�N���X���FBucket.h
//�T�v	  �F�o�P�c�𐧌䂷��N���X
//�쐬���@�F2021/09/03
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/0
//--------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"		// �X�P���^�����b�V��
#include "Bucket.generated.h"

UCLASS()
class CHASE_API ABucket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABucket();

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
		USkeletalMeshComponent* m_pbucket_mesh_;

};

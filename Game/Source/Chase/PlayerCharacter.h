// Fill out your copyright notice in the Description page of Project Settings.
/*�g���Ă܂���*/

#pragma once


#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CHASE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	USceneComponent* m_proot_;
	bool is_rotation_;
	bool actionend_;
	float player_rotation_;

	void PlayerRotation(const float _axisval);
	void DeleteArrow();
	
protected:

public:

	UPROPERTY(EditAnywhere, Category = "Player")
		bool debugmode_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;

	UPROPERTY(EditAnywhere, Category = "Player")
		float input_rotation_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float speed_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool hit;

	// BP�ŏ����ݒ�o���Ȃ��s�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		class UStaticMeshComponent* m_parrow_;

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

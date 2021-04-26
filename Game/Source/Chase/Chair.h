// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
// #include "Components/PrimitiveComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chair.generated.h"

// �֎q�̃t�F�[�Y�̗񋓌^
UENUM(BlueprintType)
enum class EPhase : uint8
{
	kMove UMETA(DisplayName = "Move"),				// �ړ����
	kRotation UMETA(DisplayName = "Rotation"),		// ��]���
	kSlip UMETA(DisplayName = "Slip"),				// ������
	kEnd UMETA(DisplayName = "End"),				// �s���I��
};

UCLASS()
class CHASE_API AChair : public APawn
{
	GENERATED_BODY()

public:
	// �R���X�g���N�^
	AChair();

protected:
	// �������ɌĂ΂��
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	USceneComponent* m_proot_;						// ���[�g�R���|�[�l���g�p(���b�V���̐e)
	float player_rotation_;							// ��]��
	float player_location_;							// �ړ���
	float input_value_;								// ���͒l
	int phase_cnt_;									// �t�F�[�Y�̃J�E���g�p�ϐ�

	void SetInputValue(const float _axisval);		// ���͂��ꂽ�l
	void PlayerMove(const float _deltatime);		// �v���C���[�̈ړ�
	void PlayerRotation(const float _deltatime);	// �v���C���[�̉�]
	void PlayerSlip(const float _deltatime);		// �v���C���[�����鏈��
	void DeleteArrow();								// �K�C�h�������֐�
	void NextPhase();								// ���̏�ԂɕύX����֐�

public:

	UPROPERTY(EditAnywhere, Category = "Player")	
		bool debugmode_;												// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	
		bool is_movement_;														// �����������ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		EPhase phase_;													// ���݂̃t�F�[�Y�i�[�p

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	
		float input_speed_scale_;												// �ړ��̔{��

	UPROPERTY(EditAnywhere, Category = "Player")
		float input_rotation_scale_;									// ��]���͔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	
		float input_slip_scale_;												// ����̔{��
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	
		float hitstop_scale_;											// �q�b�g���̌����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float is_movement_scale_;												// �q�b�g���̑��x�̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// �֎q�̃��b�V��

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		class UStaticMeshComponent* m_parrow_;							// �K�C�h�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovement�R���|�[�l���g

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult );
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
// #include "Components/PrimitiveComponent.h"
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
	float player_rotation_;							// 
	int phase_cnt_;									// �t�F�[�Y�̃J�E���g�p�ϐ�
	float player_location;
	float input_value_;

	void SetInputValue(const float _axisval);
	void PlayerMove(const float _deltatime);
	void PlayerRotation(const float _deltatime);		// 
	void PlayerSlip(const float _deltatime);
	void DeleteArrow();								// �K�C�h�������֐�
	void NextPhase();

public:

	UPROPERTY(EditAnywhere, Category = "Player")	// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���
		bool debugmode_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// �֎q�̃��b�V��
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;

	UPROPERTY(EditAnywhere, Category = "Player")	// ��]���͔{��
		float input_rotation_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// �ړ��̔{��
		float speed_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// �ړ��̔{��
		float slip_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// �����������ǂ���
		bool hit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")	// �����������ǂ���
	EPhase phase_;									// ���݂̃t�F�[�Y�i�[�p

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		class UStaticMeshComponent* m_parrow_;

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

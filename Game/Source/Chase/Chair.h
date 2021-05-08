
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
	kStay UMETA(DisplayName = "Stay"),				// �ҋ@���
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
	float def_maxspeed;								// ������Ԃ̍ō����x

	void SetInputValue(const float _axisval);		// ���͂��ꂽ�l
	void PlayerMove(const float _deltatime);		// �v���C���[�̈ړ�
	void PlayerRotation(const float _deltatime);	// �v���C���[�̉�]
	void PlayerSlip(const float _deltatime);		// �v���C���[�����鏈��
	void DeleteArrow();								// �K�C�h�������֐�
	void NextPhase();								// ���̏�ԂɕύX����֐�
	void SwitchSlipPowerLv1();
	void SwitchSlipPowerLv2();
	void SwitchSlipPowerLv3();

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

public:

	UPROPERTY(EditAnywhere, Category = "Default Setting")	
		bool debugmode_;												// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")	
		bool is_movement_;												// �����������ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		EPhase phase_;													// ���݂̃t�F�[�Y�i�[�p

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float input_speed_scale_;										// �ړ��̔{��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float input_rotation_scale_;									// ��]���͔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float input_slip_scale_;										// ����̔{��
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float hitstop_scale_;											// �q�b�g���̌����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float is_movement_scale_;										// �q�b�g���̑��x�̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString name_;													// �֎q�̖��O������ϐ�(P1 or P2��������Ȃ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovement�R���|�[�l���g

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// �֎q�̃��b�V��

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// �K�C�h�̃��b�V��
};
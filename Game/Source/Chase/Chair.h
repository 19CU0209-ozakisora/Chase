// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
// #include "Components/PrimitiveComponent.h"
#include "Math/Vector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chair.generated.h"

//�O���錾
class UAudioComponent;

// �֎q�̃t�F�[�Y�̗񋓌^
UENUM(BlueprintType)
enum class EPhase : uint8
{
	kStay UMETA(DisplayName = "Stay"),					// �ҋ@���
	kMove UMETA(DisplayName = "Move"),					// ���ړ����
	kRotation UMETA(DisplayName = "Rotation"),			// ����������̕ύX���
	kSpin UMETA(DisplayName = "Spin"),					// �X�s�����
	kPawerChange UMETA(DisplayName = "PawerChange"),	// �p���[�ύX
	kSlip UMETA(DisplayName = "Slip"),					// ������
	kEnd UMETA(DisplayName = "End"),					// �s���I��
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
	bool m_first_player_spin_input_flag_;			// ���߂ăX�e�B�b�N��|�������ۂ��̃t���O�p
	bool m_slip_curve_;								//
	bool is_hit_wall_;
	float m_wall_time;
	float m_angle_corection_;						// �X�s�����̕␳�p�̕ϐ�
	float m_player_rotation_;						// ��]��
	float m_player_location_;						// �ړ���
	float m_player_spin_value_;						// �X�s����
	float m_player_spin_angle_;						// �X�e�B�b�N���񂵂��p�x
	float m_preb_player_spin_input_;				// �X�s�����̑O��̓���
	float m_first_player_spin_input_angle_;			// ���߂ăX�e�B�b�N��|�����p�x�̕ۑ��p
	int m_player_spin_cnt_;							// ����]������
	int m_power_level_;								// �p���[�̃��x���̃J�E���g�p
	FVector m_forward_vec_;							// �O�����x�N�g��
	FVector2D m_input_value_;						// ���͒l
	int m_phase_cnt_;								// �t�F�[�Y�̃J�E���g�p�ϐ�
	float m_def_maxspeed_;							// ������Ԃ̍ō����x

	UAudioComponent* m_audiocomponent_;				//���y������R���|�[�l���g

	void SetInputValue_X(const float _axisval);		// ���͂��ꂽ�l_X
	void SetInputValue_Y(const float _axisval);		// ���͂��ꂽ�l_Y
	void PlayerMove(const float _deltatime);		// �v���C���[�̉��ړ�
	void PlayerRotation(const float _deltatime);	// �v���C���[�̓���������̕ύX
	void PlayerSpin(const float _deltatime);		// �v���C���[�̉�]
	void PlayerSlip(const float _deltatime);		// �v���C���[�����鏈��
	void DeleteArrow();								// �K�C�h�������֐�
	void NextPhase();								// ���̏�ԂɕύX����֐�
	void SwitchSlipPowerLv1();
	void SwitchSlipPowerLv2();
	void SwitchSlipPowerLv3();
	void SwitchSlipPower();
	void SetSlipCurve();

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

public:
	UPROPERTY(EditAnywhere, Category = "Default Setting")
	USceneComponent* m_proot_;						// ���[�g�R���|�[�l���g�p(���b�V���̐e)

	UPROPERTY(EditAnywhere, Category = "Default Setting")	
		bool m_debugmode_;												// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���

	bool m_ishit_;									// �֎q�ɏՓ˂��ꂽ��true��
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")	
		bool m_is_movement_;											// �����������ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		EPhase m_phase_;												// ���݂̃t�F�[�Y�i�[�p

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_input_speed_scale_;										// �ړ��̔{��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_input_rotation_scale_;									// �p�x�����߂�Ƃ��̓��͔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_powerchange_scale_;								// �͂̕ύX�̔{��(�ǂ̈ʏグ�邩/�����邩)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_spin_scale_;										// �X�s���̔{��(�X�e�B�b�N���]�ӂ艽�x��]�����邩)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_input_slip_scale_;										// ����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_slip_curve_;										// �����Ă���Ƃ��ɋȂ����
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")	
		float m_hitstop_scale_;											// �q�b�g���̌����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_is_movement_scale_;										// �q�b�g���̑��x�̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString m_name_;												// �֎q�̖��O������ϐ�(P1 or P2��������Ȃ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// �֎q�̃��b�V��

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// �K�C�h�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovement�R���|�[�l���g

	UPROPERTY()
		USoundBase* m_deside_sound_;									//�T�E���h������R���|�[�l���g
																		//���艹
	UPROPERTY()
		USoundBase* m_chair_roll_sound_;								//�֎q�̓]���鉹

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void Ragdoll();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void DestroyHuman();
};
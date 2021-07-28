
#pragma once

#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
#include "Math/Vector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"		// FindLookAtRotation���g������
#include "Components/BoxComponent.h"
#include "AddScoreTrigger.h"
#include "Kismet/KismetSystemLibrary.h"
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
	//kMove UMETA(DisplayName = "Move"),				// ���ړ����									
	kRotation UMETA(DisplayName = "Rotation"),			// �p�x�������								
	kPowerChange UMETA(DisplayName = "PowerChange"),	// �p���[�������								
	kEntrance UMETA(DisplayName = "Entrance"),			// �������										
	kRide UMETA(DisplayName = "Ride"),					// �����		(2021/06/23 �ǉ�)				
	//kSpin UMETA(DisplayName = "Spin"),				// �X�s�����	(2021/06/23 �R�����g��)
	kSlip UMETA(DisplayName = "Slip"),					// ������										
	kEnd UMETA(DisplayName = "End"),
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

	bool m_is_input_add_slip_power_;				// ���x�𑝂₷�{�^���������ꂽ���ǂ���
	bool m_slip_curve_;								// �Ȃ���{�^���������ꂽ���ǂ���
	bool is_hit_wall_;								// �ǂɓ����������ǂ���
	bool m_is_sweep_;								// �X�E�B�[�v�{�^�������������ǂ���
	EPhase m_phase_;								// ���݂̃t�F�[�Y�i�[�p
	float m_wall_time;								// �ǂɓ�����������
	float m_angle_corection_;						// �X�s�����̕␳�p�̕ϐ�
	float m_player_rotation_;						// ��]��
	float m_player_location_;						// �ړ���
	float m_player_spin_value_;						// ���݉��x���̉�]�ʂ������Ă��邩
	float m_preb_player_spin_input_;				// �X�s�����̑O��̓���
	float m_first_player_spin_input_angle_;			// ���߂ăX�e�B�b�N��|�����p�x�̕ۑ��p
	int m_player_spin_cnt_;							// ����]������
	FVector m_forward_vec_;							// �O�����x�N�g��
	FVector m_target_point_location_;				// �ڕW�n�_�̍��W
	float temp;

	UAudioComponent* m_audiocomponent_;				//���y������R���|�[�l���g

	void SetInputValue_X(const float _axisval);		// ���͂��ꂽ�l_X
	void SetInputValue_Y(const float _axisval);		// ���͂��ꂽ�l_Y
	void PlayerMove(const float _deltatime);		// �v���C���[�̉��ړ�
	void PlayerEntrance(const float _deltatime);	// �����̏���
	void PlayerRotation(const float _deltatime);	// �v���C���[�̓���������̕ύX
	void PlayerSpin(const float _deltatime);		// �v���C���[�̉�]
	void PlayerSlip(const float _deltatime);		// �v���C���[�����鏈��
	void DeleteArrow();								// �K�C�h�������֐�
	void PlayerhSlipPower();						// ��������(�ߋ���)
	void SetSlipCurve() { m_slip_curve_ = !m_slip_curve_; }	// �Ȃ���{�^���������ꂽ��/�����ꂽ�珈��
	void Deceleration(const float _deltatime);		// ��������
	void PlayerSweep(const float _deltatime);		// deltatime�����͂��Ă��܂�
	void SetPlayerSweepFlag();	// �X�E�B�[�v�{�^���������ꂽ�珈��
	void PlayerPowerChange(const float _deltatime);	// �������̃p���[�ύX����
	void InputDecide();

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		bool m_debugmode_;							// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		bool m_is_jumpanimation_end_;				// �W�����v�A�j���[�V�������I��������ǂ���(�W�����v�A�j���[�V�������I���܂ł̓X�E�B�[�v�������s�킹�Ȃ�)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_ishit_;														// �֎q�ɏՓ˂��ꂽ��true��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool is_entrance_;												// ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_in_ride_flag_;						// BP_Ride���ɓ��������ǂ����̕ϐ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_input_ride_;	// ride��Ԃ̎��Ɍ���L�[��������slip��ԂɕύX���ꂽ���ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_speed_scale_;										// �ړ��̔{��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_input_rotation_scale_;									// �p�x�����߂�Ƃ��̓��͔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_max_speed_;												// �֎q�̍ō����x

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_min_speed_;												// �֎q�̍Œᑬ�x

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_add_speed_val_;									// �͂̕ύX�̔{��(�ǂ̈ʏグ�邩)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_deceleration_val_;										// ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_sweep_scale_;											// �X�E�B�[�v���̌����̌y���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_input_slip_curve_;										// �����Ă���Ƃ��ɋȂ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_hitstop_scale_;											// �q�b�g���̌����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_is_movement_scale_;										// �q�b�g���̑��x�̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_rotation_max_val;									// ���ړ��̍ő��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_max_move_val_;								// �O��̈ړ��̍ő��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		float m_speed_percent_;						// �֎q�ɏ��Ƃ��̉������^�C�~���O�̊�����ۗL����ϐ�

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_min_ride_percent_;		// ����Ԃ̍ŏ�%

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_ride_percent_;		// ����Ԃ̍ő�% (m_max_ride_percent_ �ȏ�Ȃ�100%�Ƃ���)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_movement_max_val_;												// �p���[�ύX���̈ړ��ł����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_powerchange_velocity_val_;													// �p���[�ύX���ɂǂꂾ�����x�̕ύX�������邩(���W��1������ m_powerchange_velocity_val_ ���ύX)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_def_player_posX_;															// �f�t�H���g�̍��W(X���̂�)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		FVector2D m_input_value_;						// ���͒l

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString m_name_;												// �֎q�̖��O������ϐ�(P1 or P2��������Ȃ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		int m_pummeled_frame_;											// �{�^�����������Ƃ���F��������������邩

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;						// �֎q�̃��b�V��

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// �K�C�h�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_target_point_mesh_;					// �ڕW�n�_�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UFloatingPawnMovement* m_floating_pawn_movement_;				// FloatingPawnMovement�R���|�[�l���g

	UPROPERTY()
		USoundBase* m_deside_sound_;									//�T�E���h������R���|�[�l���g
																		//���艹
	UPROPERTY()
		USoundBase* m_chair_roll_sound_;								//�֎q�̓]���鉹

	UPROPERTY()
		USoundBase* m_chair_collide_sound_;								//�֎q���Ԃ��������̉�

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void Ragdoll();													// ���O�h�[����������֐�

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void DestroyHuman();											// Human���b�V�����폜����֐�

	UFUNCTION(BlueprintCallable, Category = "MyF")
		void SetPhase(const EPhase _phase);								// ���̏�ԂɕύX����֐�

	UFUNCTION(BlueprintCallable, Category = "MyF")
		EPhase GetPhase() { return m_phase_; }

	UFUNCTION(BlueprintCallable, Category = "MyF")
		bool GetIsSweep() { return m_is_sweep_; }

	void EnableTargetCollision(bool _flag);

	float m_def_speed_;

	UPROPERTY(EditAnywhere)
		AAddScoreTrigger* m_pscore_obj_[2];

	float m_before_slip_rotation_;
	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_spin_add_rotation_value_;		// ���t���[�����Z����p�x�̏��
	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float input_spin_scale_;
};
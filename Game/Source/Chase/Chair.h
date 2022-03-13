//--------------------------------------------------------------
//�N���X���FChair.h
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/22 ���葓�� �쐬
//			2021/04/23 ���葓�� �p�x��ړ�����͒l�̕ϐ��E�R���|�[�l���g�̕ϐ��쐬
//			2021/04/26 ���葓�� �q�b�g���̑��x�̕ϐ���ǉ��E�͂̋�����ς���֐��̒ǉ�
//			2021/05/07 ���葓�� m_name_(���O������ϐ�)�̒ǉ�
//								�֎q���֎q�ȊO�̕��ɂԂ��������̃N���b�V���C�� 
//			2021/05/09 ���葓�� UPROPETY��Category�ǉ�
//			2021/05/12 ���葓�� �\���̂̒ǉ�
//								�e�ϐ���m_��ǉ�
//			2021/05/14 ���葓�� m_forward_vec_(�O�����x�N�g��)�̒ǉ�
//			2021/05/16 ���葓�� SwitchSlipPower�֐�(�������L�[�ɂ���ė͂̋�����ύX����֐�)�̒ǉ�
//			2021/05/20 ���葓�� �X�s���֌W�̕ϐ��E�֐��̒ǉ�
//								Ragdoll�֐�(���O�h�[����)�̒ǉ�
//			2021/05/21 ���葓�� DestroyHuman�֐�(���O�h�[�������ꂽ���b�V���̍폜)��ǉ�
// 			2021/05/22 ��c���_ BGM/SE�̏�����ǉ�
//			2021/05/24 ��c���_ ���ꕔ�ϐ����C��
//			2021/05/24 ���葓�� ���ˏ����̉��쐬(���i�K�ł͖�����)�̂��߁A
//								Math/Vector�̃C���N���[�h/m_is_hit_wall/m_wall_time�̒ǉ�
//			2021/05/26 ���葓�� _input_powerchange_scale_(�͂̕ύX�{��)�̕ϐ��̒ǉ�
//								EPhase��kEntrance�̒ǉ�(������)
//			2021/05/27 ���葓�� �X�s���ɈӐ}���Ă��Ȃ���]���������Ă��܂����̏C��
//			2021/05/28 ���葓�� m_is_input_add_slip_power_(���x�𑝂₷�{�^���������ꂽ���ǂ���)
//								m_is_sweep_(sweep��Ԃ��ǂ���)
// 								m_deltatime_(���͊֌W����Ă΂��֐��Ɉ������쐬�o���Ȃ���)
//								m_deceleration_val_(������)
// 								m_sweep_scale_(�X�E�B�[�v�����ۂɌ������ǂꂾ���ɘa�����邩)
// 								m_pummeled_frame_(�X�E�B�[�v�̗L���t���[��)
//								Deceleration�֐�(����)
// 								PlayerSweep�֐�(�X�E�B�[�v�����Ƃ��ɌĂ΂��֐�)
// 								SetPlayerSweepFlag�֐�(�X�E�B�[�v�{�^���������ꂽ���Ƀt���O�ύX������֐�)
// 								�̒ǉ�(m_pummeled_frame_�͖�����)
//			2021/06/01 ���葓�� �͂�ς���֐����قڍ폜����PlayerPowerChange�֐�(�������̃p���[�ύX������֐�)�̒ǉ�
//								EPhase�̒��̖��O�̈ꕔ��ύX
//			2021/06/03 ���葓�� ���̖ڕW�n�_(m_target_point_)�̒ǉ�
//			2021/06/03 ��c���_ �T�E���h�ǉ��i�Ԃ��鉹�ǉ��j
//			2021/06/07 ���葓�� m_phase_��private�Ɉړ������AGetPhase()�̒ǉ�
//			2021/06/18 ���葓�� EnableTargetCollision�֐�(target_point�̃R���W��������̊֐�)�̒ǉ�
//			2021/06/28 ���葓�� ���d�l�̒ǉ��E����Ȃ��Ȃ���Phase�̃R�����g��
//			2021/07/02 ���葓�� �͂̎d�l�ύX(UI�ɑΉ�)�ׂ̈̏����ύX
//			2021/07/05 ���葓�� ���ϐ����̖����K���ɏ]���Ă��Ȃ������׏C��
//			2021/07/16 ���葓�� ���_�̎d�l�ύX�ɂ��overrap�ɏ����̒ǉ�
//								�X�R�A�I�u�W�F�N�g���i�[�ł���ϐ�����邽�߂�AddScoreTrigger.h�̃C���N���[�h
//			2021/07/20 ���葓�� �A�j���[�V�����̎����ׂ̈�SetPlayerSweepFlag�֐��̒ǉ�
//			2021/07/28 ���葓�� �X�s���Ŏg�p���Ă����ϐ��̍Đ錾(��x�d�l�������������)
//			2021/08/11 ���葓�� m_can_input_(���͉\�t���O)�̒ǉ�
//								���ɐG�ꂽ�ۂ�forward_vector��ύX���Ȃ���΂Ȃ�Ȃ���
//								SetForwardVec�֐���ǉ�
//			2021/08/20 ���葓�� m_parrow_�̍폜
//			2021/09/03 �n粗��� �ǁiComponentTag��Wall�̂��́j�ɂ����������ɔ��˂���悤�ɏ����̒ǉ�
// 			2021/09/06 ���葓�� EPhase��kRotation�̍폜
//			2021/09/07 ���葓�� �j�����ꂽ�f�[�^�̕����ƌ���
//								Move�֐���SetSlipPower�֐���PlayerMove�֐��ɏ����𕪂��APlayerMove�֐����폜
//								���ɂ�����ASetSlipPower�֐��̒ǉ�
//								�g�p�p�r�̔���Ă���ϐ��̃R�����g��
//								m_max_stick_slide_time / m_stick_slide_time_�ϐ��̒ǉ�(�X�e�B�b�N��e�����Ɏg�p)
//			2021/09/08 ���葓�� EPhase��kEntrance��kSlip���폜�����׊Y�������̍폜
//								����L�[�̍폜
//								�v��Ȃ��֐��̍폜
//								�FDeleteArrow()
//								, PlayerEntrance(const float _deltatime)
//								, PlayerRotation(const float _deltatime)
//								, PlayerPowerChange(const float _deltatime)
//								�g���Ă��Ȃ��ϐ��̍폜
//								private
//								: bool m_slip_curve_;							// �Ȃ���{�^���������ꂽ���ǂ���
//								, float m_angle_corection_;						// �X�s�����̕␳�p�̕ϐ�(90.f)
//								, float m_player_rotation_;						// ��]��
// 								, float m_player_location_;						// �ړ���
// 								, float m_first_player_spin_input_angle_;		// ���߂ăX�e�B�b�N��|�����p�x�̕ۑ��p
// 								, float m_def_speed_;							// �������x(�R���|�[�l���g����擾)
// 								
//								public
// 								, bool is_entrance_;							// ��������
// 								, bool m_in_ride_flag_;							// BP_Ride���ɓ��������ǂ����̕ϐ�
// 								, float m_input_speed_scale_;					// �ړ��̔{��
// 								, float m_input_rotation_scale_;				// �p�x�����߂�Ƃ��̓��͔{��
// 								, float m_min_speed_;							// �֎q�̍Œᑬ�x
// 								, float m_input_add_speed_val_;					// �͂̕ύX�̔{��(�ǂ̈ʏグ�邩)
// 								, float m_input_slip_curve_;					// �����Ă���Ƃ��ɋȂ����
// 								, float m_rotation_max_val;						// ���ړ��̍ő��
// 								, float m_powerchange_max_move_val_;			// �O��̈ړ��̍ő��
// 								, float m_speed_percent_;						// �֎q�ɏ��Ƃ��̉������^�C�~���O�̊�����ۗL����ϐ�
// 								, float m_min_ride_percent_;					// ����Ԃ̍ŏ�%
// 								, float m_max_ride_percent_;					// ����Ԃ̍ő�% (m_max_ride_percent_ �ȏ�Ȃ�100%�Ƃ���)
// 								, float m_powerchange_movement_max_val_;		// �p���[�ύX���̈ړ��ł����
// 								, float m_powerchange_velocity_val_;			// �p���[�ύX���ɂǂꂾ�����x�̕ύX�������邩(���W��1������ m_powerchange_velocity_val_ ���ύX)
//			2021/09/09 ���葓�� , m_pplayer_mesh_��UStaticMeshComponent*����USkeltalMeshComponent*�ɕύX
//			2021/09/13 �n粗��� �X�e�B�b�N�ړ������₷���A�d�l�ʂ�ɕύX
//			2021/09/14 ���葓�� m_end_phase_flag_ ��ǉ�
//					   �n粗��� �^�C�~���O�ɍ��킹�Ď����̒ǉ�
//			2021/09/14 ���葓�� m_end_phase_flag_ ���폜
//								m_chair_reflection_��ǉ�
//			2021/09/15 �n粗��� �����̒ǉ��̂��߂ɃA�E�g�]�[���ɋ���̂��ǂ������`�F�b�N����ϐ���ǉ�
//			2021/09/16 �n粗��� �X�e�B�b�N�̉��������͂����܂ł̍Œ�l�ł͂Ȃ��A���˂��鐔�t���[���O�̒l���g�p����悤�ɕύX
//			2021/09/17 �n粗��� ���ړ��̔{����ς�����悤��
//			2021/09/23 �n粗��� �֎q���m���Ԃ������Ƃ��̏�����ύX
//			2021/10/04 �n粗��� �f�o�b�O�p�@�\�̒ǉ��i�L�[�{�[�h�p����̒ǉ��E�s�^�~�߂̒ǉ��j
//--------------------------------------------------------------
#pragma once

#include "Engine/StaticMesh.h"		// ���̑�p(2021/04/13 Player�̑���Ɏg�p)
#include "Engine/SkeletalMesh.h"	// Player���b�V��
#include "Engine/Engine.h"			// �X�N���[�����O�o�͗p
#include "Math/Vector.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"		// FindLookAtRotation���g������
#include "Components/BoxComponent.h"
#include "AddScoreTrigger.h"
#include "EnumObject.h"					// ������Enum�g�p
#include "Kismet/KismetSystemLibrary.h"	// ���C
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
	kPowerChange UMETA(DisplayName = "PowerChange"),	// �p���[�������										
	kSlip UMETA(DisplayName = "Slip"),					// ������										
	kEnd UMETA(DisplayName = "End"),
};

USTRUCT(BlueprintType)
struct FCommentStruct
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<ECommentID> CommentID;
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

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool m_is_input_add_slip_power_;				// ���x�𑝂₷�{�^���������ꂽ���ǂ���
	bool m_IsShoot;									// �֎q�𓊂���{�^���i�L�[�{�[�h���̂݁j�������ꂽ��
	bool m_chair_reflection_;						// �֎q�ɓ����������ɔ��ˏ�Ԃɂ�����t���O
	bool m_addComment;								// �����̃R�����g��ǉ��������ǂ���
	bool m_end_phase_flag_;							// EndPhase���ɃR���|�[�l���g�̑��x������������ϐ�
	bool m_hit_wall_;								// �ǂɓ����������ǂ���
	bool m_is_sweep_;								// �X�E�B�[�v�{�^�������������ǂ���
	bool m_stick_up;								// �X�e�B�b�N�����
	bool m_IsOutZone;								// �A�E�g�]�[���ɂ��邩�ǂ���
	EPhase m_phase_;								// ���݂̃t�F�[�Y�i�[�p
	float m_wall_time;								// �ǂɓ�����������
	float m_hitWallVelocityY;						// �ǂɂ��������ۂ�Y�̃x���V�e�B�[
	float m_player_spin_value_;						// ���݉��x���̉�]�ʂ������Ă��邩
	float m_before_slip_rotation_;					// �O�t���[���̊p�x
	float m_stick_slide_time_;						// �X�e�B�b�N��|���̂ɂ�����������
	float m_stick_down_;							// ���X�e�B�b�N�ő�l
	float m_stick_max_;								// ���X�e�B�b�N�ő�l
	float m_OriginPosZ;								// ����Ƃ���Z�ʒu
	FVector m_forward_vec_;							// �O�����x�N�g��
	//FVector m_target_point_location_;				// �ڕW�n�_�̍��W

	TArray<float> m_stick_minArray;								// ���X�e�B�b�N�ŏ��l

	UAudioComponent* m_audiocomponent_;				//���y������R���|�[�l���g

	void SetPlayerSweepFlag();	// �X�E�B�[�v�{�^���������ꂽ�珈��
	void EnableTargetCollision(const bool _flag);
	void SetInputValue_X(const float _axisval);		// ���͂��ꂽ�l_X
	void SetInputValue_Y(const float _axisval);		// ���͂��ꂽ�l_Y
	void PlayerSpin(const float _deltatime);		// �v���C���[�̉�]
	void PlayerSlip(const float _deltatime);		// �v���C���[�����鏈��
	void Deceleration(const float _deltatime);		// ��������
	void PlayerSweep(const float _deltatime);		// deltatime�����͂��Ă��܂�
	void SetSlipPower(const float _deltatime);		// ���鎞�̑��x����
	void SetCommentary(const TArray<ECommentID> _commentArray);	// �E�B�W�F�b�g�ɃR�����g��ǉ�����
	void IncrimentPower(const float _axisval);
	void DecidePower();
	bool IsGamePadConnected();

	// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ�
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult);

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	bool m_camera_impact_; 

	UPROPERTY(EditAnywhere, Category = "Temp")
		bool TMP_AnotherInputType;					// �X�e�B�b�N���̓^�C�v��؂肩����i�e�X�g�p�j

	UPROPERTY(EditAnywhere, Category = "Temp")
		float TMP_StickDifferenceThreshold;			// �X�e�B�b�N���͂̍��i�e�X�g�p�j

	UPROPERTY(VisibleAnyWhere, Category = "Temp")
		float TMP_PrevStick;						// �S�t���[���̃X�e�B�b�N���͒l�i�e�X�g�p�j

	UPROPERTY(EditAnywhere)
		AAddScoreTrigger* m_pscore_obj_[2];			// �X�R�A�g���K�[������p

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		bool m_debugmode_;							// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���

	UPROPERTY(EditAnywhere, Category = "Default Setting|KeyBoard")
		bool m_inputKeyBoard;						// �L�[�{�[�h���̓��[�h�ɂ��邩�ǂ���

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		bool m_isStickDownOnly;						// �X�e�B�b�N���̓��[�h�؂�ւ��i�����͂����ňړ��ł���悤�Ɂj

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		bool m_is_jumpanimation_end_;				// �W�����v�A�j���[�V�������I��������ǂ���(�W�����v�A�j���[�V�������I���܂ł̓X�E�B�[�v�������s�킹�Ȃ�)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_ishit_;														// �֎q�ɏՓ˂��ꂽ��true��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_input_ride_;	// ride��Ԃ̎��Ɍ���L�[��������slip��ԂɕύX���ꂽ���ǂ���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_is_comenting_;		// ���������ۂ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		bool m_can_input_;		// ���͉\���ǂ���

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		int m_stickUpFrame;												// �X�e�B�b�N�̏���̗͂P�\�t���[��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		int m_stickDownFrame;												// �ǂ̂��炢�O�̃X�e�B�b�N�̉����͂̒l��K�p���邩

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_StopVectorX;											// ���̑��x�ȉ��Ȃ��~�Ƃ݂Ȃ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_default_speed_;											// �֎q�̏������x

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_spinScale;											// ���̑��x�ȉ��Ȃ��~�Ƃ݂Ȃ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_deceleration_val_;										// ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_sweep_scale_;											// �X�E�B�[�v���̌����̌y���

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_hitstop_scale_;											// �q�b�g���̌����̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_is_movement_scale_;										// �q�b�g���̑��x�̔{��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		float m_def_player_posX_;															// �f�t�H���g�̍��W(X���̂�)

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_spin_add_rotation_value_;		// ���t���[�����Z����p�x�̏��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float input_spin_scale_;

	UPROPERTY(EditAnywhere, Category = "Default Setting|Wall")
		float m_hit_wall_reflection_power_;

	UPROPERTY(EditAnywhere, Category = "Default Setting|Wall")
		float m_HitWallReflectionTime;							// �f�o�b�O���[�h��ON�ɂ��邩�ǂ���

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_hit_chair_reflection_power_;

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_max_stick_slide_time_;		// �X�e�B�b�N��|���܂łɂ����鎞�Ԃ̍ő�l

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_SlipPowerMin;												// ���点��p���[�̍ŏ��{��

	UPROPERTY(EditAnywhere, Category = "Default Setting")
		float m_SlipPowerMax;												// ���点��p���[�̍ő�{��

	UPROPERTY(EditAnywhere, Category = "Default Setting|KeyBoard")
		float m_AddPowerForKeyBoard;												// ���点��p���[�̍ő�{��

	UPROPERTY(EditAnywhere, Category = "Commentary|Throw")
		float m_PowerThreshold;												// �E�B�W�F�b�g��\�����邵�����l

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default Setting")
		FVector2D m_input_value_;						// ���͒l

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		FString m_name_;												// �֎q�̖��O������ϐ�(P1 or P2��������Ȃ�����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class USkeletalMeshComponent* m_pplayermesh_;						// �֎q�̃��b�V��

	// BP�ŏ����ݒ�o���Ȃ��s����� -> �ēxBP����蒼�����Ƃŉ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_parrow_;							// �K�C�h�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		class UStaticMeshComponent* m_target_point_mesh_;					// �ڕW�n�_�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default Setting")
		UProjectileMovementComponent* m_projectile_movement_;				// FloatingPawnMovement�R���|�[�l���g

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commentary|Throw")
		TArray<FCommentStruct> m_throwStrongComment;								// ������������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commentary|Throw")
		TArray<FCommentStruct> m_throwWeakComment;									// �キ��������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commentary|Stop")
		TArray<FCommentStruct> m_OutZoneComment;									// �A�E�g�]�[��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Commentary|Stop")
		TArray<FCommentStruct> m_InHouseComment;									// �n�E�X

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Chair")
		TSubclassOf<AActor> m_PowerChair;						// �֎q�̃��b�V��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Power Chair")
		AActor* m_SpawnedChair;							// �������ꂽ�Q�[�W�p�֎q

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
		void SetForwardVec(const FVector _vec) { m_forward_vec_ = _vec; };

	UFUNCTION(BlueprintPure, Category = "MyF")
		EPhase GetPhase() { return m_phase_; }

	UFUNCTION(BlueprintCallable, Category = "MyF")
		bool GetIsSweep() { return m_is_sweep_; }

	UFUNCTION(BlueprintPure, Category = "MyF")
		float GetStickValueDown() { return m_stick_down_; }

	UFUNCTION(BlueprintPure, Category = "MyF")
		float GetStickValueMax() { return m_stick_max_; }

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void LiveComment(ECommentID commentID, float voiceVolume);

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void SetPowerChair();

	UFUNCTION(BlueprintCallable)
		void SetIsOutZone(bool _InOutZone)
	{
		m_IsOutZone = _InOutZone;
	}


	//������������������������������������������������������������������������������������
	// ��
private:
	bool FrameCountStart;
	bool f7;

public:
	void F7();
	//������������������������������������������������������������������������������������
};
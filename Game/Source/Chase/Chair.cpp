//--------------------------------------------------------------
//�N���X���FChair.cpp
//�T�v	  �F�֎q�̐���p�N���X
//�쐬���@�F2021/04/22
//�쐬�ҁ@�F19CU0209 ���葓��
//�X�V�����F2021/04/22 ���葓�� �쐬
//			2021/04/23 ���葓�� �q�b�g���̏�����BP����C++�ɈڐA
//			2021/04/26 ���葓�� �͂̋�����ς���v���O�����̍쐬
//			2021/05/07 ���葓�� �^�O�ŏ��������Ă���������FString�ɕύX
//								�֎q���֎q�ȊO�̕��ɂԂ��������̃N���b�V���C�� 
//			2021/05/09 ���葓�� �R���X�g���N�^�̂��Y����C��
//			2021/05/11 ���葓�� ������������m_name_�̌����ɁuDefault�v��ǉ�
//			2021/05/12 ���葓�� �e�ϐ���m_��ǉ�
//			2021/05/16 ���葓�� �������L�[�ɂ���ăp���[�̕ύX���ł���悤�ɕύX
//			2021/05/20 ���葓�� �X�s�������̒ǉ�
//			2021/05/21 ���葓�� �X�s���ɍő�p�x��ݒ�(forward_vec�ł̃`�F�b�N)
//			2021/05/22 ��c���_ BGM/SE�̏�����ǉ�
//			2021/05/24 ��c���_ ���ꕔ�ϐ����C��
//			2021/05/24 ���葓�� ���ˏ����̉��쐬(���i�K�ł͖�����)
//			2021/05/26 ���葓�� �X�s���̏����ŏ������̕ύX�E������͂̏����̕ύX�E��������DeltaTime���g���Ă��Ȃ����̏C��
//			2021/05/28 ���葓�� �����@�\�̍쐬�E�X�E�B�[�v�@�\�̍쐬
//			2021/06/01 ���葓�� �Q�[���t���[���ς�����׈ꕔ�g�݂Ȃ���
//			2021/06/03 ���葓�� ���̖ڕW�n�_�̒ǉ�
//			2021/06/03 ��c���_ �T�E���h�ǉ��i�Ԃ��鉹�ǉ��j
//			2021/06/07 ���葓�� ����������w��̍ۂ̈ʒu�̕s��C��
//			2021/06/18 ���葓�� �ڕW�n�_�̃��b�V���̓����蔻��𖳌��ɂ���֐��̒ǉ�
//			2021/06/28 ���葓�� ���d�l�̒ǉ��E����Ȃ��Ȃ���State�̃R�����g��
//			2021/07/02 ���葓�� �͂̎d�l�ύX(UI�ɑΉ�)�ׂ̈̏����ύX
//			2021/07/05 ���葓�� ���ϐ����̖����K���ɏ]���Ă��Ȃ������׏C��
//			2021/07/16 ���葓�� ���_�̎d�l�ύX�ɂ��overrap�ɏ����̒ǉ�
//			2021/07/20 ���葓�� �A�j���[�V�����̎����ׂ̈�SetPlayerSweepFlag�֐��̒ǉ�
//			2021/07/28 ���葓�� �X�s���̍č쐬(��x�d�l�������������)
//			2021/08/11 ���葓�� ���͉\�t���O�̒ǉ�
// 			2021/08/20 ���葓�� m_parrow_�̍폜
//			2021/08/27 ���葓�� ���x���w�肵�����x�܂œ��B���Ȃ��s��̏C��
//								�s�v�ȕϐ��̍폜
//			2021/09/02 ���葓�� �s���I�����Ɉ֎q�̉�]���x�����񂾂񉺂��鏈����ǉ�
//								m_player_spin_value_��+m_max_spin_add_rotation_value_���傫��������-m_max_spin_add_rotation_value_�����������ꍇ�ɓK�؂Ȓl���������Ă��Ȃ��������̏C��
//			2021/09/03 �n粗��� �ǁiComponentTag��Wall�̂��́j�ɂ����������ɔ��˂���悤�ɏ����̒ǉ�
// 			2021/09/06 ���葓�� EPhase��kRotation�̍폜
//			2021/09/07 ���葓�� �j�����ꂽ�f�[�^�̕����ƌ���
//			2021/09/08 ���葓�� EPhase��kEntrance��kSlip���폜�����׊Y�������̍폜
//								����L�[�̍폜
//								�v��Ȃ��֐��̍폜
//								�FDeleteArrow()
//								, PlayerEntrance(const float _deltatime)
//								, PlayerRotation(const float _deltatime)
//								, PlayerPowerChange(const float _deltatime)
//			2021/09/09 ���葓�� , m_pplayer_mesh_��UStaticMeshComponent*����USkeltalMeshComponent*�ɕύX
//			2021/09/13 �n粗��� �X�e�B�b�N�ړ������₷���A�d�l�ʂ�ɕύX
//								�ړ��R���|�[�l���g��FloatPawnMovement����ProjectileMovement�ɕύX
//			2021/09/14 ���葓�� End����Tick��Velocity = Zerovector�ɂ��Ă��鏈�������񎞂݂̂ɕύX
//			2021/09/15 ���葓�� �֎q�ɓ����������Ƀt���O��ǉ����AEnd����if���Ō����Ɋւ��镪�򏈗��̍쐬
//			2021/09/15 �n粗��� �����̒ǉ��̂��߂ɃA�E�g�]�[���ɋ���̂��ǂ������`�F�b�N����ϐ���ǉ�
//			2021/09/16 �n粗��� �X�e�B�b�N�̉��������͂����܂ł̍Œ�l�ł͂Ȃ��A���˂��鐔�t���[���O�̒l���g�p����悤�ɕύX
//			2021/09/17 �n粗��� ���ړ��̔{����ς�����悤��
// //		2021/09/23 �n粗��� �֎q���m���Ԃ������Ƃ��̏�����ύX
//--------------------------------------------------------------

#include "Chair.h"

//�T�E���h�n�C���N���[�h
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ActiveSound.h"

// Sets default values
AChair::AChair()
// private
	: m_chair_reflection_(false)
	, m_is_input_add_slip_power_(false)
	, m_IsShoot(false)
	, m_addComment(false)
	, m_hit_wall_(false)
	, m_is_sweep_(false)
	, m_IsOutZone(false)
	, m_phase_(EPhase::kStay)
	, m_wall_time(0.f)
	, m_player_spin_value_(0.f)
	, m_before_slip_rotation_(0.f)
	, m_stick_down_(0.0f)
	, m_stick_max_(0.0f)
	, m_stick_slide_time_(0.f)
	, m_forward_vec_(FVector::ZeroVector)
	//, m_target_point_location_(FVector::ZeroVector)
	, m_audiocomponent_(NULL)
	// public
	, m_pscore_obj_()
	, m_debugmode_(false)
	, m_inputKeyBoard(false)
	, m_is_jumpanimation_end_(true)
	, m_ishit_(false)
	, m_can_input_(true)
	, m_stickUpFrame(2)
	, m_stickDownFrame(5)
	, m_StopVectorX(10.0f)
	, m_default_speed_(3500.0f)
	, m_spinScale(15.0f)
	, m_deceleration_val_(0.f)
	, m_sweep_scale_(3.f)
	, m_hitstop_scale_(0.f)
	, m_is_movement_scale_(0.35f)
	, m_def_player_posX_(0.f)
	, m_max_spin_add_rotation_value_(0.f)
	, input_spin_scale_(0.f)
	, m_hit_wall_reflection_power_(3.f)
	, m_hit_chair_reflection_power_(5000.0f)
	, m_HitWallReflectionTime(0.3f)
	, m_max_stick_slide_time_(0.f)
	, m_SlipPowerMin(0.2f)
	, m_SlipPowerMax(1.2f)
	, m_AddPowerForKeyBoard(0.05f)
	, m_PowerThreshold(0.8f)
	, m_input_value_(FVector2D::ZeroVector)
	, m_name_("")
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
	, m_target_point_mesh_(NULL)
	, m_projectile_movement_(NULL)
	, m_deside_sound_(NULL)
	, m_chair_roll_sound_(NULL)
	, m_chair_collide_sound_(NULL)
	//����������������������������������������������
	, FrameCountStart(false)
	, f7(false)
	//����������������������������������������������

	, TMP_AnotherInputType(false)
	, TMP_StickDifferenceThreshold(0.1f)
	, TMP_PrevStick(0.0f)
{

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �֎q�̃��b�V���̐ݒ�

	m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);


	// �ړ��֌W�̃R���|�[�l���g�̒ǉ�
	m_projectile_movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("m_projectile_movement_"));
	m_projectile_movement_->ProjectileGravityScale = 0.0f;
	m_projectile_movement_->Velocity = FVector(0.0f, 1.0f, 0.0f);
	m_projectile_movement_->bSimulationEnabled = false;
	m_projectile_movement_->bShouldBounce = true;

	// ��������
	m_pplayermesh_->SetSimulatePhysics(true);
	m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

	m_target_point_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_target_point_mesh_"));
	m_target_point_mesh_->SetupAttachment(m_pplayermesh_);

	//���̉����Đ����邩���p�X�Ŏw��A����������I�u�W�F�N�g�ɓ����
	//�p�X�̏������́A"/Game/Music/BGM or SE/�T�E���h�̖��O"�iContent�͏ȗ����邱�Ɓj
	//���艹
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_deside_(TEXT("/Game/Music/SE/deside"));

	if (find_sound_deside_.Succeeded())
	{
		m_deside_sound_ = find_sound_deside_.Object;
	}
	//�֎q���]���鉹
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_chair_(TEXT("/Game/Music/SE/Move"));
	if (find_sound_chair_.Succeeded())
	{
		m_chair_roll_sound_ = find_sound_chair_.Object;
	}
	//�Ԃ��������̉�
	static ConstructorHelpers::FObjectFinder<USoundBase> find_sound_chair_collide_(TEXT("/Game/Music/SE/Collide01_"));
	if (find_sound_chair_collide_.Succeeded())
	{
		m_chair_collide_sound_ = find_sound_chair_collide_.Object;
	}

};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	// �q�b�g���̊֐��̃o�C���h
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
	m_pplayermesh_->OnComponentBeginOverlap.AddDynamic(this, &AChair::OverlapBegin);

	// m_floating_pawn_movement_ �̍ő呬�x���i�[
	m_forward_vec_ = FVector::ForwardVector;

	//����������������������������������������������������������������������������
	// m_pMesh�̏������W��ێ�
	//PlayerLocation = GetActorLocation();

	// m_pMesh��X���W�̕ێ�
	//LocationX = PlayerLocation.X;
	//����������������������������������������������������������������������������
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_projectile_movement_->Velocity.Z = 0.f;

	// �ǂɂ��������ꍇ�^�C�}�[���Z
	if (m_hit_wall_)
	{
		UE_LOG(LogTemp, Warning, TEXT("[Chair (%s)] Wall is true"), *GetName());
		m_wall_time += DeltaTime;

		// ��莞�Ԍo�߂����瓖��������������낷
		if (m_wall_time >= m_HitWallReflectionTime)
		{
			m_projectile_movement_->Velocity.Y = 0.0f;
			m_wall_time = 0.0f;
			m_hit_wall_ = false;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("[Chair (%s)]Velocity = %s"), *GetName(), *m_projectile_movement_->Velocity.ToString());

	// ��
	// UE_LOG(LogTemp, Warning, TEXT("m_player_spin_value_ = %f"), m_player_spin_value_);
	// ��

	//fvec�̃��C
	//UKismetSystemLibrary::DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + FVector(m_forward_vec_.X, m_forward_vec_.Y, 0.f) * 500.f, FLinearColor(255, 0, 0, 100), 0, 20);

	// �p���[����
	if (m_phase_ == EPhase::kPowerChange)
	{
		SetSlipPower(DeltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("PowerChange")));
	}
	// ����
	else if (m_phase_ == EPhase::kSlip)
	{
		FVector pos = GetActorLocation();
		pos.Z = m_OriginPosZ;
		SetActorLocation(pos);

		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip")));

		PlayerSpin(DeltaTime);
		PlayerSlip(DeltaTime);

		if (m_is_sweep_ == true && m_is_jumpanimation_end_ == true)
		{
			PlayerSweep(DeltaTime);
		}
		else
		{
			Deceleration(DeltaTime);
		}

		//���y�Đ��i�֎q���]���鉹�j
				//����Đ�
		if (m_audiocomponent_ == nullptr)
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
		//����Đ��A�܂��͑O�̃t���[���ŃT�E���h���Đ�������Ȃ��ꍇ�A�����������߂���Đ�����
		else if (!m_audiocomponent_->IsPlaying())
		{
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_roll_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
	}
	// �s���I��
	else if (m_phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End")));

		if (m_player_spin_value_ > 0.0001f)
		{
			m_player_spin_value_ -= input_spin_scale_ * DeltaTime;

			if (m_player_spin_value_ < 0.f)
			{
				m_player_spin_value_ = 0.f;
			}
		}
		else if (m_player_spin_value_ < 0.0001f)
		{
			m_player_spin_value_ += input_spin_scale_ * DeltaTime;

			if (m_player_spin_value_ > 0.f)
			{
				m_player_spin_value_ = 0.f;
			}
		}

		m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));

		//�Ԃ����Ă��]���鉹���Đ��I������܂�SE�������Ȃ��̂ł����œ]���鉹���I��
		if (m_audiocomponent_->IsPlaying())
		{
			m_audiocomponent_->Stop();
		}

		if (!m_addComment)
		{
			int inNum = UKismetMathLibrary::RandomInteger(m_InHouseComment.Num());
			int outNum = UKismetMathLibrary::RandomInteger(m_OutZoneComment.Num());

			if (m_IsOutZone)
			{
				SetCommentary(m_OutZoneComment[outNum].CommentID);
			}
			else
			{
				SetCommentary(m_InHouseComment[inNum].CommentID);
			}
			m_addComment = true;
		}

		/*
		if (m_chair_reflection_)
		{
			if (FMath::Abs(m_projectile_movement_->Velocity.X) < m_StopVectorX)
			{
				Deceleration(DeltaTime);
			}
			else
			{
				m_projectile_movement_->Velocity = FVector::ZeroVector;
				// ���ˈړ����I�������false�ɂ��Ď���ȍ~�Ԃ���ꂽ�ۂ�Deceleration�Ő����������������s����悤�ɂ���
				m_chair_reflection_ = false;
			}
		}
		else
		{
			if (FMath::Abs(m_projectile_movement_->Velocity.X) < m_StopVectorX)
			{
				m_projectile_movement_->Velocity = FVector::ZeroVector;
			}
			else
			{
				Deceleration(DeltaTime);
			}
		}*/
	}

	m_is_input_add_slip_power_ = false;
}

void AChair::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (bSelfMoved)
	{
		if (Cast<AChair>(Other))
		{
			Cast<AChair>(Other)->SetPhase(EPhase::kSlip);
			Cast<AChair>(Other)->m_projectile_movement_->Velocity = m_forward_vec_ * m_projectile_movement_->Velocity * m_is_movement_scale_;
		}
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ���E���͂ƌ���L�[
	InputComponent->BindAxis("Horizontal", this, &AChair::SetInputValue_X);
	InputComponent->BindAxis("Vertical", this, &AChair::SetInputValue_Y);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Pressed, this, &AChair::SetPlayerSweepFlag);
	InputComponent->BindAction("Sweep", EInputEvent::IE_Released, this, &AChair::SetPlayerSweepFlag);

	InputComponent->BindAxis("PowerKeyboard", this, &AChair::IncrimentPower);
	InputComponent->BindAction("Decide", EInputEvent::IE_Released, this, &AChair::DecidePower);

	InputComponent->BindAction("Stop", EInputEvent::IE_Released, this, &AChair::MoveStop);


	InputComponent->BindAction("F7", EInputEvent::IE_Released, this, &AChair::F7);
}

void AChair::SetInputValue_X(const float _axisval)
{
	if (m_can_input_)
	{
		if (m_debugmode_)
		{
			if (_axisval == 0.f)
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input Horizontal")));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Horizontal")));
			}
		}

		// ���͂��ꂽ�l���i�[
		m_input_value_.X = _axisval;
	}
	else
	{
		m_input_value_.X = 0.f;
	}
}

void AChair::SetInputValue_Y(const float _axisval)
{
	if (!m_inputKeyBoard)
	{
		if (m_can_input_)
		{
			if (m_debugmode_)
			{
				if (_axisval == 0.f)
				{
					GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input Vertical")));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input Vertical")));
				}
			}

			// ���͂��ꂽ�l���i�[
			m_input_value_.Y = _axisval;
		}
		else
		{
			m_input_value_.Y = 0.f;
		}
	}
}

// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ� -> BP����C++�ɈڐA(2021/04/23 ����)
void AChair::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (m_audiocomponent_ != nullptr)
	{
		FVector a = m_audiocomponent_->GetComponentLocation();
		if (m_chair_collide_sound_ != NULL)
		{
			//�֎q���Ԃ����������Đ�
			m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_chair_collide_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("NULL"));
		}
	}

	// �֎q�ɓ��������ꍇ�̏���
	if (Cast<AChair>(OtherActor))
	{
		m_camera_impact_ = true;
		/*
		if (Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity == FVector::ZeroVector)
		{
			if (m_debugmode_)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Chair Hit")));
				// �֎q�̃��b�V���̑O�����x�N�g��
				UE_LOG(LogTemp, Warning, TEXT("this forwardVector = %f, %f, %f, "), m_pplayermesh_->GetForwardVector().X, m_pplayermesh_->GetForwardVector().Y, m_pplayermesh_->GetForwardVector().Z);
				// floatingpawnmovement�̑��x
				UE_LOG(LogTemp, Warning, TEXT("this component speed = %f, %f, %f, "), m_projectile_movement_->Velocity.X, m_projectile_movement_->Velocity.Y, m_projectile_movement_->Velocity.Z);
			}

			// �����̓��������̐ݒ�
			m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

			// �֎q�ɓ��Ă�ꂽ��true��
			Cast<AChair>(OtherActor)->m_ishit_ = true;
			m_chair_reflection_ = true;

			// ���������֎q�ɑ��x��^����(����O�����x�N�g���Ƒ��x�Ōv�Z)
			//Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity * m_is_movement_scale_;
			Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity = m_forward_vec_ * m_projectile_movement_->Velocity * m_is_movement_scale_;
			Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity.Z = 0.f;

			// �֎q�̌�������(X Y Z �̂����ꂩ��0���ƌv�Z���Ă���Ȃ����ۂ��H�H�H�H)
			m_projectile_movement_->Velocity.X /= m_hitstop_scale_;
			m_projectile_movement_->Velocity.Y /= m_hitstop_scale_;
			m_projectile_movement_->Velocity.Z = 0.f;

			Cast<AChair>(OtherActor)->Ragdoll();

			if (m_debugmode_)
			{
				// ���������֎q�̑��x
				UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity.Z);
				// �֎q�̑��x
				UE_LOG(LogTemp, Warning, TEXT("this after hit speed = %f, %f, %f,"), m_projectile_movement_->Velocity.X, m_projectile_movement_->Velocity.Y, m_projectile_movement_->Velocity.Z);
			}

			// �s���I����
			//SetPhase(EPhase::kEnd);
		}
		else
		{
			if (m_debugmode_)
			{
				FVector vec = Cast<AChair>(OtherActor)->m_projectile_movement_->Velocity;
				UE_LOG(LogTemp, Warning, TEXT("false(X = %f, Y = %f, Z = %f)"), vec.X, vec.Y, vec.Z);
			}
		}
		*/
	}

	// �ǂɂ���������
	if (OtherComp->ComponentHasTag("Wall") && m_hit_wall_ == false)
	{
		m_hit_wall_ = true;

		m_player_spin_value_ *= -1.0f;

		FVector normalVelocity = m_projectile_movement_->Velocity;
		normalVelocity.Normalize();

		m_hitWallVelocityY = -m_projectile_movement_->Velocity.Y * m_hit_wall_reflection_power_ * normalVelocity.X;

		FVector reverseVec = m_forward_vec_;
		reverseVec.Y *= -m_hit_wall_reflection_power_;
		m_forward_vec_ = reverseVec;

		/*
		m_pplayermesh_->SetSimulatePhysics(true);
		m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);
		*/
	}
}

void AChair::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("ScoreTrigger"))
	{
		m_pscore_obj_[1] = m_pscore_obj_[0];
		m_pscore_obj_[0] = Cast<AAddScoreTrigger>(OtherActor);
	}
	/*
		if (OtherActor->ActorHasTag("ChangeSlip"))
	{
		SetPhase(EPhase::kSlip);
	}
	else if (OtherActor->ActorHasTag("ChangeSpin"))
	{
		SetPhase(EPhase::kSpin);
	}
	*/ // (2021/06/23 �R�����g��)
}

void AChair::SetPhase(const EPhase _phase)
{
	m_phase_ = _phase;
	// �ePhase�ɕύX�����ۂ̏����ݒ�
	if (m_phase_ == EPhase::kPowerChange)
	{
		m_stick_down_ = 0.0f;
		m_stick_max_ = 0.0f;

		if (m_parrow_ != NULL)
		{
			Cast<USceneComponent>(m_target_point_mesh_)->DestroyComponent();
		}

		EnableTargetCollision(false);
		m_def_player_posX_ = this->GetActorLocation().X;

		m_OriginPosZ = GetActorLocation().Z;
	}
	else if (m_phase_ == EPhase::kEnd)
	{
		m_projectile_movement_->Velocity = FVector::ZeroVector;
	}
	/*
	else if (m_phase_ == EPhase::kSlip)
	{
		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("m_floating component before speed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}
		//m_floating_pawn_movement_->MaxSpeed *= m_speed_percent_;

		// ���p�[�Z���g�����Ȃ�ꗥ�̃p�[�Z���g��
		if (m_speed_percent_ < m_min_ride_percent_)
		{
			m_speed_percent_ = m_min_ride_percent_;
		}
		// ���p�[�Z���g�ȏ�Ȃ�ꗥ�̃p�[�Z���g��
		else if (m_speed_percent_ >= m_max_ride_percent_)
		{
			m_speed_percent_ = 1.f;
		}

		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("percent = %f"), m_speed_percent_);
			UE_LOG(LogTemp, Warning, TEXT("m_floating component after speed = %f"), m_floating_pawn_movement_->GetMaxSpeed());
		}

		m_is_input_ride_ = true;
		m_before_slip_rotation_ = FMath::Atan2(m_target_point_location_.Y - GetActorLocation().Y, m_target_point_location_.X - GetActorLocation().X);// +90.f;
	}
	*/

	//���Đ��i���艹�j
	m_audiocomponent_ = UGameplayStatics::SpawnSound2D(GetWorld(), m_deside_sound_, 1.0f, 1.0f, 0.0f, nullptr, false, false);
}

void AChair::PlayerSpin(const float _deltatime)
{
	FVector test;
	float test1;
	float rot_x;
	float rot_y;

	// ���E���͂������Ă�����
	if (FMath::Abs(m_input_value_.X) > 0.001f || m_hit_wall_)
	{
		// ���̃t���[���Ԃŉ�]������l�̎擾
		m_player_spin_value_ += m_input_value_.X * _deltatime * input_spin_scale_;
		test1 = FMath::DegreesToRadians(m_before_slip_rotation_ + m_player_spin_value_);

		// �p�x�̌v�Z			 ���݂̑O�����x�N�g�� + ��]��
		rot_x = FMath::Sin(test1);
		rot_y = FMath::Cos(test1);

		// ���
		//FVector test = FVector(rot_x, rot_y, 0.f);
		test = FVector(rot_y, rot_x, 0.f);

		m_forward_vec_ = test;
	}

	if (FMath::Abs(m_player_spin_value_) > m_max_spin_add_rotation_value_)
	{
		if (m_player_spin_value_ > 0.f)
		{
			m_player_spin_value_ = m_max_spin_add_rotation_value_;
		}
		else
		{
			m_player_spin_value_ = m_max_spin_add_rotation_value_ * -1.f;
		}
	}

	m_pplayermesh_->AddRelativeRotation(FRotator(0.f, m_player_spin_value_, 0.f));

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("m_player_spin_value_ = %f"), m_player_spin_value_);
	}

}

void AChair::PlayerSlip(const float _deltatime)
{
	// �O�����x�N�g���Ɍ������Ĉړ�
	//AddMovementInput(m_forward_vec_, 1.f);

	/*
	FVector newActorPos = GetActorLocation() + FVector(0.0f, m_forward_vec_.Y, 0.0f) * m_spinScale;
	SetActorLocation(newActorPos);
	*/

	if (m_hit_wall_)
	{
		m_projectile_movement_->Velocity.Y = FMath::Lerp(m_hitWallVelocityY, 0.0f, (m_wall_time / m_HitWallReflectionTime));
	}
	else
	{
		m_projectile_movement_->Velocity.Y += m_forward_vec_.Y * m_spinScale;
	}

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("hit chair speed = %f, %f, %f, "), m_forward_vec_.X, m_forward_vec_.Y, m_forward_vec_.Z);
	}
}

void AChair::Deceleration(const float _deltatime)
{
	if (!m_is_input_add_slip_power_)
	{
		// �v���C���[�̋t�������擾
		int reversePlayerVector = m_projectile_movement_->Velocity.X > 0.0f ? -1 : 1;

		//m_projectile_movement_->Velocity.X -= m_deceleration_val_ * _deltatime;
		if (FMath::Abs(m_projectile_movement_->Velocity.X) > m_StopVectorX)
		{
			// �Փ˂��ꂽ���̈֎q�̏���
			if (m_ishit_)
			{
				m_projectile_movement_->AddForce(FVector(m_deceleration_val_ / m_is_movement_scale_ * reversePlayerVector, 0.0f, 0.0f));
			}
			// �ʏ펞�̌�������
			else
			{
				m_projectile_movement_->AddForce(FVector(m_deceleration_val_ * reversePlayerVector, 0.0f, 0.0f));
			}
		}
		// �Փ˂������̈֎q�̏���
		else if (FMath::Abs(m_projectile_movement_->Velocity.X) < m_StopVectorX && m_chair_reflection_)
		{
			FVector normalVector = m_projectile_movement_->Velocity;
			//normalVector.Normalize();
			//m_projectile_movement_->AddForce(-normalVector);
			m_projectile_movement_->Velocity = -normalVector;
		}

		if (FMath::Abs(m_projectile_movement_->Velocity.X) <= m_StopVectorX && m_phase_ == EPhase::kSlip)
		{
			m_projectile_movement_->ClearPendingForce();
			SetPhase(EPhase::kEnd);
		}

		if (m_debugmode_)
		{
			UE_LOG(LogTemp, Warning, TEXT("Deceleration/  MaxSpeed = %f"), m_projectile_movement_->GetMaxSpeed());
		}
	}
}

void AChair::PlayerSweep(const float _deltatime)
{
	m_is_sweep_ = true;

	// �v���C���[�̋t�������擾
	int reversePlayerVector = m_projectile_movement_->Velocity.X > 0.0f ? -1 : 1;

	//m_projectile_movement_->Velocity.X -= (m_deceleration_val_ / m_sweep_scale_) * _deltatime;
	if (FMath::Abs(m_projectile_movement_->Velocity.X) > m_StopVectorX)
	{
		m_projectile_movement_->AddForce(FVector((m_deceleration_val_ / m_sweep_scale_ * reversePlayerVector), 0.0f, 0.0f));
	}

	if (FMath::Abs(m_projectile_movement_->Velocity.X) <= m_StopVectorX && m_phase_ == EPhase::kSlip)
	{
		m_projectile_movement_->ClearPendingForce();
		SetPhase(EPhase::kEnd);
	}

	if (m_debugmode_)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sweep/  MaxSpeed = %f"), m_projectile_movement_->GetMaxSpeed());
	}
}

void AChair::EnableTargetCollision(bool _flag)
{
	if (_flag)
	{
		m_target_point_mesh_->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		m_target_point_mesh_->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AChair::SetPlayerSweepFlag()
{
	if (m_is_jumpanimation_end_)
	{
		m_is_sweep_ = !m_is_sweep_;
	}
}

void AChair::SetSlipPower(const float _deltatime)
{
	static int stickFrameCnt = 0;
	static float totalDeltaTime = 0.0f;

	float minSpeed = m_default_speed_ * m_SlipPowerMin;
	float maxSpeed = m_default_speed_ * m_SlipPowerMax;

	float speedAlpha = 0.0f;

	if (m_inputKeyBoard)
	{
		if (m_IsShoot)
		{
			speedAlpha = FMath::Abs(m_stick_down_);
			// �������|���Z
			m_projectile_movement_->Velocity *= FMath::Lerp(minSpeed, maxSpeed, speedAlpha);
			m_projectile_movement_->bSimulationEnabled = true;
			UE_LOG(LogTemp, Warning, TEXT("[Chair] min = %f, mag = %f (%f)"), m_stick_down_, speedAlpha, m_projectile_movement_->Velocity.X);
			SetPhase(EPhase::kSlip);
		}
	}
	else
	{
		// �X�e�B�b�N���������ɓ��͂��ꂽ��
		if (m_input_value_.Y < 0.f)
		{
			// �J�E���g�X�^�[�g
			FrameCountStart = true;
			UE_LOG(LogTemp, Warning, TEXT("[Chair] Stick = %f"), m_input_value_.Y);
		}

		if (TMP_AnotherInputType)
		{
			if (FrameCountStart && m_input_value_.Y <= 0.0f)
			{
				float diff = FMath::Abs(TMP_PrevStick - m_input_value_.Y);
				UE_LOG(LogTemp, Warning, TEXT("[Chair] Stick Diff = %f"), diff);

				if (diff < TMP_StickDifferenceThreshold)
				{
					m_stick_down_ = m_input_value_.Y;
					UE_LOG(LogTemp, Warning, TEXT("[Chair] Set Stick Down (%f)"), m_stick_down_);
				}
			}

			TMP_PrevStick = m_input_value_.Y;
		}
		else
		{
			if (FrameCountStart && m_input_value_.Y <= 0.0f)
			{
				m_stick_minArray.Add(m_input_value_.Y);

				if (m_stick_minArray.Num() > m_stickDownFrame)
				{
					m_stick_minArray.RemoveAt(0);
				}

				if (m_stick_minArray.IsValidIndex(0))
				{
					m_stick_down_ = m_stick_minArray[0];
					UE_LOG(LogTemp, Warning, TEXT("[Chair] Power(Before %d Frame) = %f, Now Input = %f"), m_stickDownFrame, m_stick_down_, m_input_value_.Y);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("[Chair] m_stickDownFrame is not"))
				}
			}
		}

		// ��܂ŃX�e�B�b�N���̓��[�h
		if (!m_isStickDownOnly)
		{
			// �X�e�B�b�N��������ɓ��͂��ꂽ�ꍇ
			if (FrameCountStart && m_input_value_.Y > 0.f)
			{
				FrameCountStart = false;
				m_stick_up = true;
			}

			if (m_stick_up)
			{
				m_stick_slide_time_ += _deltatime;

				if (m_input_value_.Y > m_stick_max_)
				{
					m_stick_max_ = m_input_value_.Y;
				}

				// ���σt���[���Z�o
				stickFrameCnt++;
				totalDeltaTime += _deltatime;
				float averageFPS = 1 / (totalDeltaTime / stickFrameCnt);

				if (m_stick_slide_time_ > (1.0f / averageFPS) * m_stickUpFrame)
				{
					speedAlpha = FMath::Abs(m_stick_down_ * m_stick_max_);
					// �������|���Z
					m_projectile_movement_->Velocity *= FMath::Lerp(minSpeed, maxSpeed, speedAlpha);
					m_projectile_movement_->bSimulationEnabled = true;
					UE_LOG(LogTemp, Warning, TEXT("[Chair] min = %f, max = %f, mag = %f (%f)"), m_stick_down_, m_stick_max_, speedAlpha, m_projectile_movement_->Velocity.X);
					SetPhase(EPhase::kSlip);
				}
			}
		}
		// �������X�e�B�b�N���̓��[�h
		else
		{
			// �X�e�B�b�N���j���[�g�����ȏ�̏ꍇ
			if (FrameCountStart && m_input_value_.Y >= 0.f)
			{
				speedAlpha = FMath::Abs(m_stick_down_);
				// �������|���Z
				m_projectile_movement_->Velocity *= FMath::Lerp(minSpeed, maxSpeed, speedAlpha);
				m_projectile_movement_->bSimulationEnabled = true;
				UE_LOG(LogTemp, Warning, TEXT("[Chair] min = %f, mag = %f (%f)"), m_stick_down_, speedAlpha, m_projectile_movement_->Velocity.X);
				SetPhase(EPhase::kSlip);
			}
		}
	}


	if (GetPhase() == EPhase::kSlip)
	{
		// �����R�����g
		TArray<ECommentID> commentArray;

		int strongNum = UKismetMathLibrary::RandomInteger(m_throwStrongComment.Num());
		int weakNum = UKismetMathLibrary::RandomInteger(m_throwWeakComment.Num());

		commentArray = speedAlpha > m_PowerThreshold ? m_throwStrongComment[strongNum].CommentID : m_throwWeakComment[weakNum].CommentID;

		SetCommentary(commentArray);

		// �l�̏�����
		stickFrameCnt = 0;
		totalDeltaTime = 0.0f;
		m_stick_slide_time_ = 0.0f;
		m_stick_up = false;
	}
}

void AChair::SetCommentary(const TArray<ECommentID> _commentArray)
{
	if (_commentArray.Num() > 0)
	{
		for (ECommentID id : _commentArray)
		{
			LiveComment(id, 10.0f);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Chair] comment is not set."));
	}
}

void AChair::IncrimentPower(const float _axisval)
{
	if (m_inputKeyBoard)
	{
		m_stick_down_ += m_AddPowerForKeyBoard * _axisval;
		m_stick_down_ = FMath::Clamp(m_stick_down_, -1.0f, 1.0f);
		m_input_value_.Y = m_stick_down_;
	}
}

void AChair::DecidePower()
{
	if (m_phase_ == EPhase::kPowerChange)
	{
		m_IsShoot = true;
	}
}

void AChair::MoveStop()
{
	SetPhase(EPhase::kEnd);
}

void AChair::F7()
{
	if (!FrameCountStart)
		f7 = !f7;

	if (f7) { UE_LOG(LogTemp, Error, TEXT("f7 = true")); }
	else if (!f7) { UE_LOG(LogTemp, Error, TEXT("f7 = false")); }
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Chair.h"

// Sets default values
AChair::AChair()
	: m_proot_(NULL)
	, player_rotation_(0.f)
	, player_location_(0.f)
	, input_value_(0.f)
	, phase_cnt_(0.f)
	, debugmode_(false)
	, hit_(false)
	, phase_(EPhase::kMove)
	, input_speed_scale_(0.f)
	, input_rotation_scale_(0.f)
	, input_slip_scale_(0.f)
	, hitstop_scale_(0.f)
	, m_pplayermesh_(NULL)
	, m_parrow_(NULL)
	, m_floating_pawn_movement_(NULL)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���[�g�R���|�[�l���g�̐ݒ�
	//m_proot_ = CreateDefaultSubobject<USceneComponent>(TEXT("m_proot_"));
	//m_proot_ = RootComponent;

	// �֎q�̃��b�V���̐ݒ�
	//m_pplayermesh_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_pplayermesh_"));
	m_pplayermesh_->SetupAttachment(RootComponent);

	// �K�C�h���b�V���̐ݒ�
	m_parrow_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("m_parrow_"));
	m_parrow_->SetupAttachment(m_pplayermesh_);

	// �ړ��֌W�̃R���|�[�l���g�̒ǉ�
	m_floating_pawn_movement_ = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("m_floating_pawn_movement_"));
};

// Called when the game starts or when spawned
void AChair::BeginPlay()
{
	Super::BeginPlay();

	// �q�b�g���̊֐��̃o�C���h
	m_pplayermesh_->OnComponentHit.AddDynamic(this, &AChair::ComponentHit);
}

// Called every frame
void AChair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �ړ�
	if (phase_ == EPhase::kMove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Move"), player_rotation_));
		PlayerMove(DeltaTime);
	}
	// ��]
	else if (phase_ == EPhase::kRotation)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Rotation"), player_rotation_));
		PlayerRotation(DeltaTime);
	}
	// ����
	else if (phase_ == EPhase::kSlip && !hit_)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("Slip"), player_rotation_));
		PlayerSlip(DeltaTime);
	}
	// �s���I��
	else if (phase_ == EPhase::kEnd)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("End"), player_rotation_));
	}
}

// Called to bind functionality to input
void AChair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ���E���͂ƌ���L�[
	InputComponent->BindAxis("TurnRate", this, &AChair::SetInputValue);
	InputComponent->BindAction("Decide", EInputEvent::IE_Pressed, this, &AChair::NextPhase);
}

void AChair::SetInputValue(const float _axisval)
{
	if (debugmode_)
	{
		if (_axisval == 0.f)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("not input TurnRate"), player_rotation_));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Blue, FString::Printf(TEXT("input TurnRate"), player_rotation_));
		}
	}

	// ���͂��ꂽ�l���i�[
	input_value_ = _axisval;
}

void AChair::DeleteArrow()
{
	if (m_parrow_ != NULL)
	{
		Cast<USceneComponent>(m_parrow_)->DestroyComponent();
	}
}

// �J�v�Z���R���|�[�l���g���Q�Ƃ��Ă���ד������̂�BP�ɒǉ� -> BP����C++�ɈڐA(2021/04/23 ����)
void AChair::ComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// ���O�܂ň֎q�ɓ������Ă��Ȃ���� ���� ���������Ώۂ̃^�O��Player��������
	if (!hit_ && OtherActor->ActorHasTag("Player"))
	{
		if (debugmode_)
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Chair Hit")));
			// �֎q�̃��b�V���̑O�����x�N�g��
			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, "), m_pplayermesh_->GetForwardVector().X, m_pplayermesh_->GetForwardVector().Y, m_pplayermesh_->GetForwardVector().Z);
			// floatingpawnmovement�̑��x
			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
		}

		// �����̓��������̐ݒ�
		m_pplayermesh_->SetConstraintMode(EDOFMode::XYPlane);

		// �֎q�ɓ���������ԂɕύX
		hit_ = true;
		phase_ = EPhase::kEnd;

		// ���������֎q�ɑ��x��^����(����O�����x�N�g���Ƒ��x�Ōv�Z)
		Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity = m_pplayermesh_->GetForwardVector() * m_floating_pawn_movement_->Velocity;

		// �֎q�̌�������(X Y Z �̂����ꂩ��0���ƌv�Z���Ă���Ȃ����ۂ��H�H�H�H)
		m_floating_pawn_movement_->Velocity.X /= input_speed_scale_;
		m_floating_pawn_movement_->Velocity.Y /= input_speed_scale_;
		m_floating_pawn_movement_->Velocity.Z /= input_speed_scale_;
		
		if (debugmode_)
		{
			// ���������֎q�̑��x
			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, "), Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.X, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Y, Cast<AChair>(OtherActor)->m_floating_pawn_movement_->Velocity.Z);
			// �֎q�̑��x
			UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f, "), m_floating_pawn_movement_->Velocity.X, m_floating_pawn_movement_->Velocity.Y, m_floating_pawn_movement_->Velocity.Z);
		}
	}
}

void AChair::NextPhase()
{
	if (phase_ == EPhase::kSlip)
	{
		return;
	}

	phase_cnt_++;
	phase_ = EPhase(phase_cnt_);

	// ���钼�O�ɃK�C�h������
	if (phase_ == EPhase::kSlip)
	{
		DeleteArrow();
		return;
	}
}

void AChair::PlayerMove(const float _deltatime)
{
	// ���݂̈ʒu���擾���A���͒l�ɕ␳�������Čv�Z�㔽�f
	FVector nowLocation = GetActorLocation();
	player_location_ += (input_value_ * input_speed_scale_) * _deltatime;
	nowLocation.Y = player_location_;
	SetActorLocation(nowLocation);
}

void AChair::PlayerRotation(const float _deltatime)
{
	// ���͒l�ɕ␳�������Ċp�x��ݒ�
	player_rotation_ += (input_value_* input_rotation_scale_) * _deltatime;
	Cast<USceneComponent>(m_pplayermesh_)->SetWorldRotation(FRotator(0.f, player_rotation_, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("%f"), player_rotation_);
}

void AChair::PlayerSlip(const float _deltatime)
{
	AddMovementInput(Cast<USceneComponent>(m_pplayermesh_)->GetForwardVector(), input_slip_scale_);
}
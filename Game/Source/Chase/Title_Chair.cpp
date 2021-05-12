//------------------------------------------------------------------
//�N���X���FTitle_Chair.cpp
//�T�v	  �F�^�C�g���̈֎q�̓�������
//�쐬���@�F2021/05/11
//�쐬�ҁ@�F19CU0228 ��c���_
//�T�v	�@�F2021/05/11 �N���X�쐬
//------------------------------------------------------------------

//�C���N���[�h
#include "Title_Chair.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


//�R���X�g���N�^
ATitle_Chair::ATitle_Chair()
	:m_movetime_(0.f)
	,m_visibletime_(0.f)
	,m_pboxcomponent_(NULL)
	,m_pstaticmeshcomp_(NULL)
{
 	//���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O�B
	//�K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɁA�؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	m_pbase_ = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = m_pbase_;

	m_pboxcomponent_ = CreateDefaultSubobject<UBoxComponent>(TEXT("CollsionComp"));
	m_pboxcomponent_->SetupAttachment(RootComponent);

	m_pstaticmeshcomp_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticComp"));
	m_pstaticmeshcomp_->SetupAttachment(RootComponent);
	

}

//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void ATitle_Chair::BeginPlay()
{
	Super::BeginPlay();
	
}

//���t���[���X�V����
void ATitle_Chair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�\���\���Ԃ��J�E���g
	m_visibletime_ += DeltaTime;

	//�\�����Ԃ��w�肵�����Ԃ𒴂���܂Ŕ�\��
	if (m_visibletime_ < m_visibletimemax_)
	{
		m_pstaticmeshcomp_->SetVisibility(false);
	}
	else
	{
		//�w�肵�����Ԃ𒴂����烁�b�V����\��
		m_pstaticmeshcomp_->SetVisibility(true);
		MoveChair(DeltaTime);
	}

}

//�֎q�𓮂���
void ATitle_Chair::MoveChair(float deltaTime_)
{

	//�ړ��p�ɐV�������W��ݒ�
	FVector v_newactorlocation_ = GetActorLocation();
	//��]����
	FRotator v_newactorrotation_ = GetActorRotation();

	//�J��Ԃ��^��
	float move_ = -(FMath::Sin(move_ + deltaTime_ * 8.f) - FMath::Sin(deltaTime_));

	//UE_LOG(LogTemp, Warning, TEXT("move_ = %f"), move_);

	//X���ɉ^���̑�����ݒ�
	v_newactorlocation_.X += move_ * 500.f;

	v_newactorrotation_.Yaw += move_ * 3.0f;

	//���˂����֎q�̎��Ԃ��J�E���g
	++m_chaircnt_;

	//UE_LOG(LogTemp, Warning, TEXT("m_chaircnt = %f"), m_chaircnt_);

	//m_movetime_ -= deltaTime_;

	//���W�Ăяo��
	SetActorLocation(FVector(v_newactorlocation_));

	SetActorRotation(FRotator(v_newactorrotation_));

	//�֎q���~�߂鏈��
	if (m_visibletime_ > m_visibletimemax_ + m_stopchairtime_)
	{
		//�e�ݒ肳�ꂽX���W���Ăяo��
		v_newactorlocation_.X = m_location_x_;

		//���W�Ăяo��
		SetActorLocation(FVector(v_newactorlocation_));

		//�֎q�̔��Ԏ��Ԃ��w�肵�����Ԃ𒴂�����
		if (m_chaircnt_ >= m_chaircntmax_)
		{
			//���b�V�����\��
			m_pstaticmeshcomp_->SetVisibility(false);

			//�X�^�[�g���W�Ɉ֎q��߂�
			v_newactorlocation_.X = 2650.f;

			//���W�Ăяo��
			SetActorLocation(FVector(v_newactorlocation_));

			//Tick()�ő�����Ă����ϐ��̏�����
			m_visibletime_ = 0.f;

			m_chaircnt_ = 0.0f;
		}
	}
}


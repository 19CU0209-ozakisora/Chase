//--------------------------------------------------------------
//�N���X���FHousePoint.cpp
//�T�v	  �F�֎q�̋����ɂ���āA���_������N���X�iChair�N���X�̌p���N���X�j
//�쐬���@�F2021/04/29
//�쐬�ҁ@�F19CU0228 ��c���_
//�X�V�����F2021/04/29 �쐬
//--------------------------------------------------------------

//�C���N���[�h
#include "HouseCenter.h"
#include "Chair.h"

AHouseCenter::AHouseCenter()
	:m_getPoint(0)
	, m_thisLocation(FVector::ZeroVector)
	, m_ChairLocation(FVector::ZeroVector)
	, m_differenceLocation(0.f)
{
	//���t���[���A����Actor()��Tick���ĂԂ��ǂ��������߂�t���O�B�K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	//�m�F�p�X�^�e�B�b�N���b�V���p�R���|�[�l���g�쐬
	m_pConfirmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Central"));
	m_pConfirmMesh->SetupAttachment(RootComponent);

}

//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈���B
void AHouseCenter::BeginPlay()
{
	Super::BeginPlay();

	//�n�E�X�̒��S���W���i�[
	m_thisLocation = GetActorLocation();


	//�n�E�X�̒��S�_�̍��W�m�F�p
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("X %f"), m_thisLocation.X));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Y %f"), m_thisLocation.Y));
}

//���t���[���X�V����
void AHouseCenter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�֎q���~�܂������̏���
	StopChair();

}

//�֎q���~�܂������̏���
void AHouseCenter::StopChair()
{
	//�����܂Œʂ�

	//��������悪�ʂ�Ȃ�
	//�p�����Ă��邽��phase_�ł��K�p����͂����Ǝv���Ă���ł����E�E�E
	//�֎q�̏�Ԃ��s���I���ɂȂ�����i�̂���j
	if (AChair::phase_ == EPhase::kEnd)
	{
		//�֎q�̍��W���i�[�i���Ă����j
		m_ChairLocation = AChair::GetActorLocation();

		//�n�E�X�̒��S���W�ƈ֎q�̍��W�̋����̍����i�[�i�̂���j
		m_differenceLocation = m_ChairLocation.X * m_ChairLocation.Y;

		//��������Ēʂ��ĂȂ����Ƃ��m�F���Ă܂��B
		UE_LOG(LogTemp, Warning, TEXT("m_d %f"), m_differenceLocation);

	}

}


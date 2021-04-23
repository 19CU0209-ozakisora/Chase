//--------------------------------------------------------------
//�N���X���FHousePoint.cpp
//�T�v	  �F�֎q�̋����ɂ���āA���_������N���X
//�쐬���@�F2021/04/23
//�쐬�ҁ@�F19CU0228 ��c���_
//�X�V�����F2021/04/23 �쐬
//--------------------------------------------------------------

//�C���N���[�h
#include "HousePoint.h"
#include"Chair.h"

//�R���X�g���N�^
AHousePoint::AHousePoint()
	:m_getPoint(0)
	,m_thisLocation(FVector::ZeroVector)
	,m_ChairLocation(FVector::ZeroVector)
	,m_prevdifferenceLocation(FVector::ZeroVector)
	,m_differenceLocation(FVector::ZeroVector)
{
 	//���t���[���A����Actor()��Tick���ĂԂ��ǂ��������߂�t���O�B�K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	//�m�F�p�X�^�e�B�b�N���b�V���p�R���|�[�l���g�쐬
	m_pConfirmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("House Central"));
	m_pConfirmMesh->SetupAttachment(RootComponent);

}

//�Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈���B
void AHousePoint::BeginPlay()
{
	Super::BeginPlay();
	
	//�n�E�X�̒��S���W���i�[
	m_thisLocation = GetActorLocation();

	//�֎q�̍��W���i�[
	m_ChairLocation = FVector::ZeroVector;

	//�n�E�X�̒��S���W�ƈ֎q�̍��W�̋����̍����i�[(���ˑO)
	m_prevdifferenceLocation = m_ChairLocation - m_thisLocation;

	//�n�E�X�̒��S�_�̍��W�m�F�p
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("X %f"), m_thisLocation.X));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Y %f"), m_thisLocation.Y));
}

//���t���[���X�V����
void AHousePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHousePoint::StopChair()
{
	//�֎q�̍��W���i�[
	m_ChairLocation = FVector::ZeroVector;

	//�n�E�X�̒��S���W�ƈ֎q�̍��W�̋����̍����i�[
	m_differenceLocation = m_ChairLocation - m_thisLocation;

}


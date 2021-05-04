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
	:m_getPoint(500)
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
	// 2021/04/29 ����F�ꎞ�I�ɃR�����g��
	//2021/05/02�@��c�F�R�����g����
	//StopChair();
}

//�֎q���~�܂������̏���
void AHouseCenter::StopChair()
{

	//�T�������N���X������
	TSubclassOf<AChair> findClass;
	findClass = AChair::StaticClass();
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), findClass, temp);

	//���������֎q�̃I�u�W�F�N�g�A���W���擾
	for (int i = 0; i < temp.Num(); ++i)
	{
		AChair* chair = Cast<AChair>(temp[i]);
		FChair tmp;
		tmp.chair_obj_ = chair;
		tmp.location_ = chair->GetActorLocation();
		//���S����֎q�̋������v�Z���A�֎q�̏��ɕۑ�
		_Vector[i] = sqrt(((m_thisLocation.X - tmp.location_.X) * (m_thisLocation.X - tmp.location_.X))
			+ ((m_thisLocation.Y - tmp.location_.Y) * (m_thisLocation.Y - tmp.location_.Y)));
		chairs.Add(tmp);
	}

	ChairSort(_Vector);

	SetPoint(_Vector);

	//���O�m�F�p
	for (int n = 0; n < chairs.Num(); ++n)
	{
		//FString name = (chairs[n].chair_obj_)->GetName();
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, name);
		//UE_LOG(LogTemp, Warning, TEXT("���W�F X : %f , Y : %f, Z : %f"), chairs[n].location_.X, chairs[n].location_.Y, chairs[n].location_.Z);
		//UE_LOG(LogTemp, Warning, TEXT("kyori= %f"), _Vector[n]);
	}

}

//�֎q�̋����\�[�g�p(�o�u���\�[�g)
void AHouseCenter::ChairSort(float _Vector[])
{
	float tmp;

	int dataCount01;
	int dataCount02;

	//2�_�Ԃ̋����Ń\�|�g��������
	for (dataCount01 = 0; dataCount01 < 9; ++dataCount01)
	{
		for (dataCount02 = 0; dataCount02 < 10 - dataCount01; ++dataCount02)
		{
			if (_Vector[dataCount02 + 1] < _Vector[dataCount02])
			{
				tmp = _Vector[dataCount02];
				_Vector[dataCount02] = _Vector[dataCount02 + 1];
				_Vector[dataCount02 + 1] = tmp;
			}
		}
	}
	for (int n = 0; n < 10; ++n)
	{
		UE_LOG(LogTemp, Warning, TEXT("kyori= %f"), _Vector[n]);
	}
}

void AHouseCenter::SetPoint(float _Vector[])
{
	for (int i = 0; i < 10; ++i)
	{
		if (_Vector[i])
		{
			UE_LOG(LogTemp, Warning, TEXT("point: %d"), m_getPoint);

			if (m_getPoint > 0)
			{
				m_getPoint -= 100;
			}
		}
	}
}


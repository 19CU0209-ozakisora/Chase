//--------------------------------------------------------------
//�N���X���FOutZone
//�T�v	  �F�֎q���~�܂������ɍ폜�����]�[��
//�쐬���@�F2021/08/05
//�쐬�ҁ@�F�n粗���
//�X�V�����F2021/08/10 �n粗��� BP����ڍs
//		�@�F2021/08/18 �n粗��� UI�̕\��
//		�@�F2021/09/10 �n粗��� Chair�^�ɃL���X�g��Chair��m_Phase�𒲂ׂ�悤��
//							�@  �����蔻��ł͂Ȃ�TargetPoint�Ŕ͈͂��w�肷��悤��
//--------------------------------------------------------------

#include "OutZone.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AOutZone::AOutZone()
	: isEnable(true)
	, Root(nullptr)
	, TargetStart(nullptr)
	, TargetEnd(nullptr)
	, outWidget(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	// RootComponent�̐ݒ�
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	/*
	// StaticMeshComponent�iCube�j�̐ݒ�
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);
	*/

	// TargetPoint�̐ݒ�
	TargetStart = CreateDefaultSubobject<UChildActorComponent>(TEXT("Start"));
	TargetEnd = CreateDefaultSubobject<UChildActorComponent>(TEXT("End"));

	TargetStart->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
	TargetEnd->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	TargetStart->SetupAttachment(RootComponent);
	TargetEnd->SetupAttachment(RootComponent);

	// �R���|�[�l���g�̃Q�[������\���ݒ�E���r���e�B��L���X�g�V���h�E�̐ݒ�
	SetActorHiddenInGame(true);
	Root->SetMobility(EComponentMobility::Static);

	// OUT��Widget�̃f�t�H���g�ݒ�
	ConstructorHelpers::FObjectFinder<UClass> tmpWidget(TEXT("/Game/Widget/OUT_Widget.OUT_Widget_C"));
	outWidget = tmpWidget.Object;
	
}

void AOutZone::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> getActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChair::StaticClass(), getActor);

	for (AActor* act : getActor)
	{
		deleteChair.Add(Cast<AChair>(act));
	}
}

void AOutZone::PostInitializeCompenents()
{
	Super::PostInitializeComponents();

	TargetStart->SetChildActorClass(ATargetPoint::StaticClass());
	TargetEnd->SetChildActorClass(ATargetPoint::StaticClass());
}

void AOutZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isEnable)
	{
		if (deleteChair.Num() > 0)
		{
			// �R���W�������ɓ����Ă���SActor��Velocity�𒲂ׂ�
			for (int i = 0; i < deleteChair.Num(); ++i)
			{
				// ��~��Ԃł���΍폜
				if (deleteChair[i] != nullptr && deleteChair[i]->GetActorLocation().X >= TargetStart->GetComponentLocation().X && deleteChair[i]->GetActorLocation().X <= TargetEnd->GetComponentLocation().X && deleteChair[i]->GetPhase() == EPhase::kEnd)
				{
					deleteChair[i]->SetIsOutZone(true);
					DeleteActor(deleteChair[i]);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[OutZone] Chair is not found."))
		}
	}
}

void AOutZone::DeleteActor(AChair* _chair)
{
	if (_chair != nullptr)
	{
		// Actor�̃R���W�����𖳌������A�����Ȃ�����
		_chair->SetActorEnableCollision(false);
		_chair->GetRootComponent()->SetVisibility(false, true);

		// �z�񂩂�폜
		deleteChair.Remove(_chair);

		// Widget�\��
		if (outWidget != nullptr)
		{
			UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), outWidget);
			
			if (UserWidget != nullptr)
			{
				UserWidget->AddToViewport();
			}
		}
	}
}
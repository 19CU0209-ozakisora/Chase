//--------------------------------------------------------------
//�N���X���FOutZone
//�T�v	  �F�֎q���~�܂������ɍ폜�����]�[��
//�쐬���@�F2021/08/05
//�쐬�ҁ@�F�n粗���
//�X�V�����F2021/08/10 �n粗��� BP����ڍs
//		�@�F2021/08/18 �n粗��� UI�̕\��
//--------------------------------------------------------------

#include "OutZone.h"
#include "Kismet/KismetMathLibrary.h"

AOutZone::AOutZone()
	: Root(nullptr)
	, Cube(nullptr)
	, DeleteActorTag("Player")
	, outWidget(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	// RootComponent�̐ݒ�
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// StaticMeshComponent�iCube�j�̐ݒ�
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);

	// �R���|�[�l���g�̃Q�[������\���ݒ�E���r���e�B��L���X�g�V���h�E�̐ݒ�
	SetActorHiddenInGame(true);
	Root->SetMobility(EComponentMobility::Static);
	Cube->SetCastShadow(false);

	// OUT��Widget�̃f�t�H���g�ݒ�
	ConstructorHelpers::FObjectFinder<UClass> tmpWidget(TEXT("/Game/Widget/OUT_Widget.OUT_Widget_C"));
	outWidget = tmpWidget.Object;
	
}

void AOutZone::BeginPlay()
{
	Super::BeginPlay();

	Cube->OnComponentBeginOverlap.AddDynamic(this, &AOutZone::OnOverlapBegin);
	Cube->OnComponentEndOverlap.AddDynamic(this, &AOutZone::OnOverlapEnd);
}

void AOutZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �R���W�������ɓ����Ă���SActor��Velocity�𒲂ׂ�
	for (AActor* Actor : deleteActor)
	{
		// �����Ă��Ȃ���΍폜
		if (Actor != nullptr && UKismetMathLibrary::EqualEqual_VectorVector(Actor->GetVelocity(), FVector::ZeroVector))
		{
			DeleteActor(Actor);			
		}
	}

}

void AOutZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// �����Actor�������Ă��āA�폜����Actor�̃^�O�����Ă���΍폜Actor�z��ɒǉ�
	if (bFromSweep && OtherActor->ActorHasTag(DeleteActorTag))
	{
		deleteActor.AddUnique(OtherActor);
	}
}

void AOutZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// �R���W��������o�����ɍ폜Actor�z�񂩂�폜
	if (deleteActor.Contains(OtherActor))
	{
		deleteActor.Remove(OtherActor);
	}
}

void AOutZone::DeleteActor(AActor* _actor)
{
	if (_actor != nullptr)
	{
		// Actor�̃R���W�����𖳌������A�����Ȃ�����
		_actor->SetActorEnableCollision(false);
		_actor->GetRootComponent()->SetVisibility(false, true);

		// �z�񂩂�폜
		deleteActor.Remove(_actor);

		// Widget�\��
		if (outWidget != nullptr)
		{
			TSubclassOf<class UUserWidget> Widget = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*outWidget->GetPathName())).LoadSynchronous();

			UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), Widget);
			
			if (UserWidget != nullptr)
			{
				UserWidget->AddToViewport();
			}
		}
	}
}
//--------------------------------------------------------------
//�N���X���FOutZone
//�T�v	  �F�֎q���~�܂������ɍ폜�����]�[��
//�쐬���@�F2021/08/05
//�쐬�ҁ@�F�n粗���
//�X�V�����F2021/08/10 �n粗��� BP����ڍs
//--------------------------------------------------------------

#include "OutZone.h"
#include "Kismet/KismetMathLibrary.h"

AOutZone::AOutZone()
	: Root(nullptr)
	, Cube(nullptr)
	, DeleteActorTag("Player")
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);
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
	for (AActor* Actor : deleteActor)
	{
		if (Actor != nullptr && UKismetMathLibrary::EqualEqual_VectorVector(Actor->GetVelocity(), FVector::ZeroVector))
		{
			DeleteActor(Actor);
		}
	}

}

void AOutZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (bFromSweep && OtherActor->ActorHasTag(DeleteActorTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("[OutZone] Overlap Begin"))
		deleteActor.AddUnique(OtherActor);
	}
}

void AOutZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (deleteActor.Contains(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("[OutZone] Overlap End"))
		deleteActor.Remove(OtherActor);
	}
}

void AOutZone::DeleteActor(AActor* _actor)
{
	if (_actor != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[OutZone] YEAH"));
		_actor->SetActorEnableCollision(false);
		_actor->GetRootComponent()->SetVisibility(false, true);

		deleteActor.Remove(_actor);
	}
}

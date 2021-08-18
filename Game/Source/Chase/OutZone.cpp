//--------------------------------------------------------------
//クラス名：OutZone
//概要	  ：椅子が止まった時に削除されるゾーン
//作成日　：2021/08/05
//作成者　：渡邊龍音
//更新履歴：2021/08/10 渡邊龍音 BPから移行
//		　：2021/08/18 渡邊龍音 UIの表示
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

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);

	ConstructorHelpers::FObjectFinder<UClass> tmpWidget(TEXT("/Game/Widget/OUT_Widget.OUT_Widget_C"));
	outWidget = tmpWidget.Object;
	
}

void AOutZone::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);

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
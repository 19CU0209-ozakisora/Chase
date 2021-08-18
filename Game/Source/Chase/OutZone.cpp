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

	// RootComponentの設定
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// StaticMeshComponent（Cube）の設定
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);

	// コンポーネントのゲーム中非表示設定・モビリティやキャストシャドウの設定
	SetActorHiddenInGame(true);
	Root->SetMobility(EComponentMobility::Static);
	Cube->SetCastShadow(false);

	// OUT時Widgetのデフォルト設定
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

	// コリジョン内に入っている全ActorのVelocityを調べる
	for (AActor* Actor : deleteActor)
	{
		// 動いていなければ削除
		if (Actor != nullptr && UKismetMathLibrary::EqualEqual_VectorVector(Actor->GetVelocity(), FVector::ZeroVector))
		{
			DeleteActor(Actor);			
		}
	}

}

void AOutZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	// 相手のActorが動いていて、削除するActorのタグがついていれば削除Actor配列に追加
	if (bFromSweep && OtherActor->ActorHasTag(DeleteActorTag))
	{
		deleteActor.AddUnique(OtherActor);
	}
}

void AOutZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// コリジョンから出た時に削除Actor配列から削除
	if (deleteActor.Contains(OtherActor))
	{
		deleteActor.Remove(OtherActor);
	}
}

void AOutZone::DeleteActor(AActor* _actor)
{
	if (_actor != nullptr)
	{
		// Actorのコリジョンを無効化し、見えなくする
		_actor->SetActorEnableCollision(false);
		_actor->GetRootComponent()->SetVisibility(false, true);

		// 配列から削除
		deleteActor.Remove(_actor);

		// Widget表示
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
//--------------------------------------------------------------
//クラス名：OutZone
//概要	  ：椅子が止まった時に削除されるゾーン
//作成日　：2021/08/05
//作成者　：渡邊龍音
//更新履歴：2021/08/10 渡邊龍音 BPから移行
//		　：2021/08/18 渡邊龍音 UIの表示
//		　：2021/09/10 渡邊龍音 Chair型にキャストしChairのm_Phaseを調べるように
//							　  当たり判定ではなくTargetPointで範囲を指定するように
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

	// RootComponentの設定
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	/*
	// StaticMeshComponent（Cube）の設定
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Cube->SetupAttachment(RootComponent);
	Cube->bMultiBodyOverlap = true;
	Cube->SetUseCCD(true);
	*/

	// TargetPointの設定
	TargetStart = CreateDefaultSubobject<UChildActorComponent>(TEXT("Start"));
	TargetEnd = CreateDefaultSubobject<UChildActorComponent>(TEXT("End"));

	TargetStart->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
	TargetEnd->SetRelativeLocation(FVector(100.0f, 0.0f, 0.0f));

	TargetStart->SetupAttachment(RootComponent);
	TargetEnd->SetupAttachment(RootComponent);

	// コンポーネントのゲーム中非表示設定・モビリティやキャストシャドウの設定
	SetActorHiddenInGame(true);
	Root->SetMobility(EComponentMobility::Static);

	// OUT時Widgetのデフォルト設定
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
			// コリジョン内に入っている全ActorのVelocityを調べる
			for (int i = 0; i < deleteChair.Num(); ++i)
			{
				// 停止状態であれば削除
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
		// Actorのコリジョンを無効化し、見えなくする
		_chair->SetActorEnableCollision(false);
		_chair->GetRootComponent()->SetVisibility(false, true);

		// 配列から削除
		deleteChair.Remove(_chair);

		// Widget表示
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
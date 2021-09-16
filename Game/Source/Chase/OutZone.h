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


#pragma once

#include "CoreMinimal.h"
#include "Chair.h"
#include "Blueprint/UserWidget.h"
#include "Engine/TargetPoint.h"
#include "Components/ChildActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "OutZone.generated.h"

UCLASS()
class CHASE_API AOutZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOutZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<AChair*> deleteChair;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeCompenents();
	
public:
	UFUNCTION(BlueprintCallable)
		void DeleteActor(AChair* _chair);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isEnable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* TargetStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UChildActorComponent* TargetEnd;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> outWidget;
};
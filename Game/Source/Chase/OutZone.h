//--------------------------------------------------------------
//クラス名：OutZone
//概要	  ：椅子が止まった時に削除されるゾーン
//作成日　：2021/08/05
//作成者　：渡邊龍音
//更新履歴：2021/08/10 渡邊龍音 BPから移行
//		　：2021/08/18 渡邊龍音 UIの表示
//--------------------------------------------------------------


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	TArray<AActor*> deleteActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
public:
	UFUNCTION(BlueprintCallable)
		void DeleteActor(AActor* _actor);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Cube;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName DeleteActorTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> outWidget;
};
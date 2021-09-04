//--------------------------------------------------------------
//クラス名：Bucket.h
//概要	  ：バケツを制御するクラス
//作成日　：2021/09/03
//作成者　：19CU0209 尾崎蒼宙
//更新履歴：2021/0
//--------------------------------------------------------------
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"		// スケルタルメッシュ
#include "Bucket.generated.h"

UCLASS()
class CHASE_API ABucket : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABucket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

public:
	UPROPERTY(EditAnyWhere)
		USkeletalMeshComponent* m_pbucket_mesh_;

};

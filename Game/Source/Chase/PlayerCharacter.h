// Fill out your copyright notice in the Description page of Project Settings.
/*使ってません*/

#pragma once


#include "Engine/StaticMesh.h"		// 矢印の代用(2021/04/13 Playerの代わりに使用)
#include "Engine/SkeletalMesh.h"	// Playerメッシュ
#include "Engine/Engine.h"			// スクリーンログ出力用
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class CHASE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	USceneComponent* m_proot_;
	bool is_rotation_;
	bool actionend_;
	float player_rotation_;

	void PlayerRotation(const float _axisval);
	void DeleteArrow();
	
protected:

public:

	UPROPERTY(EditAnywhere, Category = "Player")
		bool debugmode_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		// USkeletalMeshComponent* m_pplayermesh_;
		class UStaticMeshComponent* m_pplayermesh_;

	UPROPERTY(EditAnywhere, Category = "Player")
		float input_rotation_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float speed_scale_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		bool hit;

	// BPで初期設定出来ない不具合あり
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arrow")
		class UStaticMeshComponent* m_parrow_;

	// カプセルコンポーネントを参照している為同じものをBPに追加
	UFUNCTION()
		void ComponentHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

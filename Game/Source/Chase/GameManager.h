// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chair.h"
#include "Playerchara.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

UCLASS()
class CHASE_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	int nowroundnum_;
	float time_cnt_;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int maxroundnum_;

	UPROPERTY(EditAnywhere)
		int player_num_;

	UPROPERTY(EditAnywhere)
		AChair* control_chair_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float chair_create_time;

	UPROPERTY(EditAnywhere)
		TArray<APlayerchara*> players_;

	UPROPERTY(EditAnywhere)
		TArray<AChair*> chairs_;

	bool TimeCheck(float _deltatime);
};

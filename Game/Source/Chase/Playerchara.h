// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Chair.h"
#include "Playerchara.generated.h"

UCLASS()
class CHASE_API APlayerchara : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerchara();

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
	bool cretae_flag;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 1, ClampMax = 2),BlueprintReadWrite, Category = "Default Settings")
		int player_number_;												// âΩPÇ»ÇÃÇ©Çì¸ÇÍÇÈïœêî

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* chair_spawner_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* chair_stack_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
		AChair* control_chair_;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void CreateChair();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyF")
		void GetOperate();

	UFUNCTION(BlueprintCallable, Category = "MyF")
		void SetChairTag();
};

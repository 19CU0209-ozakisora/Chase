// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChara.h"

// Sets default values
APlayerChara::APlayerChara()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	acceleration_val_ = 1.05f;
	max_acceleration_val_ = 1.05f;

	// スプリングアームのオブジェクトを生成
	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("m_pSpringArm"));

	// スプリングアームにRootComponentをアタッチ
	m_pSpringArm -> SetupAttachment(RootComponent);

	// カメラとプレイヤーの距離
	m_pSpringArm->TargetArmLength = 0.f;

	// カメラの子リジョンテストを行うかを設定
	m_pSpringArm->bDoCollisionTest = false;

	// カメラ追従ラグを使うかを設定
	m_pSpringArm->bEnableCameraLag = false;

	// カメラ追従ラグの速度を設定
	m_pSpringArm->CameraLagSpeed = 35.f;

	m_pcamera_ = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_pcamera_ -> SetupAttachment(m_pSpringArm, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void APlayerChara::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChara::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector a = GetActorLocation();
	if (is_accelerator_)
	{
		acceleration_val_ *= 1.05f;
		a.X += acceleration_val_;

		SetActorLocation(a);
		//UE_LOG(LogTemp, Warning, TEXT("%f"), move_input_.X);
		
	}
	else
	{
		acceleration_val_ = max_acceleration_val_;
	}

	m_pcamera_->SetWorldRotation(FRotator(camera_rotation.X, camera_rotation.Y, 0.f));
	UE_LOG(LogTemp, Warning, TEXT("%f"), camera_rotation.X);
}

// Called to bind functionality to input
void APlayerChara::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Accelerator", IE_Pressed, this, &APlayerChara::SwitchAccelerator);
	InputComponent->BindAction("Accelerator", IE_Released, this, &APlayerChara::SwitchAccelerator);

	InputComponent->BindAxis("CameraVertical", this, &APlayerChara::CameraRotation_X);
	InputComponent->BindAxis("CameraHorizontal", this, &APlayerChara::CameraRotation_Y);
}

void APlayerChara::SwitchAccelerator()
{
	is_accelerator_ = !is_accelerator_;
}

void APlayerChara::CameraRotation_X(float _axisvalue_)
{
	camera_rotation.X += _axisvalue_;
}

void APlayerChara::CameraRotation_Y(float _axisvalue_)
{
	camera_rotation.Y += _axisvalue_;
}
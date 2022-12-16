// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "Curves/CurveFloat.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
	// testt

}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	LeftController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (LeftController != nullptr && LeftHandMeshClass != nullptr)
	{
		LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		LeftController->SetHand(EControllerHand::Left);
		LeftController->SetLeftHandMesh(LeftHandMeshClass);
		LeftController->SetOwner(this);
	}
	RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	if (RightController != nullptr && RightHandMeshClass != nullptr)
	{
		RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
		RightController->SetHand(EControllerHand::Right);
		RightController->SetRightHandMesh(RightHandMeshClass);
		RightController->SetOwner(this);
	}

	LeftController->PairController(RightController);
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);

	//LeftController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	//if (LeftController != nullptr)
	//{
	//	LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
	//	LeftController->SetHand(EControllerHand::Left);
	//	LeftController->SetOwner(this);
	//}
	//RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
	//if (RightController != nullptr)
	//{
	//	RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
	//	RightController->SetHand(EControllerHand::Right);
	//	RightController->SetOwner(this);
	//}

	//LeftController->PairController(RightController);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void AVRCharacter::MoveForward(float throttle)
{
	AddMovementInput(Camera->GetForwardVector(), throttle);
}

void AVRCharacter::MoveRight(float throttle)
{
	AddMovementInput(Camera->GetRightVector(), throttle);
}



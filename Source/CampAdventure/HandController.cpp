// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"
#include "VRCharacter.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/SphereComponent.h"


// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(MotionController);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(MotionController);
}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AHandController::ActorBeginOverlap);

	OnActorBeginOverlap.AddDynamic(this, &AHandController::ActorEndOverlap);
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsClimbing)
	{
		FVector HandMovement = GetActorLocation() - ClimbingStartLocation;

		GetAttachParentActor()->AddActorWorldOffset(-HandMovement);
	}
}

void AHandController::Grip()
{
	if (!bCanClimb)
	{
		return;
	}
	if (!bIsClimbing)
	{

		bIsClimbing = true;
		ClimbingStartLocation = GetActorLocation();

		OtherController->bIsClimbing = false;

		ACharacter* Character = Cast<ACharacter>(GetAttachParentActor());
		if (Character != nullptr)
		{
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			FString MovementModeStr = Character->GetCharacterMovement()->GetMovementName();
			UE_LOG(LogTemp, Warning, TEXT("Movement mode: %s"), *MovementModeStr);
		}
	}

}

void AHandController::Release()
{
	if (bIsClimbing)
	{
		bIsClimbing = false;

		ACharacter* Character = Cast<ACharacter>(GetAttachParentActor());
		if (Character != nullptr)
		{
			Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			FString MovementModeStr = Character->GetCharacterMovement()->GetMovementName();
			UE_LOG(LogTemp, Warning, TEXT("Movement mode: %s"), *MovementModeStr);
		}
	}

}

void AHandController::SetRightHandMesh(USkeletalMesh* RightHandMeshClass)
{
	HandMesh->SetSkeletalMesh(RightHandMeshClass);
	HandMesh->AddLocalRotation(FRotator(RightHPitchY, RightHYawZ, RightHRollX));
}

void AHandController::SetLeftHandMesh(USkeletalMesh* LeftHandMeshClass)
{
	HandMesh->SetSkeletalMesh(LeftHandMeshClass);
	HandMesh->AddLocalRotation(FRotator(-LeftHPitchY, -LeftHYawZ, -LefttHRollX));
}

void AHandController::PairController(AHandController* Controller)
{
	OtherController = Controller;
	OtherController->OtherController = this;
}

void AHandController::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bool bNewCanClimb = CanClimb();
	if (!bCanClimb && bNewCanClimb)
	{
		APawn* Pawn = Cast<APawn>(GetAttachParentActor());
		if (Pawn != nullptr)
		{
			APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
			if (PC != nullptr)
			{
				PC->PlayHapticEffect(HandHoldHaptic, MotionController->GetTrackingSource());
			}
		}
	}
	bCanClimb = bNewCanClimb;

}

void AHandController::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bCanClimb = CanClimb();
}

bool AHandController::CanClimb() const
{
	TArray<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors);

	for (AActor* OverlappingActor : OverlappedActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Climbable")))
		{
			return true;
		}
	}

	return false;
}

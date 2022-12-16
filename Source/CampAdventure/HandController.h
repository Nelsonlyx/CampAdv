// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MotionControllerComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "HandController.generated.h"

UCLASS()
class CAMPADVENTURE_API AHandController : public AActor
{
	GENERATED_BODY()
	
public:	

	AHandController();

	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }
	void SetRightHandMesh(USkeletalMesh* RightHandMeshClass);
	void SetLeftHandMesh(USkeletalMesh* LeftHandMeshClass);
	void PairController(AHandController* Controller);

	void Grip();
	void Release();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Callbacks
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	// Helpers
	bool CanClimb() const;


	// Default SubObject
	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* MotionController;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* HandMesh;
	UPROPERTY(EditDefaultsOnly)
	class UHapticFeedbackEffect_Base* HandHoldHaptic;

	// Config
	UPROPERTY(EditDefaultsOnly)
	float RightHPitchY = 70.0;
	UPROPERTY(EditDefaultsOnly)
	float RightHYawZ = 30;
	UPROPERTY(EditDefaultsOnly)
	float RightHRollX = 70;
	UPROPERTY(EditDefaultsOnly)
	float LeftHPitchY = -240;
	UPROPERTY(EditDefaultsOnly)
	float LeftHYawZ = -30;
	UPROPERTY(EditDefaultsOnly)
	float LefttHRollX =110;

	// State
	bool bCanClimb = false;
	bool bIsClimbing = false;
	FVector ClimbingStartLocation;

	AHandController* OtherController;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HandController.h"


#include "VRCharacter.generated.h"

UCLASS()
class CAMPADVENTURE_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float throttle);
	void MoveRight(float throttle);

	void GripLeft() { LeftController->Grip(); }
	void ReleaseLeft() { LeftController->Release(); }
	void GripRight() { RightController->Grip(); }
	void ReleaseRight() { RightController->Release(); }


private:
	// Configuration Parameters

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY()
	class AHandController* RightController;
	UPROPERTY()
	class AHandController* LeftController;


	UPROPERTY(EditAnywhere)
	class UCurveFloat* VelocityVsRadius;
	UPROPERTY()
	float PlayerSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;

	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* RightHandMeshClass;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* LeftHandMeshClass;

};

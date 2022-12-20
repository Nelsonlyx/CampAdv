// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HandController.h"
#include "InputActionValue.h"

#include "VRCharacter.generated.h"



UCLASS()
class CAMPADVENTURE_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVRCharacter();

protected:
	virtual void BeginPlay() override;

	// Interactions
	void Move(const FInputActionValue& Value);


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCameraComponent* Camera;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMesh* RightHandMeshClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMesh* LeftHandMeshClass;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* HandsMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* VRMove;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* GripLeftHand;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* GripRightHand;

private:

	void GripLeft() { LeftController->Grip(); UE_LOG(LogTemp, Warning, TEXT("Gripped")); }
	void ReleaseLeft() { LeftController->Release(); UE_LOG(LogTemp, Warning, TEXT("Released"));}
	void GripRight() { RightController->Grip(); UE_LOG(LogTemp, Warning, TEXT("Gripped"));}
	void ReleaseRight() { RightController->Release(); UE_LOG(LogTemp, Warning, TEXT("Released"));}

	void SetBlinkers();
	FVector2D GetBlinkerCenter();

private:

	// Components
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;
	UPROPERTY()
	class AHandController* RightController;
	UPROPERTY()
	class AHandController* LeftController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandController> HandControllerClass;
	
	// Walking Blinkers
	UPROPERTY(EditAnywhere)
	class UMaterialInterface* BlinkerMaterial;
	UPROPERTY(EditAnywhere)
	float BlinkerRadius = 0.5;
	UPROPERTY()
	UMaterialInstanceDynamic* BlinkerMatInstance;
	UPROPERTY(VisibleAnywhere)
	class UPostProcessComponent* PostProcessComponent;

	// Configuration Parameters
	UPROPERTY(EditAnywhere)
	class UCurveFloat* VelocityVsRadius;
	UPROPERTY()
	float PlayerSpeed;




};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// turn off annoying vscode reordering of include files
// clang-format off
// make sure that EnhancedInput is added to DMS332.Build.cs before this include
#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USkeletalMeshComponent;
// these two for the camera and arm
class USpringArmComponent;
class UCameraComponent;
// forward declarations for input stuff
class UInputMappingContext;
class UInputAction;

UCLASS()
class DMS332_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// add Input Category so it will be easier to find in Blueprints
  // UE5 style Input Mapping Context
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputMappingContext *CharacterMappingContext;
  // and two Input Actions
  // NOTE that these have Different Names from the ones in Bird class!!!
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction *MovementAction;
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction *LookingAction;

  
  // not forward declared - see InputActionValue include above
  void Move(const FInputActionValue &Value);
  void Look(const FInputActionValue &Value);

private:

  UPROPERTY(VisibleAnywhere)
  USpringArmComponent *SpringArm;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent *ViewCamera;

  /* jump input action
  this is in the private section but is accessible to blueprint
  because of the AllowPrivateAccess tag */
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input,
            meta = (AllowPrivateAccess = "true"))
  UInputAction *JumpAction;
  // end jump input action

};

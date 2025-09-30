// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// turn off annoying vscode reordering of include files
// clang-format off
// make sure that EnhancedInput is added to DMS332.Build.cs before this include
#include "InputActionValue.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

// forward declarations
class UCapsuleComponent;
class USkeletalMeshComponent;
// these two for the camera and arm
class USpringArmComponent;
class UCameraComponent;
// forward declarations for input stuff
class UInputMappingContext;
class UInputAction;

UCLASS()
class DMS332_API ABird : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ABird();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  // note forward declaration inline! we can do that!
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
  // forward declared 
  // add Input Category so it will be easier to find in Blueprints
  // UE5 style Input Mapping Context
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputMappingContext *BirdMappingContext;
  // and two Input Actions
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction *MoveAction;
  UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
  UInputAction *LookAction;

  // not forward declared - see InputActionValue include above
  void Move(const FInputActionValue &Value);
  void Look(const FInputActionValue &Value);


private:
  UPROPERTY(VisibleAnywhere)
  UCapsuleComponent *Capsule;

  UPROPERTY(VisibleAnywhere)
  USkeletalMeshComponent *BirdMesh;

  UPROPERTY(VisibleAnywhere)
  USpringArmComponent *SpringArm;

  UPROPERTY(VisibleAnywhere)
  UCameraComponent *ViewCamera;
};

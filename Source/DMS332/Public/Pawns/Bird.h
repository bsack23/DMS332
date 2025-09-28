// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// turn off annoying vscode reordering of include files
// clang-format off
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

// forward declarations
class UCapsuleComponent;
class USkeletalMeshComponent;
// these two for the camera and arm
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DMS332_API ABird : public APawn {
  GENERATED_BODY()

public:
  // Sets default values for this pawn's properties
  ABird();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  // Called to bind functionality to input
  virtual void SetupPlayerInputComponent(
      class UInputComponent *PlayerInputComponent) override;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

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

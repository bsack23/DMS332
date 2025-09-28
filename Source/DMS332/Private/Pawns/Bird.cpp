// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABird::ABird() {
  // Set this pawn to call Tick() every frame.  You can turn this off to improve
  // performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  // this creates the Capsule based on UCapsuleComponent template
  Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
  // and sets it as the root component
  SetRootComponent(Capsule);
  // set some height and radius
  Capsule->SetCapsuleHalfHeight(20.f);
  Capsule->SetCapsuleRadius(15.f);

  // again, take the pointer from Bird.h and create the skeletal mesh
  BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
  // attach it to the Root Component so they all move together
  BirdMesh->SetupAttachment(GetRootComponent());
  // Uncomment this if we want Player0 will auto-possess this Pawn
  // (E means that it's an element of type Enum - an enumerated list)
  // AutoPossessPlayer = EAutoRecieveInput::Player0;

  // make a spring arm for the camera and attach it to the Capsule
  SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
  SpringArm->SetupAttachment(Capsule);
  // set its length in cm
  SpringArm->TargetArmLength = 300.f;
  // add a camera component and attach it to the arm
  ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
  ViewCamera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ABird::BeginPlay() { Super::BeginPlay(); }

// Called every frame
void ABird::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
// headers for camera and arm
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// headers for input stuff
// make sure that EnhancedInput is added to DMS332.Build.cs before this include
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

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
  // AutoPossessPlayer = EAutoReceiveInput::Player0;

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
void ABird::BeginPlay() {
  Super::BeginPlay();
  // casting our new Player Controller
  // a cast is a way to explicitly convert a value from one type to another
  if (APlayerController *PlayerController =
          Cast<APlayerController>(GetController())) {
    // if the cast is successful
    // setting up the Blueprint Input Mapping Context for our class
    if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
                PlayerController->GetLocalPlayer())) {
      Subsystem->AddMappingContext(BirdMappingContext, 0);
    }
    // in Pawn.h: if true, this Pawn's pitch (yaw) will be updated to match the
    // Controller's ControlRotation pitch (yaw), if controlled by a
    // PlayerController.
    bUseControllerRotationPitch = true;
    bUseControllerRotationYaw = true;
  }
}

// Called every frame
void ABird::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

// set up the Action Values so they can move the Pawn
void ABird::Move(const FInputActionValue &Value) {
  // input from keyboard is 1D - forward & back
  // so all we need is a float value
  const float DirectionValue = Value.Get<float>();
  // check for a valid controller and non-zero value
  if (Controller && (DirectionValue != 0.f)) {
    // get the current direction as a vector
    FVector Forward = GetActorForwardVector();
    // do vector math to move
    AddMovementInput(Forward, DirectionValue);
  }
}

// set up the Action Values so the Pawn can look around while moving
void ABird::Look(const FInputActionValue &Value) {
  // input from mouse's x & y is 2D - make a vector
  const FVector2D LookAxisValue = Value.Get<FVector2D>();
  // check for valid controller
  if (GetController()) {
    // turn / look left-right
    AddControllerYawInput(LookAxisValue.X);
    // turn / look up-down
    AddControllerPitchInput(LookAxisValue.Y);
  }
}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
  Super::SetupPlayerInputComponent(PlayerInputComponent);
  // CastChecked: another type of cast - does the cast and checks for null ptr
  if (UEnhancedInputComponent *EnhancedInputComponent =
          CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,
                                       this, &ABird::Move);
    EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered,
                                       this, &ABird::Look);
  }
}

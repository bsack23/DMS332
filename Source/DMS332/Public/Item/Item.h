// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

// forward declaration
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class DMS332_API AItem : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  AItem();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

protected:
  /** sphere component - forward declared */
  UPROPERTY(VisibleAnywhere, Category = "Switch Components")
  class USphereComponent *Sphere;

  // add 'virtual' to these so they can be customized in child classes
  // like 'Utensil'
  UFUNCTION()
  virtual void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                              class AActor *OtherActor,
                              class UPrimitiveComponent *OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep,
                              const FHitResult &SweepResult);

  /** called when something leaves the sphere component */
  UFUNCTION()
  virtual void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                            class AActor *OtherActor,
                            class UPrimitiveComponent *OtherComp,
                            int32 OtherBodyIndex);

  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

  UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
  UStaticMeshComponent *ItemMesh;

  UPROPERTY(EditAnywhere, BlueprintReadWrite)
  float RotationRate = 40.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
  float SineAmplitude = 1.f;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
  float SineRate = 1.f;

  UPROPERTY(EditAnywhere)
  UNiagaraComponent *EmbersEffect;

private:
  UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
            meta = (AllowPrivateAccess = "true"))
  float RunningTime;
};

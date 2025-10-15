// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class DMS332_API ALightSwitch : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  ALightSwitch();
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  /** point light component
 (notice that we're forward declaring here with class keyword)
  */
  UPROPERTY(VisibleAnywhere, Category = "Switch Components")
  class UPointLightComponent *PointLight;

  /** sphere component */
  UPROPERTY(VisibleAnywhere, Category = "Switch Components")
  class USphereComponent *Sphere;

  UFUNCTION()
  void OnOverlapBegin(class UPrimitiveComponent *OverlappedComp,
                      class AActor *OtherActor,
                      class UPrimitiveComponent *OtherComp,
                      int32 OtherBodyIndex, bool bFromSweep,
                      const FHitResult &SweepResult);

  /** called when something leaves the sphere component */
  UFUNCTION()
  void OnOverlapEnd(class UPrimitiveComponent *OverlappedComp,
                    class AActor *OtherActor,
                    class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

  /** the desired intensity for the light */
  UPROPERTY(VisibleAnywhere, Category = "Switch Variables")
  float DesiredIntensity;
  UPROPERTY(VisibleAnywhere, Category = "Switch Variables")
  FLinearColor NewLightColor;

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;
};

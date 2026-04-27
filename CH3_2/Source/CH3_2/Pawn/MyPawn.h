// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "MyPawn.generated.h"
//컴포넌트
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
//입력
class UMPInputConfig;
class UInputMappingContext;

UCLASS()
class CH3_2_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	
	AMyPawn();
	virtual void BeginPlay() override;

protected:
	//입력컴포넌트
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//컴포넌트 선언
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "properties")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

private://입력값
	void InputMove(const FInputActionValue& InValue);
	void InputLook(const FInputActionValue& InValue);

protected://입력 에셋이 들어있는 config와 IMC가져오기
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UMPInputConfig> MyPawnInputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UInputMappingContext> MyPawnInputMappingContext;
};

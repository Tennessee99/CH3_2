// Fill out your copyright notice in the Description page of Project Settings.


#include "CH3_2/Pawn/MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CH3_2/Input/MPInputConfig.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	float CharacterHalfHeight = 90.f;
	float CharacterRadius = 40.f;


	//폰 컴포넌트 지정
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetCapsuleHalfHeight(CharacterHalfHeight);
	CapsuleComponent->SetCapsuleRadius(CharacterRadius);
	CapsuleComponent->SetSimulatePhysics(false);
	CapsuleComponent->SetCollisionProfileName(TEXT("OverlapAll"));

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	FVector PivotPosition(0.f, 0.f, -CharacterHalfHeight);
	FRotator PivotRotation(0.f, -90.f, 0.f);
	SkeletalMeshComponent->SetRelativeLocationAndRotation(PivotPosition, PivotRotation);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 600.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	
	


}


// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	//내가 만들었던 컨트롤러가 아닌 언리얼 기본 부모 클래스
	APlayerController* PawnController = Cast<APlayerController>(GetController());
	if (IsValid(PawnController) == true)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PawnController->GetLocalPlayer());
		if (IsValid(Subsystem) == true)
		{
			Subsystem->AddMappingContext(MyPawnInputMappingContext, 0);
		}
	}
}

//액션 바인딩
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(EnhancedInputComponent) == true)
	{
		EnhancedInputComponent->BindAction(
			MyPawnInputConfig->Move,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::InputMove);
		EnhancedInputComponent->BindAction(
			MyPawnInputConfig->Look,
			ETriggerEvent::Triggered,
			this,
			&AMyPawn::InputLook);
	}

}

void AMyPawn::InputMove(const FInputActionValue& InValue)
{
	FVector2D MovementVector = InValue.Get<FVector2D>();

	//UE_LOG(LogTemp, Log, TEXT("MoveInput: (%.1f, %.1f)"),MovementVector.X,MovementVector.Y);

	AddActorLocalOffset(FVector(MovementVector.X * 1000.f * GetWorld()->GetDeltaSeconds(), MovementVector.Y * 1000.f * GetWorld()->GetDeltaSeconds(), 0.f));


	//AddMovementInput(GetActorForwardVector(), MovementVector.X);//이거는 캐릭터용. 일반 Pawn은 인클루드 추가할게 있음
	//AddMovementInput(GetActorRightVector(), MovementVector.Y);

}

void AMyPawn::InputLook(const FInputActionValue& InValue)
{
	FVector2D LookVector = InValue.Get<FVector2D>();

	//UE_LOG(LogTemp, Log, TEXT("MoveInput: (%.1f, %.1f)"), LookVector.X, LookVector.Y);

	AddActorLocalRotation(FRotator(0.f, LookVector.X, 0.f));
	//캐릭터가 따라움직이지 않게 하기 위해 상하 회전은 액터가 아니라 스프링암을 움직이게 함
	FRotator CurrentSpringArmRotation = SpringArmComponent->GetRelativeRotation();
	CurrentSpringArmRotation += FRotator(-LookVector.Y * 100.f * GetWorld()->GetDeltaSeconds(), 0.f, 0.f);
	SpringArmComponent->SetRelativeRotation(CurrentSpringArmRotation);
	//AddControllerYawInput(LookVector.X);//이거 쓰지 말란다
	//AddControllerPitchInput(LookVector.Y);

}

void AMyPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}


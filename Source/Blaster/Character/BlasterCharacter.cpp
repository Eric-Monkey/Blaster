// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ABlasterCharacter::ABlasterCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	//SpringArmComp
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->TargetArmLength = 600;
	SpringArmComp->bUsePawnControlRotation = true;
	

	//CameraComp
	CameraComp = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}


void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this , &ABlasterCharacter::MoveForword);
	PlayerInputComponent->BindAxis("MoveRight", this , &ABlasterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this , &ABlasterCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnUp", this , &ABlasterCharacter::TurnUp);

}

void ABlasterCharacter::MoveForword(float value)
{
	if (Controller!=nullptr && value!=0.f) {
		const FRotator YawRotator = FRotator(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,value);
	}
}

void ABlasterCharacter::MoveRight(float value)
{
	if (Controller!=nullptr && value !=0.f)
	{
		const FRotator YawRotator = FRotator(0.f,Controller->GetControlRotation().Yaw,0.f);
		const FVector Direction = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}

}

void ABlasterCharacter::Turn(float value)
{
	AddControllerYawInput(value);
}

void ABlasterCharacter::TurnUp(float value)
{
	AddControllerPitchInput(value);
}

void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



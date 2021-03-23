// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/SkinnedMeshComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;


	//adds an instance of a gun actor object to be initiated with shooter
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    GetMesh()->USkinnedMeshComponent::HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//basic player wasd movements and jump
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("HorizontalMovement"), this, &AShooterCharacter::HorizontalMovement);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed,this,&ACharacter::Jump);

	//control aim on y-x axis
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookHorizontal"), this, &AShooterCharacter::AddControllerYawInput);

	//shooting implementation on rifle gun
	PlayerInputComponent->BindAction(TEXT("ShootLMB"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

}	

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) {

	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead()) {
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	}
	return DamageToApply;
}

bool AShooterCharacter::IsDead() const {

	return Health <= 0;

}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::MoveForward(float AxisValue) {

	AddMovementInput(GetActorForwardVector() * AxisValue);

}

void AShooterCharacter::HorizontalMovement(float AxisValue) {

	AddMovementInput(GetActorRightVector() * AxisValue);

}

void AShooterCharacter::Shoot() {

	Gun->PullTrigger();

}

void AShooterCharacter::Grenade() {



}
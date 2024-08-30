// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "NetClassProject_YJCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ANetClassProject_YJCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabPistolAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FireAction;

	//  meta = (AllowPrivateAccess = "true") : private 멤버를 에디터에 보이도록 하는 설정 
	
public:
	ANetClassProject_YJCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void OnGrabPistol(const FInputActionValue& Value);
	void MyTakePistol();	
	void MyReleasePistol();
	void OnFirePistol(const FInputActionValue& value);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bHasPistol;

	// 태어날때 부터 총의목록을 
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	TArray<AActor*> PistolList;

	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	class USceneComponent* HandComp; // 이걸 손에 부착하고 위치조절을 함

	UPROPERTY()
	class AActor* GrabPistolActor;

	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	float GrabPistolDistance =300;

	void AttachPistol(AActor* pistolActor);
	void DetachPistol();

	// 마우스왼버튼으로 총을 쏘기
	// 총알이 부딪힌 곳에 총알자국을 표현하기
	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	class UParticleSystem* BullectFX;

	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	TSubclassOf<class UUserWidget> WBP_mainWidget;
	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	class UMainWidget* MainWidget_UI;
	void InitMainWidget();
	UPROPERTY(EditDefaultsOnly,Category=Pistol)
	int32 MaxBullectCount=10;
	int32 curBullectCount=MaxBullectCount;
	
};


// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#pragma once

#include "CoreMinimal.h"
#include "MessagePayload.h"
#include "UObject/Interface.h"
#include "EventMessageReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEventMessageReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface to receive event messages. 
 */
class EVENTMESSAGINGSYSTEM_API IEventMessageReceiver
{
	GENERATED_BODY()

public:

	/**
	 * Event that gets called when this actor receives an event message.
	 * @param EventName		The received event name.
	 * @param Sender			The sender object of this message. If sent from Blueprint, it will be the graph owner.
	 * @param Payload		The optional message payload with key-value data pairs.
	 */
	UFUNCTION(BlueprintNativeEvent)
	void OnEventMessageReceived(FName EventName, UObject * Sender, FMessagePayload Payload);

	/**
	* A native event that gets called when this actor receives an event message.
	* @param EventName		The received event name.
	* @param Sender			The sender object of this message. If sent from Blueprint, it will be the graph owner.
	* @param Payload		The optional message payload with key-value data pairs.
	*/
	virtual void OnEventMessageReceived_Implementation(FName EventName, UObject * Sender, FMessagePayload Payload) {}
};

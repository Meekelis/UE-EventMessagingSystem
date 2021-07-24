// Copyright (c) 2021, Kazimieras Mikelis, MIT license.

#pragma once

#include "CoreMinimal.h"

#include "MessagePayload.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventMessageStatics.generated.h"

// A stat group for profiling event messages. Run command "stat EventMessaging" to show on screen.
DECLARE_STATS_GROUP(TEXT("EventMessaging"), STATGROUP_EventMessaging, STATCAT_Advanced);

// Cycle stat probing how long event message routing takes.
DECLARE_CYCLE_STAT(TEXT("Routing"), STAT_Routing, STATGROUP_EventMessaging);

// Cycle stat probing how long the retrieval of every world actor takes.
DECLARE_CYCLE_STAT(TEXT("Actor query"), STAT_ActorQuery, STATGROUP_EventMessaging); 

/**
 * A static library of functions for sending and processing event messages.
 * This class is all that is needed to send event messages to objects that implement the EventMessageReceiver interface.
 */
UCLASS()
class EVENTMESSAGINGSYSTEM_API UEventMessageStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Get a value of an integer property from an event message payload.
	 * @param Payload		The payload where this property is contained.
	 * @param PropertyName	The name of this property.
	 */
	UFUNCTION(BlueprintPure, meta=(DisplayName="Get Integer Payload"))
	static int32 GetIntPayload_BP(const FMessagePayload & Payload, FName PropertyName);

	/**
	* Get a value of a name property from an event message payload.
	* @param Payload		The payload where this property is contained.
	* @param PropertyName	The name of this property.
	*/
	UFUNCTION(BlueprintPure, meta=(DisplayName="Get Name Payload"))
    static FName GetNamePayload_BP(const FMessagePayload & Payload, FName PropertyName);

	/**
	* Get a value of a byte property from an event message payload.
	* @param Payload		The payload where this property is contained.
	* @param PropertyName	The name of this property.
	*/
	UFUNCTION(BlueprintPure, meta=(DisplayName="Get Byte Payload"))
    static uint8 GetBytePayload_BP(const FMessagePayload & Payload, FName PropertyName);

	/**
	* Get a value of a string property from an event message payload.
	* @param Payload		The payload where this property is contained.
	* @param PropertyName	The name of this property.
	*/
	UFUNCTION(BlueprintPure, meta=(DisplayName="Get String Payload"))
    static FString GetStringPayload_BP(const FMessagePayload & Payload, FName PropertyName);

	/**
	* Get a value of an object property from an event message payload.
	* @param Payload		The payload where this property is contained.
	* @param PropertyName	The name of this property.
	*/
	UFUNCTION(BlueprintPure, meta=(DisplayName="Get Object Payload"))
    static UObject * GetObjectPayload_BP(const FMessagePayload & Payload, FName PropertyName);

	/**
	 * Add a property of integer type to this event message payload.
	 * @param Payload		The payload to which this property should be appended.
	 * @param PropertyName	The name of this property.
	 * @param Value			The value of this property.
	 */
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Integer To Payload"))
	static FMessagePayload AddIntPayload_BP(FMessagePayload Payload, FName PropertyName, int32 Value);

	/**
	* Add a property of name type to this event message payload.
	* @param Payload		The payload to which this property should be appended.
	* @param PropertyName	The name of this property.
	* @param Value			The value of this property.
	*/
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Name To Payload"))
    static FMessagePayload AddNamePayload_BP(FMessagePayload Payload, FName PropertyName, FName Value);

	/**
	* Add a property of byte type to this event message payload.
	* @param Payload		The payload to which this property should be appended.
	* @param PropertyName	The name of this property.
	* @param Value			The value of this property.
	*/
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Byte To Payload"))
    static FMessagePayload AddBytePayload_BP(FMessagePayload Payload, FName PropertyName, uint8 Value);

	/**
	* Add a property of string type to this event message payload.
	* @param Payload		The payload to which this property should be appended.
	* @param PropertyName	The name of this property.
	* @param Value			The value of this property.
	*/
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add String To Payload"))
    static FMessagePayload AddStringPayload_BP(FMessagePayload Payload, FName PropertyName, FString Value);

	/**
	* Add a property of object type to this event message payload.
	* @param Payload		The payload to which this property should be appended.
	* @param PropertyName	The name of this property.
	* @param Value			The value of this property.
	*/
	UFUNCTION(BlueprintCallable, meta=(DisplayName="Add Object To Payload"))
    static FMessagePayload AddObjectPayload_BP(FMessagePayload Payload, FName PropertyName, UObject * Value);

	/**
	 * Make an empty payload object to be filled with Add To Payload functions.
	 */
	UFUNCTION(BlueprintPure)
	static FMessagePayload MakeLiteralEventMessagePayload();

	/**
	 * Send an event message to all actors with a tag.
	 * Note: The actors must implement the Event Message Receiver interface.
	 * @param Sender			Sending object. Auto-filled in most cases.
	 * @param ReceiverActorTag	A tag the message recipient must have.
	 * @param EventName			The name of the event.
	 * @param Payload			Payload data.
	 */
	UFUNCTION(BlueprintCallable, meta=(WorldContext="Sender", AdvancedDisplay="Payload"))
	static void SendEventMessageByTag(UObject * Sender, FName ReceiverActorTag, FName EventName, FMessagePayload Payload);

	/**
	* Send an event message to all actors of a particular class.
	* Note: The actors must implement the Event Message Receiver interface.
	* @param Sender			Sending object. Auto-filled in most cases.
	* @param ReceiverClass	A class the receiver must have or be derived from.
	* @param EventName		The name of the event.
	* @param Payload		Payload data.
	*/
	UFUNCTION(BlueprintCallable, meta=(WorldContext="Sender", AdvancedDisplay="Payload"))
    static void SendEventMessageByClass(UObject * Sender, UClass * ReceiverClass, FName EventName, FMessagePayload Payload);

	/**
	* Send an event message to all actors capable of receiving it.
	* Note: The actors must implement the Event Message Receiver interface.
	* @param Sender			Sending object. Auto-filled in most cases.
	* @param EventName			The name of the event.
	* @param Payload			Payload data.
	*/
	UFUNCTION(BlueprintCallable, meta=(WorldContext="Sender", AdvancedDisplay="Payload"))
    static void SendMulticastEventMessage(UObject * Sender, FName EventName, FMessagePayload Payload);

private:


	/**
	 * A function to get world actors faster than Unreal Engine's default ones.
	 */
	static void GetWorldActorsFast(UObject * WorldContext, TArray<AActor*> & OutActors);
	
};

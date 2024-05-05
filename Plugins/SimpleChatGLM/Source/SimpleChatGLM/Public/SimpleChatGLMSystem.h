// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HTTP/SimpleChatGLMHttp.h"
#include "SimpleChatGLMSystem.generated.h"

UCLASS(BlueprintType)
class SIMPLECHATGLM_API USimpleChatGLMSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	USimpleChatGLMSystem();

protected:

	void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool isSucces);
	void OnRequestProgress(FHttpRequestPtr HttpRequest, int32 SendByte, int32 ReceivedByte);
	void OnRequestHeaderReceived(FHttpRequestPtr HttpRequest, const FString& Header, const FString& HeaderValue);

private:
	TSharedPtr<SimpleChatGLMHTTP::FHTTP> HTTP;

};

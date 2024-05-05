// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SimpleChatGLMSystem.h"

USimpleChatGLMSystem::USimpleChatGLMSystem()
{
	SimpleChatGLMHTTP::FHttpDelegate HttpDelegate;
	HttpDelegate.CompleteDelegate.BindLambda(
		[&](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool isSucces)
		{
			OnRequestComplete(HttpRequest, HttpResponse, isSucces);
		}
	);

	HttpDelegate.ProgressDelegate.BindLambda(
		[&](FHttpRequestPtr HttpRequest, int32 SendByte, int32 ReceivedByte)
		{
			OnRequestProgress(HttpRequest, SendByte, ReceivedByte);
		}
	);

	HttpDelegate.HeaderReceivedDelegate.BindLambda(
		[&](FHttpRequestPtr HttpRequest, const FString& Header, const FString& HeaderValue)
		{
			OnRequestHeaderReceived(HttpRequest, Header, HeaderValue);
		}
	);
}

void USimpleChatGLMSystem::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool isSucces)
{
}

void USimpleChatGLMSystem::OnRequestProgress(FHttpRequestPtr HttpRequest, int32 SendByte, int32 ReceivedByte)
{
}

void USimpleChatGLMSystem::OnRequestHeaderReceived(FHttpRequestPtr HttpRequest, const FString& Header, const FString& HeaderValue)
{
}

#include "HTTP/SimpleChatGLMHttp.h"

TSharedPtr<SimpleChatGLMHTTP::FHTTP> SimpleChatGLMHTTP::FHTTP::CreateHTTPObject(FHttpDelegate InDelegate)
{
	return TSharedPtr<FHTTP>();
}

SimpleChatGLMHTTP::FHTTP::FHTTP(FHttpDelegate InDelegate)
{
}

FGuid SimpleChatGLMHTTP::FHTTP::Request(const FString& InUrl, const FString& InContent, const TMap<FString, FString>& InCustomMetadataHeader, bool isSynchronous, SimpleChatGLMHTTP::EHTTPVerbType VerbType)
{
	return FGuid();
}

FGuid SimpleChatGLMHTTP::FHTTP::Request(const FString& InUrl, const TArray<uint8>& InByteData, const TMap<FString, FString>& InCustomMetadataHeader, bool isSynchronous, SimpleChatGLMHTTP::EHTTPVerbType VerbType)
{
	return FGuid();
}

void SimpleChatGLMHTTP::FHTTP::CancelRequest(const FGuid& InRequestID)
{
}

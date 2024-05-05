#include "HTTP/SimpleChatGLMHttp.h"

#include "HttpManager.h"

TSharedPtr<SimpleChatGLMHTTP::FHTTP> SimpleChatGLMHTTP::FHTTP::CreateHTTPObject(FHttpDelegate InDelegate)
{
	return MakeShareable(new FHTTP(InDelegate));
}

SimpleChatGLMHTTP::FHTTP::FHTTP(FHttpDelegate InDelegate)
	: Delegate(InDelegate)
{
}

FGuid SimpleChatGLMHTTP::FHTTP::Request(const FString& InUrl, const FString& InContent, const TMap<FString, FString>& InCustomMetadataHeader, bool isAsynchronous, SimpleChatGLMHTTP::EHTTPVerbType VerbType)
{
	return Request(InUrl, InContent, TArray<uint8>(), InCustomMetadataHeader, isAsynchronous, VerbType);
}

FGuid SimpleChatGLMHTTP::FHTTP::Request(const FString& InUrl, const TArray<uint8>& InByteData, const TMap<FString, FString>& InCustomMetadataHeader, bool isAsynchronous, SimpleChatGLMHTTP::EHTTPVerbType VerbType)
{
	return Request(InUrl, TEXT(""), InByteData, InCustomMetadataHeader, isAsynchronous, VerbType);
}

FGuid SimpleChatGLMHTTP::FHTTP::Request(const FString& InUrl, const FString& InContent, const TArray<uint8>& InByte, const TMap<FString, FString>& InCustomMetadataHeader, bool isAsynchronous, SimpleChatGLMHTTP::EHTTPVerbType VerbType)
{
	FGuid RequestID = FGuid::NewGuid();

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(InUrl);
	Request->SetTimeout(15.f);//Overtime tolerence
	Request->SetHeader(TEXT("RequestID"), RequestID.ToString());

	//Update every header and its value to Request to send
	for(auto& Tmp : InCustomMetadataHeader)
	{
		Request->SetHeader(Tmp.Key, Tmp.Value);
	}

	Request->SetVerb(HTTPVerbeToString(VerbType));

	if(InByte.Num() > 0)
	{
		Request->SetContent(InByte);
	}
	else if(!InContent.IsEmpty())
	{
		Request->SetContentAsString(InContent);
	}

	Request->OnProcessRequestComplete().BindSP(this, &FHTTP::OnRequestComplete);
	Request->OnRequestProgress().BindSP(this, &FHTTP::OnRequestProgress);
	Request->OnHeaderReceived().BindSP(this, &FHTTP::OnRequestHeaderReceived);

	bool isSucces = Request->ProcessRequest();

	if(isSucces)
	{
		HttpRequests.Add(RequestID, Request);
		if(isAsynchronous)
		{
			//Immediately procede the next waiting request
			FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::Default);
		}
	}
	else
	{
		RequestID = FGuid();
	}

	return RequestID;
}

void SimpleChatGLMHTTP::FHTTP::CancelRequest(const FGuid& InRequestID)
{
}

bool SimpleChatGLMHTTP::FHTTP::IsValidRequest(const FGuid& InRequestID) const
{
	return HttpRequests.Contains(InRequestID);
}

void SimpleChatGLMHTTP::FHTTP::OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool isSucces)
{
	//Once request finised, get its ID and remove it from Pool
	FString RequestIDString = HttpRequest->GetHeader(TEXT("RequestID"));
	FGuid RequestID;
	FGuid::Parse(RequestIDString, RequestID);
	HttpRequests.Remove(RequestID);

	//Call back
	Delegate.CompleteDelegate.ExecuteIfBound(HttpRequest, HttpResponse, isSucces);
}

void SimpleChatGLMHTTP::FHTTP::OnRequestProgress(FHttpRequestPtr HttpRequest, int32 SendByte, int32 ReceivedByte)
{
	Delegate.ProgressDelegate.ExecuteIfBound(HttpRequest, SendByte, ReceivedByte);
}

void SimpleChatGLMHTTP::FHTTP::OnRequestHeaderReceived(FHttpRequestPtr HttpRequest, const FString& Header, const FString& HeaderValue)
{
	Delegate.HeaderReceivedDelegate.ExecuteIfBound(HttpRequest, Header, HeaderValue);
}

FString SimpleChatGLMHTTP::FHTTP::HTTPVerbeToString(EHTTPVerbType InVerbType)
{
	switch (InVerbType)
	{
		case EHTTPVerbType::CHATGLM_POST: return TEXT("POST");
		case EHTTPVerbType::CHATGLM_PUT:  return TEXT("PUT");
		case EHTTPVerbType::CHATGLM_GET:  return TEXT("GET");
		case EHTTPVerbType::CHATGLM_DELETE:  return TEXT("DELETE");
	}

	return TEXT("POST"); 
}

#pragma once

#include "CoreMinimal.h"
#include "Http.h"

namespace SimpleChatGLMHTTP
{
	enum  class EHTTPVerbType : uint8
	{
		CHATGLM_POST,
		CHATGLM_PUT,
		CHATGLM_GET,
		CHATGLM_DELETE,
	};

	/**
	 * @brief Different delegate use when a http request is using
	 */
	struct SIMPLECHATGLM_API FHttpDelegate
	{
		FHttpRequestCompleteDelegate CompleteDelegate; //Delegate use for a callback when Request is completed
		FHttpRequestProgressDelegate ProgressDelegate; //Delegate use for a callback when Request is progressing
		FHttpRequestHeaderReceivedDelegate HeaderReceivedDelegate; //Delegate use for a callback when receive a header
	};

	struct SIMPLECHATGLM_API FHTTP : public TSharedFromThis<FHTTP>
	{
		static TSharedPtr<FHTTP> CreateHTTPObject(FHttpDelegate InDelegate);

	public :
		FHTTP(FHttpDelegate InDelegate);

		/**
		 * @brief Request for a string, Ex : Normal chat with word only
		 * @param InUrl 
		 * @param InContent 
		 * @param InCustomMetadataHeader 
		 * @param isSynchronous 
		 * @param VerbType 
		 * @return 
		 */
		FGuid Request(
			const FString& InUrl,
			const FString& InContent,
			const TMap<FString, FString>& InCustomMetadataHeader,
			bool isSynchronous = false,
			SimpleChatGLMHTTP::EHTTPVerbType VerbType = SimpleChatGLMHTTP::EHTTPVerbType::CHATGLM_POST
		);


		/**
		 * @brief Request for a binary data, Ex : Image data
		 * @param InUrl 
		 * @param InByteData 
		 * @param InCustomMetadataHeader 
		 * @param isSynchronous 
		 * @param VerbType 
		 * @return 
		 */
		FGuid Request(
			const FString& InUrl,
			const TArray<uint8>& InByteData,
			const TMap<FString, FString>& InCustomMetadataHeader,
			bool isSynchronous = false,
			SimpleChatGLMHTTP::EHTTPVerbType VerbType = SimpleChatGLMHTTP::EHTTPVerbType::CHATGLM_POST
		);

		/**
		 * @brief Use for cancel a progressing Request
		 * @param InRequestID 
		 */
		void CancelRequest(const FGuid& InRequestID);

	private :
		FGuid Request(
			const FString& InUrl,
			const FString& InContent1,
			const TArray<uint8>& InContent2,
			const TMap<FString, FString>& InCustomMetadataHeader,
			bool isSynchronous = false,
			SimpleChatGLMHTTP::EHTTPVerbType VerbType = SimpleChatGLMHTTP::EHTTPVerbType::CHATGLM_POST
		);

	private:
		void OnRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool isSucces);
		void OnRequestProgress(FHttpRequestPtr HttpRequest, int32 SendByte, int32 ReceivedByte);
		void OnRequestHeaderReceived(FHttpRequestPtr HttpRequest, const FString& Header, const FString& HeaderValue);


	private:
		FString HTTPVerbeToString(EHTTPVerbType InVerbType);
	};
	
}

#pragma once

#include "WebApiRequestBody.generated.h"

/** リクエストタイプ */
UENUM(BlueprintType)
enum class EWebApiRequestType : uint8
{
	Invalid,
	Get,
	Put,
	Post,
};

/** リクエスト */
UCLASS(Abstract, BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiRequestBody : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** リクエストヘッダー */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|WebApi")
	TMap<FString, FString> RequestHeaders;

	/** ダミーリクエストフラグ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|WebApi")
	bool IsDummyRequest;

private:
	/** キャッシュしたUObjectプロパティ名リスト */
	static TArray<FString> CachedUObjectPropertyNames;

public:
	/**
	 * リクエストインスタンスを作成
	 * @param RequestClass リクエストクラス
	 * @return リクエストインスタンス
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi", meta=(DisplayName="Create Web Api Request", WorldContext="WorldContext", DeterminesOutputType="RequestClass"))
	static UWebApiRequestBody* Create(TSubclassOf<UWebApiRequestBody> RequestClass);

	/**
	 * リクエストインスタンスを作成
	 */
	template <typename RequestClassType>
	static RequestClassType* Create()
	{
		return Cast<RequestClassType>(Create(RequestClassType::StaticClass()));
	}

	/**
	 * プロパティ名リストを作成
	 * @param RequestClass リクエストクラス
	 * @return プロパティ名リスト
	 */
	static TArray<FString> GetPropertyNames(TSubclassOf<UWebApiRequestBody> RequestClass);

	/**
	 * リクエストタイプ取得
	 * @return リクエストタイプ
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	virtual EWebApiRequestType GetRequestType() const
	{
		return EWebApiRequestType::Invalid;
	}

	/**
	 * リクエストタイプ文字列取得
	 * @return リクエストタイプ文字列
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	FString GetRequestTypeAsString() const
	{
		switch (GetRequestType())
		{
		case EWebApiRequestType::Get:
			return FString("GET");
		case EWebApiRequestType::Put:
			return FString("PUT");
		case EWebApiRequestType::Post:
			return FString("Post");
		default:
			check(0);
		}

		return FString("");
	}

	/**
	 * 文字列としてリクエスト本体取得
	 * @param RequestBody リクエスト本体格納先
	 * @return 正常に取得できたらtrue
	 */
	virtual bool GetRequestBodyAsString(FString& RequestBody) const
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("%s::GetRequestBodyAsString is not supported."), *GetClass()->GetName());
		return false;
	}

	/**
	 * 文字列としてリクエスト本体取得
	 * @param RequestBody リクエスト本体格納先
	 * @param Success 正常に取得できたらtrue
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	void GetRequestBodyAsString(FString& RequestBody, bool& Success) const
	{
		Success = GetRequestBodyAsString(RequestBody);
	}

	/**
	 * バイナリとしてリクエスト本体取得
	 * @param RequestBody リクエスト本体格納先
	 * @return 正常に取得できたらtrue
	 */
	virtual bool GetRequestBodyAsBinary(TArray<uint8>& RequestBody) const
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("%s::GetRequestBodyAsBinary is not supported."), *GetClass()->GetName());
		return false;
	}

	/**
	 * バイナリとしてリクエスト本体取得
	 * @param RequestBody リクエスト本体格納先
	 * @param Success 正常に取得できたらtrue
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	void GetRequestBodyAsBinary(TArray<uint8>& RequestBody, bool& Success) const
	{
		Success = GetRequestBodyAsBinary(RequestBody);
	}

	/**
	 * デフォルトのリクエストヘッダー設定
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	virtual void SetDefaultRequestHeaders() {}

	/**
	 * リクエストヘッダー設定
	 * @param Key ヘッダーキー
	 * @param Value ヘッダー値
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetRequestHeader(const FString& Key, const FString& Value);

	/**
	 * リクエストヘッダー設定
	 * @param Key ヘッダーキー
	 * @param Value ヘッダー値
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetNameRequestHeader(const FString& Key, const FName& Value)
	{
		SetRequestHeader(Key, Value.ToString());
	}

	/**
	 * リクエストヘッダー設定
	 * @param Key ヘッダーキー
	 * @param Value ヘッダー値
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetTextRequestHeader(const FString& Key, const FText& Value)
	{
		SetRequestHeader(Key, Value.ToString());
	}

	/**
	 * リクエストヘッダー設定
	 * @param Key ヘッダーキー
	 * @param Value ヘッダー値
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetIntegerRequestHeader(const FString& Key, int32 Value)
	{
		SetRequestHeader(Key, FString::FromInt(Value));
	}

	/**
	 * リクエストヘッダー設定
	 * @param Key ヘッダーキー
	 * @param Value ヘッダー値
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetFloatRequestHeader(const FString& Key, float Value)
	{
		SetRequestHeader(Key, FString::SanitizeFloat(Value));
	}

	/**
	 * リクエストヘッダー取得
	 * @param Key ヘッダーキー
	 * @return ヘッダー値
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	const FString& GetRequestHeader(const FString& Key) const;

	/**
	 * リクエストヘッダー取得
	 * @param Key ヘッダーキー
	 * @return ヘッダー値
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	int32 GetIntegerRequestHeader(const FString& Key) const
	{
		return FCString::Atoi(*GetRequestHeader(Key));
	}

	/**
	 * リクエストヘッダー取得
	 * @param Key ヘッダーキー
	 * @return ヘッダー値
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	float GetFloatRequestHeader(const FString& Key) const
	{
		return FCString::Atof(*GetRequestHeader(Key));
	}
};

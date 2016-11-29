#pragma once

#include "WebApiResponseBody.generated.h"

USTRUCT(BlueprintType)
struct FWebApiResponseContent
{
	GENERATED_BODY()
};

UCLASS(Abstract, BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiResponseBody : public UObject
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンスコード */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|WebApi")
	int32 ResponseCode;

private:
	/** キャッシュしたUObjectプロパティ名リスト */
	static TArray<FString> CachedUObjectPropertyNames;

public:
	/**
	 * レスポンスインスタンスを作成
	 * @param ResponseClass レスポンスクラス
	 * @return レスポンスインスタンス
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi", meta=(DisplayName="Create Web Api Response", WorldContext="WorldContext", DeterminesOutputType="ResponseClass"))
	static UWebApiResponseBody* Create(TSubclassOf<UWebApiResponseBody> ResponseClass);

	/**
	 * レスポンスインスタンスを作成
	 * @return レスポンスインスタンス
	 */
	template <typename ResponseClassType>
	static ResponseClassType* Create()
	{
		return Cast<ResponseClassType>(Create(ResponseClassType::StaticClass()));
	}

	/**
	 * プロパティ名リストを作成
	 * @param ResponseClass レスポンスクラス
	 * @return プロパティ名リスト
	 */
	static TArray<FString> GetPropertyNames(TSubclassOf<UWebApiResponseBody> ResponseClass);
};

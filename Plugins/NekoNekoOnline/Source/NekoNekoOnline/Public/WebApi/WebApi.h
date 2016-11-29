#pragma once

#include "Http.h"
#include "WebApi.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApi : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestStart, class UWebApi*, Api, class UWebApiRequestBody*, Request);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRequestProgress, class UWebApi*, Api, int32, SentBytes, int32, ReceivedBytes);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestSuccess, class UWebApi*, Api, class UWebApiResponseBody*, Response);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestFailure, class UWebApi*, Api, class UWebApiResponseBody*, Response);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRequestCompleted, class UWebApi*, Api, class UWebApiResponseBody*, Response);

public:
	/** URL構成要素。これらを連結したものがリクエストURLとなる */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	TArray<FString> UrlElements;

	/** 成功判定とするレスポンスコードリスト */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	TArray<int32> SuccessResponseCodes;

	/** レスポンスクラス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	TSubclassOf<UWebApiResponseBody> ResponseClass;

	/** リクエストフィルターリスト */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	TArray<UObject*> RequestFilters;

	/** レスポンスフィルターリスト */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	TArray<UObject*> ResponseFilters;

	/** リクエスト開始時コールバック */
	UPROPERTY(BlueprintAssignable, Category="NekoNeko|Online|WebApi")
	FOnRequestStart OnRequestStart;

	/** リクエスト進行時コールバック */
	UPROPERTY(BlueprintAssignable, Category="NekoNeko|Online|WebApi")
	FOnRequestProgress OnRequestProgress;

	/** リクエスト成功時コールバック */
	UPROPERTY(BlueprintAssignable, Category="NekoNeko|Online|WebApi")
	FOnRequestSuccess OnRequestSuccess;

	/** リクエスト失敗時コールバック */
	UPROPERTY(BlueprintAssignable, Category="NekoNeko|Online|WebApi")
	FOnRequestFailure OnRequestFailure;

	/** リクエスト完了時コールバック */
	UPROPERTY(BlueprintAssignable, Category="NekoNeko|Online|WebApi")
	FOnRequestCompleted OnRequestCompleted;

private:
	/** リクエスト中フラグ */
	bool bIsProcessingRequest;

	/** 処理中リクエスト */
	FHttpRequestPtr ProcessingRequest;

	/** ダミーリクエストフラグ */
	bool IsDummyRequest;

	/** クリティカルセクション */
	mutable FCriticalSection SyncObject;

public:
	UWebApi(const FObjectInitializer& ObjectInitializer);

	// UObject interface
	virtual void PostInitProperties() override;

	/**
	 * APIインスタンスを作成
	 * @param ApiClass APIクラス
	 * @return APIインスタンス
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi", meta=(DisplayName="Create Web Api", WorldContext="WorldContext", DeterminesOutputType="ApiClass"))
	static UWebApi* Create(UObject* WorldContext, TSubclassOf<UWebApi> ApiClass);

	/**
	 * APIインスタンスを作成
	 * @return APIインスタンス
	 */
	template <typename ApiClassType>
	static ApiClassType* Create(UObject* WorldContext)
	{
		Create(WorldContext, ApiClassType::StaticClass());
	}

	/**
	 * URL生成
	 * @return URL
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	FString GenerateUrl();

	/**
	 * PostInitProperties時のイベント
	 */
	UFUNCTION(BlueprintNativeEvent, Category="NekoNeko|Online|WebApi")
	void OnPostInitProperties();

	/**
	 * リクエスト開始
	 * @param Request リクエスト本体
	 * @return 正常にリクエストできたらtrue
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	bool ProcessRequest(UWebApiRequestBody* Request);

	/**
	 * リクエストキャンセル
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void CancelRequest();

	/**
	 * リクエスト中判定
	 * @return リクエスト処理中ならtrue
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	bool IsProcessingRequest() const;

private:
	/**
	 * リクエスト経過イベント
	 * @param Request リクエストデータ
	 * @param SentBytes 送信済みバイト数
	 * @param ReceivedBytes 受信済みバイト数
	 */
	void OnRequestProgressInternal(FHttpRequestPtr Request, int32 SentBytes, int32 ReceivedBytes);

	/**
	 * リクエスト完了イベント
	 * @param Request リクエストデータ
	 * @param Response レスポンスデータ
	 * @param Success 成功フラグ
	 */
	void OnRequestCompletedInternal(FHttpRequestPtr Request, FHttpResponsePtr Response, bool Success);
};

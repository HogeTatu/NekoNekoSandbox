#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArrayFunctionLibrary.generated.h"

/** 配列関連ライブラリ */
UCLASS()
class NEKONEKOGENERAL_API UArrayFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * uint8配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddByteValueToArray(const TArray<uint8>& Array, uint8 Value);
	static void GenericAddByteValueToArray(void* Array, const UArrayProperty* ArrayProp, uint8 Value);

	DECLARE_FUNCTION(execAddByteValueToArray)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UByteProperty, Value);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddByteValueToArray(ArrayAddr, ArrayProperty, Value);
		P_NATIVE_END;
	}

	/**
	 * Clamp付きでuint8配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 * @param ClampMin Clamp下限
	 * @param ClampMax Clamp上限
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddByteValueToArrayWithClamp(const TArray<uint8>& Array, uint8 Value, uint8 ClampMin, uint8 ClampMax);
	static void GenericAddByteValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, uint8 Value, uint8 ClampMin, uint8 ClampMax);

	DECLARE_FUNCTION(execAddByteValueToArrayWithClamp)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UByteProperty, Value);
		P_GET_PROPERTY(UByteProperty, ClampMin);
		P_GET_PROPERTY(UByteProperty, ClampMax);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddByteValueToArrayWithClamp(ArrayAddr, ArrayProperty, Value, ClampMin, ClampMax);
		P_NATIVE_END;
	}

	/**
	 * int32配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddIntValueToArray(const TArray<int32>& Array, int32 Value);
	static void GenericAddIntValueToArray(void* Array, const UArrayProperty* ArrayProp, int32 Value);

	DECLARE_FUNCTION(execAddIntValueToArray)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UIntProperty, Value);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddIntValueToArray(ArrayAddr, ArrayProperty, Value);
		P_NATIVE_END;
	}

	/**
	 * Clamp付きでint32配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 * @param ClampMin Clamp下限
	 * @param ClampMax Clamp上限
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddIntValueToArrayWithClamp(const TArray<int32>& Array, int32 Value, int32 ClampMin, int32 ClampMax);
	static void GenericAddIntValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, int32 Value, int32 ClampMin, int32 ClampMax);

	DECLARE_FUNCTION(execAddIntValueToArrayWithClamp)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UIntProperty, Value);
		P_GET_PROPERTY(UIntProperty, ClampMin);
		P_GET_PROPERTY(UIntProperty, ClampMax);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddIntValueToArrayWithClamp(ArrayAddr, ArrayProperty, Value, ClampMin, ClampMax);
		P_NATIVE_END;
	}

	/**
	 * float配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddFloatValueToArray(const TArray<float>& Array, float Value);
	static void GenericAddFloatValueToArray(void* Array, const UArrayProperty* ArrayProp, float Value);

	DECLARE_FUNCTION(execAddFloatValueToArray)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UFloatProperty, Value);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddFloatValueToArray(ArrayAddr, ArrayProperty, Value);
		P_NATIVE_END;
	}

	/**
	 * Clamp付きでfloat配列全体に加算
	 * @param Array 対象の配列
	 * @param Value 加算値
	 * @param ClampMin Clamp下限
	 * @param ClampMax Clamp上限
	 */
	UFUNCTION(BlueprintCallable, CustomThunk, Category="NekoNeko|General")
	static void AddFloatValueToArrayWithClamp(const TArray<float>& Array, float Value, float ClampMin, float ClampMax);
	static void GenericAddFloatValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, float Value, float ClampMin, float ClampMax);

	DECLARE_FUNCTION(execAddFloatValueToArrayWithClamp)
	{
		Stack.MostRecentProperty = nullptr;
		Stack.StepCompiledIn<UArrayProperty>(NULL);
		void* ArrayAddr = Stack.MostRecentPropertyAddress;
		UArrayProperty* ArrayProperty = Cast<UArrayProperty>(Stack.MostRecentProperty);
		if (!ArrayProperty)
		{
			Stack.bArrayContextFailed = true;
			return;
		}

		P_GET_PROPERTY(UFloatProperty, Value);
		P_GET_PROPERTY(UFloatProperty, ClampMin);
		P_GET_PROPERTY(UFloatProperty, ClampMax);

		P_FINISH;
		P_NATIVE_BEGIN;
		GenericAddFloatValueToArrayWithClamp(ArrayAddr, ArrayProperty, Value, ClampMin, ClampMax);
		P_NATIVE_END;
	}
};

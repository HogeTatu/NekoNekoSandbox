#include "NekoNekoGeneralPrivatePCH.h"
#include "ArrayFunctionLibrary.h"

UArrayFunctionLibrary::UArrayFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UArrayFunctionLibrary::GenericAddByteValueToArray(void* Array, const UArrayProperty* ArrayProp, uint8 Value)
{
	if (Array)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			uint8* Ptr = (uint8*)ArrayHelper.GetRawPtr(ArrayIndex);
			*Ptr += Value;
		}
	}
}

void UArrayFunctionLibrary::GenericAddByteValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, uint8 Value, uint8 ClampMin, uint8 ClampMax)
{
	if (Array)
	{
		int32 ValueInt = static_cast<int32>(Value);
		int32 ClampMinInt = static_cast<int32>(ClampMin);
		int32 ClampMaxInt = static_cast<int32>(ClampMax);

		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			uint8* Ptr = (uint8*)ArrayHelper.GetRawPtr(ArrayIndex);
			int32 Temp = FMath::Clamp(static_cast<int32>(*Ptr) + ValueInt, ClampMinInt, ClampMaxInt);
			*Ptr = static_cast<uint8>(Temp);
		}
	}
}

void UArrayFunctionLibrary::GenericAddIntValueToArray(void* Array, const UArrayProperty* ArrayProp, int32 Value)
{
	if (Array)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			int32* Ptr = (int32*)ArrayHelper.GetRawPtr(ArrayIndex);
			*Ptr += Value;
		}
	}
}

void UArrayFunctionLibrary::GenericAddIntValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, int32 Value, int32 ClampMin, int32 ClampMax)
{
	if (Array)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			int32* Ptr = (int32*)ArrayHelper.GetRawPtr(ArrayIndex);
			*Ptr = FMath::Clamp(*Ptr + Value, ClampMin, ClampMax);
		}
	}
}

void UArrayFunctionLibrary::GenericAddFloatValueToArray(void* Array, const UArrayProperty* ArrayProp, float Value)
{
	if (Array)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			float* Ptr = (float*)ArrayHelper.GetRawPtr(ArrayIndex);
			*Ptr += Value;
		}
	}
}

void UArrayFunctionLibrary::GenericAddFloatValueToArrayWithClamp(void* Array, const UArrayProperty* ArrayProp, float Value, float ClampMin, float ClampMax)
{
	if (Array)
	{
		FScriptArrayHelper ArrayHelper(ArrayProp, Array);
		for (int32 ArrayIndex = 0; ArrayIndex < ArrayHelper.Num(); ++ArrayIndex)
		{
			float* Ptr = (float*)ArrayHelper.GetRawPtr(ArrayIndex);
			*Ptr = FMath::Clamp(*Ptr + Value, ClampMin, ClampMax);
		}
	}
}

#pragma once

class UAnimSequenceBase;

class AnimUtils
{
public:
	template <typename T> 
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		return nullptr;
	}
};
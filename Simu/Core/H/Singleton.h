#pragma once

#include <CoreAPI.h>

namespace core {
	template <typename Type>
	class CORE_EXPORT Singleton {
	public:
		virtual ~Singleton() {}

		static Type& Instance()
		{
			static Type instance;
			instance.Init();
			return instance;
		}

	protected:
		Singleton() = default;
		Singleton(const Singleton&) = default;
		Singleton(Singleton&&) = default;

		virtual void Init() {}
	};
}



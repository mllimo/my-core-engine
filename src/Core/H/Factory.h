#pragma once

#include <unordered_map>
#include <functional>
#include <stdexcept>

#include <CoreAPI.h>

namespace core {
	template <typename KeyType, typename BaseValueType>
	class CORE_EXPORT Factory {
	public:
		using Key = KeyType;
		using BaseValue = BaseValueType;

		template <typename ExtendedType = BaseValueType>
		void Register(const KeyType& key)
		{
			auto builder = []() { return new ExtendedType(); };
			_map.emplace(key, std::move(builder));
		}

		BaseValueType* Get(const KeyType& key) const
		{
			auto it = _map.find(key);
			if (it == _map.end()) return nullptr;
			return it->second();
		}

	private:
		std::unordered_map<KeyType, std::function<BaseValueType* (void)>> _map;
	};

	template <typename SingletonFactory, typename ValueType>
	class CORE_EXPORT AutoRegisterFactory {
	public:
		using Key = typename SingletonFactory::Key;

		AutoRegisterFactory(const Key& key)
		{
			SingletonFactory::Instance().Register<ValueType>(key);
		}
	};
}

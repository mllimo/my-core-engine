#pragma once

#include <exception>
#include <stdexcept>

#include <CoreAPI.h>

namespace core {
	class CORE_EXPORT CollisionEngineException : public std::runtime_error { public: using std::runtime_error::runtime_error; };
	class CORE_EXPORT ColliderException : public std::runtime_error { public: using std::runtime_error::runtime_error; };
	class CORE_EXPORT GeometryException : public std::runtime_error { public: using std::runtime_error::runtime_error; };
	class CORE_EXPORT MathException : public std::runtime_error { public: using std::runtime_error::runtime_error; };
	class CORE_EXPORT RenderableException : public std::runtime_error { public: using std::runtime_error::runtime_error; };
}

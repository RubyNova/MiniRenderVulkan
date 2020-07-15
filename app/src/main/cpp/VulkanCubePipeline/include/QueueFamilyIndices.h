#ifndef QUEUEFAMILYINDICES_H
#define QUEUEFAMILYINDICES_H

#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	inline bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

#endif //!QUEUEFAMILYINDICES_H
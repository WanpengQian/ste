// StE
// © Shlomi Steinberg, 2015-2016

#pragma once

#include "buffer_object.hpp"
#include "buffer_usage.hpp"

namespace StE {
namespace Core {

struct IndirectDispatchCommand {
	std::uint32_t num_groups_x;
	std::uint32_t num_groups_y;
	std::uint32_t num_groups_z;
};

class IndirectDispatchBufferObjectGeneric {
public:
	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual ~IndirectDispatchBufferObjectGeneric() noexcept {}
};

template <BufferUsage::buffer_usage U = BufferUsage::BufferUsageNone>
class IndirectDispatchBufferObject : public buffer_object<IndirectDispatchCommand, U>, public IndirectDispatchBufferObjectGeneric {
private:
	using Base = buffer_object<IndirectDispatchCommand, U>;

	ALLOW_BUFFER_OBJECT_CASTS;

public:
	IndirectDispatchBufferObject(IndirectDispatchBufferObject &&m) = default;
	IndirectDispatchBufferObject& operator=(IndirectDispatchBufferObject &&m) = default;

	using Base::Base;

	void bind() const final override { Binder::bind(get_resource_id(), GL_DISPATCH_INDIRECT_BUFFER); };
	void unbind() const final override { Binder::unbind(GL_DISPATCH_INDIRECT_BUFFER); };
	void bind_range(const LayoutLocationType &sampler, int offset, std::size_t size) const { Base::bind_range(sampler, GL_DISPATCH_INDIRECT_BUFFER, offset, size); }

	core_resource_type resource_type() const override { return core_resource_type::IndirectDispatchBufferObject; }
};

}
}

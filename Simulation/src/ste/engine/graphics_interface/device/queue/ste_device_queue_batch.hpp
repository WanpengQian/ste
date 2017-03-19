//	StE
// � Shlomi Steinberg 2015-2017

#pragma once

#include <stdafx.hpp>
#include <shared_fence.hpp>
#include <ste_device_queue_command_buffer.hpp>

#include <ste_device_queue_command_pool.hpp>
#include <shared_fence.hpp>

#include <memory>
#include <type_traits>
#include <function_traits.hpp>

namespace StE {
namespace GL {

namespace _detail {

template <typename Fence, typename Pool>
class ste_device_queue_batch_impl {
	friend class ste_device_queue;

public:
	using pool_t = Pool;
	using fence_t = Fence;

public:
	using fence_ptr_strong_t = std::shared_ptr<fence_t>;
	using fence_ptr_weak_t = std::weak_ptr<fence_t>;

private:
	using shared_fence_t = shared_fence<void>;

private:
	pool_t pool;
	std::uint32_t queue_index;

protected:
	fence_ptr_strong_t fence_strong;
	std::vector<ste_device_queue_command_buffer> command_buffers;

	auto begin() const { return std::begin(command_buffers); }
	auto end() const { return std::end(command_buffers); }

public:
	ste_device_queue_batch_impl(std::uint32_t queue_index,
								pool_t &&pool,
								const fence_ptr_strong_t &f)
		: pool(std::move(pool)),
		queue_index(queue_index),
		fence_strong(f)
	{}
	virtual ~ste_device_queue_batch_impl() noexcept {}

	ste_device_queue_batch_impl(ste_device_queue_batch_impl&&) = default;
	ste_device_queue_batch_impl &operator=(ste_device_queue_batch_impl&&) = default;

	auto& acquire_command_buffer() {
		command_buffers.emplace_back(pool->get_pool(), vk_command_buffer_type::primary);
		return command_buffers.back();
	}

	const auto& get_fence_ptr() const { return fence_strong; }

	auto& get_fence() const {
		return **fence_strong;
	}

	bool is_batch_complete() const {
		const auto& f = get_fence();
		return f.is_signaled();
	}
};

}

using ste_device_queue_batch = _detail::ste_device_queue_batch_impl<
	ste_resource_pool<shared_fence<void>>::resource_t,
	ste_resource_pool<ste_device_queue_command_pool>::resource_t
>;

}
}

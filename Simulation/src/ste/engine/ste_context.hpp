//	StE
// � Shlomi Steinberg 2015-2016

#pragma once

#include <stdafx.hpp>

#include <ste_gl_context.hpp>
#include <ste_engine.hpp>

namespace StE {

template <typename Types>
class ste_context_impl {
public:
	using context_types = Types;

	using gl_device_t = ste_engine::gl_device_t;
	using gl_context_t = ste_engine::gl_context_t;

private:
	const ste_engine_impl<Types> &engine_reference;
	const gl_context_t &gl_context;
	gl_device_t &gl_device;
	typename context_types::gl_device_memory_allocator engine_device_memory_allocator;

public:
	ste_context_impl(const ste_engine_impl<Types> &engine,
					 const gl_context_t &gl_ctx,
					 gl_device_t &device)
		: engine_reference(engine),
		gl_context(gl_ctx),
		gl_device(device),
		engine_device_memory_allocator(device.device())
	{}
	~ste_context_impl() noexcept {}

	ste_context_impl(ste_context_impl &&) = default;
	ste_context_impl(const ste_context_impl &) = delete;
	ste_context_impl &operator=(ste_context_impl &&) = default;
	ste_context_impl &operator=(const ste_context_impl &) = delete;

	auto &engine() const { return engine_reference; }
	auto &gl() const { return gl_context; }
	auto &presentation_device() const { return gl_device; }
	auto &device_memory_allocator() const { return engine_device_memory_allocator; }
};

using ste_context = ste_context_impl<
	ste_engine_types
>;

}

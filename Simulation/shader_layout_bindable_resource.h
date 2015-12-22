// StE
// � Shlomi Steinberg, 2015

#pragma once

#include "resource.h"
#include "layout_binding.h"

namespace StE {
namespace LLR {

template <typename BinderType>
class shader_layout_bindable_resource {
public:
	using LayoutLocationType = layout_binding<BinderType>;
	using EmptyLayoutLocationType = layout_binding_none<BinderType>;

protected:
	~shader_layout_bindable_resource() noexcept {}

public:
	virtual void bind(const LayoutLocationType &) const = 0;
	virtual void unbind(const LayoutLocationType &) const = 0;
};

}
}

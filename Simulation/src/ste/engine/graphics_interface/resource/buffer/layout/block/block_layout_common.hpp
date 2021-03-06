//	StE
// � Shlomi Steinberg 2015-2017

#pragma once

#include <stdafx.hpp>
#include <ste_type_traits.hpp>
#include <type_traits>

namespace ste {
namespace gl {

namespace _detail {

template <typename T>
decltype(T::block_base_alignment, std::true_type{}) _block_layout_is_block(int);
template <typename T>
std::false_type _block_layout_is_block(...) {}
template <typename T>
using _block_layout_is_block_tester = decltype(_block_layout_is_block<T>(0));
template <typename T>
struct block_layout_is_block {
	static constexpr bool value = _block_layout_is_block_tester<T>{};
};

template <typename T>
struct block_layout_type_base_alignment_impl {
	static constexpr bool is_block = block_layout_is_block<T>::value;
	static constexpr bool has_overload = is_scalar<T>::value || std::is_array_v<T> || is_vector<T>::value || is_matrix<T>::value || is_block;

	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<is_scalar<S>::value>* = nullptr) {
		static constexpr auto value = byte_t(sizeof(S));
		return value;
	}
	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<std::is_array_v<S>>* = nullptr) {
		using array_type = std::remove_all_extents_t<S>;
		return block_layout_type_base_alignment_impl<array_type>::template alignment<>();
	}
	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<is_vector<S>::value>* = nullptr) {
		static constexpr std::size_t effective_elements = type_elements_count<S>::value == 2 ? 2 : 4;
		static constexpr auto value = effective_elements * byte_t(sizeof(remove_extents<S>::type));
		return value;
	}
	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<is_matrix<S>::value>* = nullptr) {
		using row_t = std::remove_reference_t<decltype(std::declval<S>()[0])>;
		static constexpr auto value = block_layout_type_base_alignment_impl<row_t>::template alignment<>();
		return value;
	}
	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<block_layout_type_base_alignment_impl<S>::is_block>* = nullptr) {
		return T::sizeof_block_element;
	}
	template <typename S = T>
	static constexpr byte_t alignment(std::enable_if_t<!block_layout_type_base_alignment_impl<S>::has_overload>* = nullptr) {
		static_assert(false, "T is neither a scalar, vector, matrix, a c-style array of those, nor a block_layout type");
		return 0_B;
	}
};

template <int N, int Size, typename Src, typename Dst>
struct block_layout_initialize_block_layout_with_tuple {
	void operator()(Dst &dst, Src &&src) {
		dst.template get<N>() = std::move(std::get<N>(src));
		block_layout_initialize_block_layout_with_tuple<N + 1, Size, Src, Dst>()(dst, std::move(src));
	}
};
template <int Size, typename Src, typename Dst>
struct block_layout_initialize_block_layout_with_tuple<Size, Size, Src, Dst> {
	void operator()(Dst &dst, Src &&src) {}
};

}

template <typename T>
struct block_layout_type_base_alignment {
	static constexpr byte_t value = _detail::block_layout_type_base_alignment_impl<T>::template alignment<>();
};
template <typename T>
static constexpr auto block_layout_type_base_alignment_v = block_layout_type_base_alignment<T>::value;

template <typename T, typename... Ts>
struct block_layout_struct_base_alignment {
	static constexpr byte_t _align_T = _detail::block_layout_type_base_alignment_impl<T>::template alignment<>();
	static constexpr byte_t value = std::max(_align_T, block_layout_struct_base_alignment<Ts...>::value);
};
template <typename T>
struct block_layout_struct_base_alignment<T> {
	static constexpr byte_t value = _detail::block_layout_type_base_alignment_impl<T>::template alignment<>();
};
template <typename T>
static constexpr auto block_layout_struct_base_alignment_v = block_layout_struct_base_alignment<T>::value;

template <typename T>
struct is_block_layout {
	static constexpr bool value = _detail::block_layout_type_base_alignment_impl<T>::is_block;
};
template <typename T>
static constexpr auto is_block_layout_v = is_block_layout<T>::value;

template <std::size_t offset, typename T, typename T_next>
struct block_layout_member_padding {
	static constexpr auto align0 = static_cast<std::size_t>(block_layout_type_base_alignment<T>::value);
	static constexpr auto align1 = static_cast<std::size_t>(block_layout_type_base_alignment<T_next>::value);
	static_assert((offset % align0) == 0, "T does not align on offset!");

	static constexpr byte_t end = byte_t(offset) + byte_t(sizeof(T));

	static constexpr byte_t value = (byte_t(align1) - (end % align1)) % align1;

	static_assert(((offset + sizeof(T) + static_cast<std::size_t>(value)) % align1) == 0, "...");
};

}
}

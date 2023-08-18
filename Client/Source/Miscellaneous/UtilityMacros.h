#pragma once

#define DEFINE_FLAG_OPERATORS(type) constexpr inline type operator |(const type lhs, const type rhs) { \
										return (type)(uint32_t(lhs) | uint32_t(rhs)); \
						   		    } \
									constexpr inline bool operator &(const type lhs, const type rhs) { \
										return uint32_t(lhs) & uint32_t(rhs); \
						   		    }
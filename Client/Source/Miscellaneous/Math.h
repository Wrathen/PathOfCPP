#pragma once

namespace {
	template<typename T>
	T Max(T element1, T element2, T element3) {
		return (element1 > element2 && element1 > element3 ? element1 :
				element2 > element3 ? element2 : element3);
	}
}
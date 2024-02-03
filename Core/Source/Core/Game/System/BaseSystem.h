#pragma once

namespace Core {
	struct IBaseSystem {
		// Events
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void LateUpdate() = 0;
		virtual void Destroy() = 0;
	};
}
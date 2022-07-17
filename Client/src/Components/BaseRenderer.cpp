#include "BaseRenderer.h"
#include "../Managers/RenderManager.h"

void BaseRenderer::Delete() { MainRenderer.RemoveRenderer(this); }
std::string BaseRenderer::ToString() {
    if (this == nullptr) return "This renderer has already been deleted. What are you doing?!";
    return "Renderer with GUID: " + std::to_string(guid);
}
BaseRenderer::BaseRenderer() {
    MainRenderer.AddRenderer(this);
}
#pragma once
#include <iostream>


#include "Node.hpp"
#include "UI.hpp"
#include "Scene.hpp"
#include "NodePreview.hpp"


namespace ScenePreview {
	struct ScenePreview {
		Node::Node* currentViewingNode = nullptr;
	};

	inline void Render(ScenePreview* preview, Scene::Scene* scene) {
	}


}

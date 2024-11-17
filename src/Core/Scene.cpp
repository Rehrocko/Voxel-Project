#include "Scene.h"

void Scene::Init() {
	// Creates a new camera with all default values
	auto mainCamera = Camera();
	_cameras.push_back(mainCamera);
}

void Scene::Update() {
	// Go through all update loops of things in the scene
	for (Camera& camera : _cameras) {
		camera.Update();
	}
}
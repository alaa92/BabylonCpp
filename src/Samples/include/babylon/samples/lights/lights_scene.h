#ifndef BABYLON_SAMPLES_LIGHTS_LIGHTS_SCENE_H
#define BABYLON_SAMPLES_LIGHTS_LIGHTS_SCENE_H

#include <vector>
#include <babylon/interfaces/irenderable_scene.h>

namespace BABYLON {

class Mesh;
class PointLight;
using MeshPtr       = std::shared_ptr<Mesh>;
using PointLightPtr = std::shared_ptr<PointLight>;

namespace Samples {

/**
 * @brief Lights Scene. Example demonstrating how to add lights to a scene.
 * @see https://www.babylonjs-playground.com/#AQRDKW#0
 * @see https://doc.babylonjs.com/babylon101/lights
 */
class LightsScene : public IRenderableScene {

public:
  LightsScene(ICanvas* iCanvas);
  ~LightsScene() override;

  const char* getName() override;
  void initializeScene(ICanvas* canvas, Scene* scene) override;

private:
  std::vector<PointLightPtr> _lights;
  std::vector<MeshPtr> _lightSpheres;
  float _alpha;

}; // end of class LightsScene

} // end of namespace Samples
} // end of namespace BABYLON

#endif // end of BABYLON_SAMPLES_LIGHTS_LIGHTS_SCENE_H

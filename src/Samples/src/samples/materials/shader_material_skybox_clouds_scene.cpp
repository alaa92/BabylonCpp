#include <babylon/samples/materials/shader_material_skybox_clouds_scene.h>

#include <babylon/cameras/free_camera.h>
#include <babylon/engine/engine.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/effect_shaders_store.h>
#include <babylon/materials/shader_material.h>
#include <babylon/mesh/mesh.h>
#include <babylon/mesh/mesh_builder.h>
#include <babylon/mesh/vertex_data_options.h>

namespace BABYLON {
namespace Samples {

ShaderMaterialSkyboxCloudsScene::ShaderMaterialSkyboxCloudsScene(
  ICanvas* iCanvas)
    : IRenderableScene(iCanvas), _time{0.f}, _shaderMaterial{nullptr}
{
  // Vertex shader
  EffectShadersStore::Shaders["customVertexShader"] = customVertexShader;

  // Fragment shader
  EffectShadersStore::Shaders["customFragmentShader"] = customFragmentShader;
}

ShaderMaterialSkyboxCloudsScene::~ShaderMaterialSkyboxCloudsScene()
{
}

const char* ShaderMaterialSkyboxCloudsScene::getName()
{
  return "Shader Material Skybox Clouds Scene";
}

void ShaderMaterialSkyboxCloudsScene::initializeScene(ICanvas* canvas,
                                                      Scene* scene)
{
  // Create a FreeCamera, and set its position to (x:0, y:0, z:-10)
  auto camera = FreeCamera::New("camera1", Vector3(0, 0, -8), scene);

  // Target the camera to scene origin
  camera->setTarget(Vector3::Zero());

  // Attach the camera to the canvas
  camera->attachControl(canvas, true);

  // Create a basic light, aiming 0,1,0 - meaning, to the sky
  HemisphericLight::New("light1", Vector3(0, 1, 0), scene);

  // Create a built-in "box" shape
  const float ratio = static_cast<float>(getEngine()->getRenderWidth())
                      / static_cast<float>(getEngine()->getRenderHeight());
  BoxOptions options(5.f);
  options.sideOrientation = Mesh::DEFAULTSIDE;
  options.updatable       = false;
  options.width           = options.width * ratio;
  auto skybox             = MeshBuilder::CreateBox("skybox", options, scene);

  // Create shader material
  ShaderMaterialOptions shaderMaterialOptions;
  shaderMaterialOptions.attributes = {"position", "uv"};
  shaderMaterialOptions.uniforms   = {"worldViewProjection", "time"};
  _shaderMaterial
    = ShaderMaterial::New("boxShader", scene, "custom", shaderMaterialOptions);

  // box + sky = skybox !
  skybox->setMaterial(_shaderMaterial);

  // Animation
  scene->onAfterCameraRenderObservable.add([this](Camera*, EventState&) {
    _shaderMaterial->setFloat("time", _time);
    _time += 0.01f;
  });
}

} // end of namespace Samples
} // end of namespace BABYLON

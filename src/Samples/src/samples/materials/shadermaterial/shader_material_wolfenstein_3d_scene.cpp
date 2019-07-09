#include <babylon/samples/materials/shadermaterial/shader_material_wolfenstein_3d_scene.h>

#include <babylon/cameras/free_camera.h>
#include <babylon/engines/engine.h>
#include <babylon/engines/scene.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/effect.h>
#include <babylon/materials/effect_shaders_store.h>
#include <babylon/materials/shader_material.h>
#include <babylon/meshes/builders/mesh_builder_options.h>
#include <babylon/meshes/mesh.h>
#include <babylon/meshes/mesh_builder.h>
#include <babylon/meshes/vertex_data_options.h>

namespace BABYLON {
namespace Samples {

ShaderMaterialWolfenstein3DScene::ShaderMaterialWolfenstein3DScene(
  ICanvas* iCanvas)
    : IRenderableScene(iCanvas), _time{0.f}, _shaderMaterial{nullptr}
{
  // Vertex shader
  Effect::ShadersStore()["customVertexShader"] = customVertexShader;

  // Fragment shader
  Effect::ShadersStore()["customFragmentShader"] = customFragmentShader;
}

ShaderMaterialWolfenstein3DScene::~ShaderMaterialWolfenstein3DScene()
{
}

const char* ShaderMaterialWolfenstein3DScene::getName()
{
  return "Shader Material Wolfenstein 3D Scene";
}

void ShaderMaterialWolfenstein3DScene::initializeScene(ICanvas* canvas,
                                                       Scene* scene)
{
  // Create a FreeCamera, and set its position to (x:0, y:0, z:-8)
  auto camera = FreeCamera::New("camera1", Vector3(0.f, 0.f, -8.f), scene);

  // Target the camera to scene origin
  camera->setTarget(Vector3::Zero());

  // Attach the camera to the canvas
  camera->attachControl(canvas, true);

  // Create a basic light, aiming 0,1,0 - meaning, to the sky
  HemisphericLight::New("light1", Vector3(0.f, 1.f, 0.f), scene);

  // Create a built-in "box" shape
  const float ratio = static_cast<float>(getEngine()->getRenderWidth())
                      / static_cast<float>(getEngine()->getRenderHeight());
  BoxOptions options;
  options.size            = 5.f;
  options.sideOrientation = Mesh::DEFAULTSIDE;
  options.updatable       = false;
  options.width           = *options.size * ratio;
  auto skybox             = MeshBuilder::CreateBox("skybox", options, scene);

  // Create shader material
  IShaderMaterialOptions shaderMaterialOptions;
  shaderMaterialOptions.attributes = {"position", "uv"};
  shaderMaterialOptions.uniforms
    = {"worldViewProjection", "iTime", "aspectRatio"};
  _shaderMaterial
    = ShaderMaterial::New("boxShader", scene, "custom", shaderMaterialOptions);

  // box + sky = skybox !
  skybox->material = _shaderMaterial;

  // Animation
  scene->onAfterCameraRenderObservable.add([this](Camera*, EventState&) {
    const float aspectRatio
      = static_cast<float>(getEngine()->getRenderWidth())
        / static_cast<float>(getEngine()->getRenderHeight());
    _shaderMaterial->setFloat("aspectRatio", aspectRatio);
    _shaderMaterial->setFloat("iTime", _time);
    _time += 0.01f * getScene()->getAnimationRatio();
  });
}

} // end of namespace Samples
} // end of namespace BABYLON

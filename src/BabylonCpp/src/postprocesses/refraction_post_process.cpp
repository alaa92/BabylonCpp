#include <babylon/postprocesses/refraction_post_process.h>

#include <babylon/cameras/camera.h>
#include <babylon/materials/effect.h>
#include <babylon/materials/textures/texture.h>

namespace BABYLON {

RefractionPostProcess::RefractionPostProcess(const std::string& iName,
                                             const std::string& iRefractionTextureUrl,
                                             const Color3& iColor, float iDepth, int iColorLevel,
                                             float ratio, const CameraPtr& camera,
                                             const std::optional<unsigned int>& samplingMode,
                                             Engine* engine, bool reusable)
    : PostProcess{iName,
                  "refraction",
                  {"baseColor", "depth", "colorLevel"},
                  {"refractionSampler"},
                  ratio,
                  camera,
                  samplingMode,
                  engine,
                  reusable}
    , refractionTexture{this, &RefractionPostProcess::get_refractionTexture,
                        &RefractionPostProcess::set_refractionTexture}
    , _refTexture{nullptr}
    , _ownRefractionTexture{true}
{
  color                = iColor;
  depth                = iDepth;
  colorLevel           = iColorLevel;
  refractionTextureUrl = iRefractionTextureUrl;

  onActivateObservable.add([&](Camera* cam, EventState&) {
    _refTexture = _refTexture ? _refTexture : Texture::New(refractionTextureUrl, cam->getScene());
  });

  onApplyObservable.add([&](Effect* effect, EventState&) {
    effect->setColor3("baseColor", color);
    effect->setFloat("depth", depth);
    effect->setFloat("colorLevel", static_cast<float>(colorLevel));
    effect->setTexture("refractionSampler", _refTexture);
  });
}

RefractionPostProcess::~RefractionPostProcess() = default;

std::string RefractionPostProcess::getClassName() const
{
  return "RefractionPostProcess";
}

TexturePtr& RefractionPostProcess::get_refractionTexture()
{
  return _refTexture;
}

void RefractionPostProcess::set_refractionTexture(const TexturePtr& value)
{
  if (_refTexture && _ownRefractionTexture) {
    _refTexture->dispose();
  }

  _refTexture           = value;
  _ownRefractionTexture = false;
}

void RefractionPostProcess::dispose(Camera* camera)
{
  if (_refTexture && _ownRefractionTexture) {
    _refTexture->dispose();
    _refTexture = nullptr;
  }

  PostProcess::dispose(camera);
}

RefractionPostProcessPtr RefractionPostProcess::_Parse(const json& /*parsedPostProcess*/,
                                                       const CameraPtr& /*targetCamera*/,
                                                       Scene* /*scene*/,
                                                       const std::string& /*rootUrl*/)
{
  return nullptr;
}

} // end of namespace BABYLON

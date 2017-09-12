#include <babylon/materials/textures/mirror_texture.h>

#include <babylon/babylon_stl_util.h>
#include <babylon/cameras/camera.h>
#include <babylon/core/json.h>
#include <babylon/core/structs.h>
#include <babylon/engine/engine.h>
#include <babylon/engine/scene.h>
#include <babylon/postprocess/blur_post_process.h>

namespace BABYLON {

MirrorTexture::MirrorTexture(const std::string& iName, const ISize& size,
                             Scene* scene, bool generateMipMaps,
                             unsigned int type, unsigned int samplingMode,
                             bool generateDepthBuffer)

    : RenderTargetTexture{iName, size,  scene,        generateMipMaps,    true,
                          type,  false, samplingMode, generateDepthBuffer}
    , mirrorPlane{Plane(0.f, 1.f, 0.f, 1.f)}
    , _transformMatrix{Matrix::Zero()}
    , _mirrorMatrix{Matrix::Zero()}
    , _savedViewMatrix{Matrix::Zero()}
    , _blurX{nullptr}
    , _blurY{nullptr}
    , _blurKernelX{0.f}
    , _blurKernelY{0.f}
    , _blurRatio{1.f}

{
  onBeforeRender = [this]() {
    auto scene = getScene();
    Matrix::ReflectionToRef(mirrorPlane, _mirrorMatrix);
    _savedViewMatrix = scene->getViewMatrix();
    _mirrorMatrix.multiplyToRef(_savedViewMatrix, _transformMatrix);
    scene->setTransformMatrix(_transformMatrix, scene->getProjectionMatrix());
    scene->setClipPlane(mirrorPlane);
    scene->getEngine()->cullBackFaces = false;
    scene->setMirroredCameraPosition(Vector3::TransformCoordinates(
      scene->activeCamera->globalPosition(), _mirrorMatrix));
  };

  onAfterRender = [this]() {
    auto scene = getScene();
    scene->setTransformMatrix(_savedViewMatrix, scene->getProjectionMatrix());
    scene->getEngine()->cullBackFaces = true;
    scene->_mirroredCameraPosition.reset(nullptr);
    scene->resetClipPlane();
  };
}

MirrorTexture::~MirrorTexture()
{
}

void MirrorTexture::setBlurRatio(float value)
{
  if (stl_util::almost_equal(_blurRatio, value)) {
    return;
  }

  _blurRatio = value;
  _preparePostProcesses();
}

float MirrorTexture::blurRatio() const
{
  return _blurRatio;
}

void MirrorTexture::setBlurKernel(float value)
{
  setBlurKernelX(value);
  setBlurKernelY(value);
}

void MirrorTexture::setBlurKernelX(float value)
{
  if (stl_util::almost_equal(_blurKernelX, value)) {
    return;
  }

  _blurKernelX = value;
  _preparePostProcesses();
}

float MirrorTexture::blurKernelX() const
{
  return _blurKernelX;
}

void MirrorTexture::setBlurKernelY(float value)
{
  if (stl_util::almost_equal(_blurKernelY, value)) {
    return;
  }

  _blurKernelY = value;
  _preparePostProcesses();
}

float MirrorTexture::blurKernelY() const
{
  return _blurKernelY;
}

void MirrorTexture::_preparePostProcesses()
{
  clearPostProcesses(true);

  if (_blurKernelX != 0.f && _blurKernelY != 0.f) {
    auto engine = getScene()->getEngine();

    auto textureType = engine->getCaps().textureFloatRender ?
                         EngineConstants::TEXTURETYPE_FLOAT :
                         EngineConstants::TEXTURETYPE_HALF_FLOAT;

    _blurX = ::std::make_unique<BlurPostProcess>(
      "horizontal blur", Vector2(1.f, 0.f), _blurKernelX, _blurRatio, nullptr,
      TextureConstants::BILINEAR_SAMPLINGMODE, engine, false, textureType);
    _blurX->autoClear = false;

    if (_blurRatio == 1.f && samples() < 2) {
      _blurX->setOutputTexture(_texture);
    }
    else {
      _blurX->alwaysForcePOT = true;
    }

    _blurY = ::std::make_unique<BlurPostProcess>(
      "vertical blur", Vector2(0.f, 1.f), _blurKernelY, _blurRatio, nullptr,
      TextureConstants::BILINEAR_SAMPLINGMODE, engine, false, textureType);
    _blurY->autoClear      = false;
    _blurY->alwaysForcePOT = _blurRatio != 1.f;

    addPostProcess(_blurX.get());
    addPostProcess(_blurY.get());
  }
}

std::unique_ptr<MirrorTexture> MirrorTexture::clone() const
{
  auto textureSize = getSize();
  auto newTexture  = ::std::make_unique<MirrorTexture>(
    name,                                        //
    Size(textureSize.width, textureSize.height), //
    getScene(),                                  //
    _renderTargetOptions.generateMipMaps,        //
    _renderTargetOptions.type,                   //
    _renderTargetOptions.samplingMode,           //
    _renderTargetOptions.generateDepthBuffer     //
  );

  // Base texture
  newTexture->setHasAlpha(hasAlpha());
  newTexture->level = level;

  // Mirror Texture
  newTexture->mirrorPlane = mirrorPlane;
  newTexture->renderList  = renderList;

  return newTexture;
}

Json::object MirrorTexture::serialize() const
{
  return Json::object();
}

} // end of namespace BABYLON

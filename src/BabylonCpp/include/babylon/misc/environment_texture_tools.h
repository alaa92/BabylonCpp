#ifndef BABYLON_MISC_ENVIRONMENT_TEXTURE_TOOLS
#define BABYLON_MISC_ENVIRONMENT_TEXTURE_TOOLS

#include <array>
#include <memory>
#include <unordered_map>

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>
#include <babylon/babylon_fwd.h>

namespace BABYLON {

class ArrayBufferView;
class Engine;
class EnvironmentTextureInfo;
class EnvironmentTextureIrradianceInfoV1;
struct Image;
FWD_CLASS_SPTR(BaseTexture)
FWD_CLASS_SPTR(EnvironmentTextureInfo)
FWD_CLASS_SPTR(EnvironmentTextureIrradianceInfoV1)
FWD_CLASS_SPTR(InternalTexture)
FWD_CLASS_SPTR(PostProcess)
FWD_CLASS_SPTR(SphericalPolynomial)

/**
 * @brief Sets of helpers addressing the serialization and deserialization of environment texture
 * stored in a BabylonJS env file. Those files are usually stored as .env files.
 */
class BABYLON_SHARED_EXPORT EnvironmentTextureTools {

private:
  /**
   * Magic number identifying the env file.
   */
  static std::array<uint8_t, 8> _MagicBytes;

public:
  EnvironmentTextureTools();
  ~EnvironmentTextureTools(); // = default

  /**
   * @brief Gets the environment info from an env file.
   * @param data The array buffer containing the .env bytes.
   * @returns the environment file info (the json header) if successfully parsed.
   */
  static EnvironmentTextureInfoPtr GetEnvInfo(const ArrayBufferView& data);

  /**
   * @brief Creates the ArrayBufferViews used for initializing environment texture image data.
   * @param data the image data
   * @param info parameters that determine what views will be created for accessing the underlying
   * buffer
   * @return the views described by info providing access to the underlying buffer
   */
  static std::vector<std::vector<ArrayBuffer>>
  CreateImageDataArrayBufferViews(const ArrayBufferView& data, const EnvironmentTextureInfo& info);

  /**
   * @brief Uploads the texture info contained in the env file to the GPU.
   * @param texture defines the internal texture to upload to
   * @param data defines the data to load
   * @param info defines the texture info retrieved through the GetEnvInfo method
   * @returns a promise
   */
  static void UploadEnvLevelsSync(const InternalTexturePtr& texture, const ArrayBufferView& data,
                                  const EnvironmentTextureInfo& info);

  /**
   * @brief Uploads the levels of image data to the GPU.
   * @param texture defines the internal texture to upload to
   * @param imageData defines the array buffer views of image data [mipmap][face]
   */
  static void UploadLevelsSync(const InternalTexturePtr& texture,
                               const std::vector<std::vector<ArrayBuffer>>& imageData);

  /**
   * @brief Uploads spherical polynomials information to the texture.
   * @param texture defines the texture we are trying to upload the information to
   * @param info defines the environment texture info retrieved through the GetEnvInfo method
   */
  static void UploadEnvSpherical(const InternalTexturePtr& texture,
                                 const EnvironmentTextureInfo& info);

  /**
   * @brief Hidden
   */
  static void _UpdateRGBDSync(const InternalTexturePtr& internalTexture,
                              const std::vector<std::vector<ArrayBuffer>>& data,
                              const SphericalPolynomialPtr& sphericalPolynomial, float lodScale,
                              float lodOffset);

private:
  /**
   * @brief Creates a JSON representation of the spherical data.
   * @param texture defines the texture containing the polynomials
   * @return the JSON representation of the spherical info
   */
  static EnvironmentTextureIrradianceInfoV1Ptr
  _CreateEnvTextureIrradiance(const BaseTexturePtr& texture);

  /**
   * @brief Hidden
   */
  static void _OnImageReadySync(const Image& image, Engine* engine, bool expandTexture,
                                const PostProcessPtr& rgbdPostProcess, const std::string& url,
                                unsigned int face, int i, bool generateNonLODTextures,
                                const std::unordered_map<size_t, BaseTexturePtr>& lodTextures,
                                const InternalTexturePtr& cubeRtt,
                                const InternalTexturePtr& texture);

}; // end of class EnvironmentTextureTools

} // end of namespace BABYLON

#endif // end of BABYLON_MISC_ENVIRONMENT_TEXTURE_TOOLS

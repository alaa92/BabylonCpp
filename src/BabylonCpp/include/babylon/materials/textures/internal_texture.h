#ifndef BABYLON_MATERIALS_TEXTURES_INTERNAL_TEXTURE_H
#define BABYLON_MATERIALS_TEXTURES_INTERNAL_TEXTURE_H

#include <variant>

#include <babylon/babylon_api.h>
#include <babylon/babylon_common.h>
#include <babylon/core/structs.h>
#include <babylon/materials/textures/iinternal_texture_tracker.h>
#include <babylon/tools/observable.h>

namespace BABYLON {

class BaseTexture;
class Engine;
class ICanvasRenderingContext2D;
class SphericalPolynomial;
using BaseTexturePtr = std::shared_ptr<BaseTexture>;

namespace GL {
class IGLFramebuffer;
class IGLRenderbuffer;
class IGLTexture;
} // namespace GL

/**
 * @brief Class used to store data associated with WebGL texture data for the
 * engine This class should not be used directly.
 */
class BABYLON_SHARED_EXPORT InternalTexture : public IInternalTextureTracker {

public:
  /**
   * The source of the texture data is unknown
   */
  static constexpr unsigned int DATASOURCE_UNKNOWN = 0;
  /**
   * Texture data comes from an URL
   */
  static constexpr unsigned int DATASOURCE_URL = 1;
  /**
   * Texture data is only used for temporary storage
   */
  static constexpr unsigned int DATASOURCE_TEMP = 2;
  /**
   * Texture data comes from raw data (ArrayBuffer)
   */
  static constexpr unsigned int DATASOURCE_RAW = 3;
  /**
   * Texture content is dynamic (video or dynamic texture)
   */
  static constexpr unsigned int DATASOURCE_DYNAMIC = 4;
  /**
   * Texture content is generated by rendering to it
   */
  static constexpr unsigned int DATASOURCE_RENDERTARGET = 5;
  /**
   * Texture content is part of a multi render target process
   */
  static constexpr unsigned int DATASOURCE_MULTIRENDERTARGET = 6;
  /**
   * Texture data comes from a cube data file
   */
  static constexpr unsigned int DATASOURCE_CUBE = 7;
  /**
   * Texture data comes from a raw cube data
   */
  static constexpr unsigned int DATASOURCE_CUBERAW = 8;
  /**
   * Texture data come from a prefiltered cube data file
   */
  static constexpr unsigned int DATASOURCE_CUBEPREFILTERED = 9;
  /**
   * Texture content is raw 3D data
   */
  static constexpr unsigned int DATASOURCE_RAW3D = 10;
  /**
   * Texture content is a depth texture
   */
  static constexpr unsigned int DATASOURCE_DEPTHTEXTURE = 11;

  /**
   * Texture data comes from a raw cube data encoded with RGBD
   */
  static constexpr unsigned int DATASOURCE_CUBERAW_RGBD = 12;

public:
  /**
   * @brief Creates a new InternalTexture.
   * @param engine defines the engine to use
   * @param dataSource defines the type of data that will be used
   */
  InternalTexture(Engine* engine, unsigned int dataSource
                                  = InternalTexture::DATASOURCE_UNKNOWN);
  ~InternalTexture();

  /**
   * @brief Gets the Engine the texture belongs to.
   * @returns The babylon engine
   */
  Engine* getEngine();

  /**
   * @brief Gets the data source type of the texture (can be one of the
   * BABYLON.InternalTexture.DATASOURCE_XXXX).
   */
  unsigned int dataSource() const;

  /**
   * @brief Increments the number of references (ie. the number of
   * {BABYLON.Texture} that point to it).
   */
  void incrementReferences();

  /**
   * @brief Change the size of the texture (not the size of the content).
   * @param width defines the new width
   * @param height defines the new height
   * @param depth defines the new depth (1 by default)
   */
  void updateSize(int width, int height, int depth = 1);

  /**
   * @brief Rebuilds the internal texture.
   */
  void _rebuild();

  /**
   * @brief Hidden
   */
  void _swapAndDie(InternalTexture* target);

  /**
   * @brief Dispose the current allocated resources.
   */
  void dispose();

public:
  /**
   * Defines if the texture is ready
   */
  bool isReady;
  /**
   * Defines if the texture is a cube texture
   */
  bool isCube;
  /**
   * Defines if the texture contains 3D data
   */
  bool is3D;
  /**
   * Gets the URL used to load this texture
   */
  std::string url;
  /**
   * Gets the sampling mode of the texture
   */
  unsigned int samplingMode;
  /**
   * Gets a boolean indicating if the texture needs mipmaps generation
   */
  bool generateMipMaps;
  /**
   * Gets the number of samples used by the texture (WebGL2+ only)
   */
  unsigned int samples;
  /**
   * Gets the type of the texture
   */
  unsigned int type;
  /**
   * Gets the format of the texture
   */
  unsigned int format;
  /**
   * Observable called when the texture is loaded
   */
  Observable<InternalTexture> onLoadedObservable;
  /**
   * Gets the width of the texture
   */
  int width;
  /**
   * Gets the height of the texture
   */
  int height;
  /**
   * Gets the depth of the texture
   */
  int depth;
  /**
   * Gets the initial width of the texture (It could be rescaled if the current
   * system does not support non power of two textures)
   */
  int baseWidth;
  /**
   * Gets the initial height of the texture (It could be rescaled if the current
   * system does not support non power of two textures)
   */
  int baseHeight;
  /**
   * Gets the initial depth of the texture (It could be rescaled if the current
   * system does not support non power of two textures)
   */
  int baseDepth;
  /**
   * Gets a boolean indicating if the texture is inverted on Y axis
   */
  bool invertY;

  // Private
  int _initialSlot;
  int _designatedSlot;
  unsigned int _dataSource;
  std::variant<ArrayBuffer, Image> _buffer;
  ArrayBuffer _bufferView;
  std::vector<ArrayBuffer> _bufferViewArray;
  std::vector<std::vector<ArrayBuffer>> _bufferViewArrayArray;
  int _size;
  std::string _extension;
  std::vector<std::string> _files;
  ICanvas* _workingCanvas;
  ICanvasRenderingContext2D* _workingContext;
  std::shared_ptr<GL::IGLFramebuffer> _framebuffer;
  std::shared_ptr<GL::IGLRenderbuffer> _depthStencilBuffer;
  std::unique_ptr<GL::IGLFramebuffer> _MSAAFramebuffer;
  Uint32Array _attachments;
  std::unique_ptr<GL::IGLRenderbuffer> _MSAARenderBuffer;
  unsigned int _cachedCoordinatesMode;
  unsigned int _cachedWrapU;
  unsigned int _cachedWrapV;
  unsigned int _cachedWrapR;
  unsigned int _cachedAnisotropicFilteringLevel;
  bool _isDisabled;
  std::string _compression;
  bool _generateStencilBuffer;
  bool _generateDepthBuffer;
  int _comparisonFunction;
  std::unique_ptr<SphericalPolynomial> _sphericalPolynomial;
  float _lodGenerationScale;
  float _lodGenerationOffset;
  // The following three fields helps sharing generated fixed LODs for texture
  // filtering
  // In environment not supporting the textureLOD extension like EDGE. They are
  // for internal use only.
  // They are at the level of the gl texture to benefit from the cache.
  BaseTexturePtr _lodTextureHigh;
  BaseTexturePtr _lodTextureMid;
  BaseTexturePtr _lodTextureLow;
  bool _isRGBD;

  std::shared_ptr<GL::IGLTexture> _webGLTexture;
  int _references;

private:
  Engine* _engine;

}; // end of struct InternalTexture

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_TEXTURES_INTERNAL_TEXTURE_H

#ifndef BABYLON_PROCEDURAL_TEXTURES_LIBRARY_ROAD_ROAD_PROCEDURAL_TEXTURE_H
#define BABYLON_PROCEDURAL_TEXTURES_LIBRARY_ROAD_ROAD_PROCEDURAL_TEXTURE_H

#include <babylon/babylon_global.h>
#include <babylon/materials/textures/procedurals/procedural_texture.h>
#include <babylon/math/color3.h>

namespace BABYLON {
namespace ProceduralTexturesLibrary {

class BABYLON_SHARED_EXPORT RoadProceduralTexture : public ProceduralTexture {

public:
  template <typename... Ts>
  static RoadProceduralTexture* New(Ts&&... args)
  {
    auto texture = new RoadProceduralTexture(::std::forward<Ts>(args)...);
    texture->addToScene(
      static_cast<unique_ptr_t<RoadProceduralTexture>>(texture));

    return texture;
  }
  ~RoadProceduralTexture();

  void updateShaderUniforms();

  /**
   * @brief Serializes this road procedural texture.
   * @returns a serialized road procedural texture object
   */
  Json::object serialize() const;

  /**
   * @brief Creates a Road Procedural Texture from parsed road procedural
   * texture data.
   * @param parsedTexture defines parsed texture data
   * @param scene defines the current scene
   * @param rootUrl defines the root URL containing road procedural texture
   * information
   * @returns a parsed Road Procedural Texture
   */
  static unique_ptr_t<RoadProceduralTexture>
  Parse(const Json::value& parsedTexture, Scene* scene,
        const string_t& rootUrl);

protected:
  RoadProceduralTexture(const std::string& name, const Size& size, Scene* scene,
                        Texture* fallbackTexture = nullptr,
                        bool generateMipMaps     = false);

  Color3& get_roadColor();
  void set_roadColor(const Color3& value);

public:
  Property<RoadProceduralTexture, Color3> roadColor;

private:
  Color3 _roadColor;

}; // end of class RoadProceduralTexture

} // end of namespace ProceduralTexturesLibrary
} // end of namespace BABYLON

#endif // end of
       // BABYLON_PROCEDURAL_TEXTURES_LIBRARY_ROAD_ROAD_PROCEDURAL_TEXTURE_H

#include <babylon/materials/pbr/pbr_material_defines.h>

#include <sstream>

namespace BABYLON {

PBRMaterialDefines::PBRMaterialDefines()
{
  boolDef = {
    {"PBR", true}, //

    {"REALTIME_FILTERING", false}, //

    {"MAINUV1", false}, //
    {"MAINUV2", false}, //
    {"UV1", false},     //
    {"UV2", false},     //

    {"ALBEDO", false},      //
    {"GAMMAALBEDO", false}, //
    {"VERTEXCOLOR", false}, //

    {"DETAIL", false}, //

    {"AMBIENT", false},            //
    {"AMBIENTINGRAYSCALE", false}, //

    {"OPACITY", false},            //
    {"VERTEXALPHA", false},        //
    {"OPACITYRGB", false},         //
    {"ALPHATEST", false},          //
    {"DEPTHPREPASS", false},       //
    {"ALPHABLEND", false},         //
    {"ALPHAFROMALBEDO", false},    //
    {"SPECULAROVERALPHA", false},  //
    {"RADIANCEOVERALPHA", false},  //
    {"ALPHAFRESNEL", false},       //
    {"LINEARALPHAFRESNEL", false}, //
    {"PREMULTIPLYALPHA", false},   //

    {"EMISSIVE", false}, //

    {"REFLECTIVITY", false}, //
    {"SPECULARTERM", false}, //

    {"MICROSURFACEFROMREFLECTIVITYMAP", false}, //
    {"MICROSURFACEAUTOMATIC", false},           //
    {"LODBASEDMICROSFURACE", false},            //
    {"MICROSURFACEMAP", false},                 //

    {"METALLICWORKFLOW", false},              //
    {"ROUGHNESSSTOREINMETALMAPALPHA", false}, //
    {"ROUGHNESSSTOREINMETALMAPGREEN", false}, //
    {"METALLNESSSTOREINMETALMAPBLUE", false}, //
    {"AOSTOREINMETALMAPRED", false},          //

    {"METALLIC_REFLECTANCE", false}, //

    {"ENVIRONMENTBRDF", false},      //
    {"ENVIRONMENTBRDF_RGBD", false}, //

    {"NORMAL", false},                //
    {"TANGENT", false},               //
    {"BUMP", false},                  //
    {"OBJECTSPACE_NORMALMAP", false}, //
    {"PARALLAX", false},              //
    {"PARALLAXOCCLUSION", false},     //
    {"NORMALXYSCALE", true},          //

    {"LIGHTMAP", false},               //
    {"USELIGHTMAPASSHADOWMAP", false}, //
    {"GAMMALIGHTMAP", false},          //
    {"RGBDLIGHTMAP", false},           //

    {"REFLECTION", false},                                  //
    {"REFLECTIONMAP_3D", false},                            //
    {"REFLECTIONMAP_SPHERICAL", false},                     //
    {"REFLECTIONMAP_PLANAR", false},                        //
    {"REFLECTIONMAP_CUBIC", false},                         //
    {"USE_LOCAL_REFLECTIONMAP_CUBIC", false},               //
    {"REFLECTIONMAP_PROJECTION", false},                    //
    {"REFLECTIONMAP_SKYBOX", false},                        //
    {"REFLECTIONMAP_EXPLICIT", false},                      //
    {"REFLECTIONMAP_EQUIRECTANGULAR", false},               //
    {"REFLECTIONMAP_EQUIRECTANGULAR_FIXED", false},         //
    {"REFLECTIONMAP_MIRROREDEQUIRECTANGULAR_FIXED", false}, //
    {"INVERTCUBICMAP", false},                              //
    {"USESPHERICALFROMREFLECTIONMAP", false},               //
    {"USEIRRADIANCEMAP", false},                            //
    {"SPHERICAL_HARMONICS", false},                         //
    {"USESPHERICALINVERTEX", false},                        //
    {"REFLECTIONMAP_OPPOSITEZ", false},                     //
    {"LODINREFLECTIONALPHA", false},                        //
    {"GAMMAREFLECTION", false},                             //
    {"RGBDREFLECTION", false},                              //
    {"LINEARSPECULARREFLECTION", false},                    //
    {"RADIANCEOCCLUSION", false},                           //
    {"HORIZONOCCLUSION", false},                            //

    {"INSTANCES", false},      //
    {"THIN_INSTANCES", false}, //

    {"PREPASS", false},              //
    {"PREPASS_IRRADIANCE", false},   //
    {"PREPASS_ALBEDO", false},       //
    {"PREPASS_DEPTHNORMAL", false},  //
    {"PREPASS_POSITION", false},     //
    {"PREPASS_VELOCITY", false},     //
    {"PREPASS_REFLECTIVITY", false}, //

    {"BONETEXTURE", false},            //
    {"BONES_VELOCITY_ENABLED", false}, //

    {"NONUNIFORMSCALING", false}, //

    {"MORPHTARGETS", false},         //
    {"MORPHTARGETS_NORMAL", false},  //
    {"MORPHTARGETS_TANGENT", false}, //
    {"MORPHTARGETS_UV", false},      //

    {"IMAGEPROCESSING", false},            //
    {"VIGNETTE", false},                   //
    {"VIGNETTEBLENDMODEMULTIPLY", false},  //
    {"VIGNETTEBLENDMODEOPAQUE", false},    //
    {"TONEMAPPING", false},                //
    {"TONEMAPPING_ACES", false},           //
    {"CONTRAST", false},                   //
    {"COLORCURVES", false},                //
    {"COLORGRADING", false},               //
    {"COLORGRADING3D", false},             //
    {"SAMPLER3DGREENDEPTH", false},        //
    {"SAMPLER3DBGRMAP", false},            //
    {"IMAGEPROCESSINGPOSTPROCESS", false}, //
    {"EXPOSURE", false},                   //
    {"MULTIVIEW", false},                  //

    {"USEPHYSICALLIGHTFALLOFF", false}, //
    {"USEGLTFLIGHTFALLOFF", false},     //
    {"TWOSIDEDLIGHTING", false},        //
    {"SHADOWFLOAT", false},             //
    {"CLIPPLANE", false},               //
    {"CLIPPLANE2", false},              //
    {"CLIPPLANE3", false},              //
    {"CLIPPLANE4", false},              //
    {"CLIPPLANE5", false},              //
    {"CLIPPLANE6", false},              //
    {"POINTSIZE", false},               //
    {"FOG", false},                     //
    {"LOGARITHMICDEPTH", false},        //

    {"FORCENORMALFORWARD", false}, //

    {"SPECULARAA", false}, //

    {"CLEARCOAT", false},                                //
    {"CLEARCOAT_DEFAULTIOR", false},                     //
    {"CLEARCOAT_TEXTURE", false},                        //
    {"CLEARCOAT_TEXTURE_ROUGHNESS", false},              //
    {"CLEARCOAT_USE_ROUGHNESS_FROM_MAINTEXTURE", false}, //
    {"CLEARCOAT_TEXTURE_ROUGHNESS_IDENTICAL", false},    //
    {"CLEARCOAT_BUMP", false},                           //
    {"CLEARCOAT_REMAP_F0", true},                        //
    {"CLEARCOAT_TINT", false},                           //
    {"CLEARCOAT_TINT_TEXTURE", false},                   //

    {"ANISOTROPIC", false},         //
    {"ANISOTROPIC_TEXTURE", false}, //

    {"BRDF_V_HEIGHT_CORRELATED", false},                //
    {"MS_BRDF_ENERGY_CONSERVATION", false},             //
    {"SPECULAR_GLOSSINESS_ENERGY_CONSERVATION", false}, //

    {"SHEEN", false},                                //
    {"SHEEN_TEXTURE", false},                        //
    {"SHEEN_TEXTURE_ROUGHNESS", false},              //
    {"SHEEN_LINKWITHALBEDO", false},                 //
    {"SHEEN_ROUGHNESS", false},                      //
    {"SHEEN_ALBEDOSCALING", false},                  //
    {"SHEEN_USE_ROUGHNESS_FROM_MAINTEXTURE", false}, //
    {"SHEEN_TEXTURE_ROUGHNESS_IDENTICAL", false},    //

    {"SUBSURFACE", false}, //

    {"SS_REFRACTION", false},   //
    {"SS_TRANSLUCENCY", false}, //
    {"SS_SCATTERING", false},   //

    {"SS_THICKNESSANDMASK_TEXTURE", false}, //

    {"SS_REFRACTIONMAP_3D", false},             //
    {"SS_REFRACTIONMAP_OPPOSITEZ", false},      //
    {"SS_LODINREFRACTIONALPHA", false},         //
    {"SS_GAMMAREFRACTION", false},              //
    {"SS_RGBDREFRACTION", false},               //
    {"SS_LINEARSPECULARREFRACTION", false},     //
    {"SS_LINKREFRACTIONTOTRANSPARENCY", false}, //
    {"SS_ALBEDOFORREFRACTIONTINT", false},      //

    {"SS_MASK_FROM_THICKNESS_TEXTURE", false},      //
    {"SS_MASK_FROM_THICKNESS_TEXTURE_GLTF", false}, //

    {"UNLIT", false}, //
  };

  intDef = {
    {"NUM_SAMPLES", 0},                         //
    {"AMBIENTDIRECTUV", 0},                     //
    {"ALBEDODIRECTUV", 0},                      //
    {"DETAILDIRECTUV", 0},                      //
    {"DETAIL_NORMALBLENDMETHOD", 0},            //
    {"OPACITYDIRECTUV", 0},                     //
    {"EMISSIVEDIRECTUV", 0},                    //
    {"REFLECTIVITYDIRECTUV", 0},                //
    {"MICROSURFACEMAPDIRECTUV", 0},             //
    {"METALLIC_REFLECTANCEDIRECTUV", 0},        //
    {"BUMPDIRECTUV", 0},                        //
    {"LIGHTMAPDIRECTUV", 0},                    //
    {"NUM_BONE_INFLUENCERS", 0},                //
    {"BonesPerMesh", 0},                        //
    {"PREPASS_IRRADIANCE_INDEX", -1},           //
    {"PREPASS_ALBEDO_INDEX", -1},               //
    {"PREPASS_DEPTHNORMAL_INDEX", -1},          //
    {"PREPASS_POSITION_INDEX", -1},             //
    {"PREPASS_VELOCITY_INDEX", -1},             //
    {"PREPASS_REFLECTIVITY_INDEX", -1},         //
    {"SCENE_MRT_COUNT", 0},                     //
    {"NUM_MORPH_INFLUENCERS", 0},               //
    {"CLEARCOAT_TEXTUREDIRECTUV", 0},           //
    {"CLEARCOAT_TEXTURE_ROUGHNESSDIRECTUV", 0}, //
    {"CLEARCOAT_BUMPDIRECTUV", 0},              //
    {"CLEARCOAT_TINT_TEXTUREDIRECTUV", 0},      //
    {"ANISOTROPIC_TEXTUREDIRECTUV", 0},         //
    {"SHEEN_TEXTUREDIRECTUV", 0},               //
    {"SHEEN_TEXTURE_ROUGHNESSDIRECTUV", 0},     //
    {"SS_THICKNESSANDMASK_TEXTUREDIRECTUV", 0}, //
    {"DEBUGMODE", 0},                           //
  };

  stringDef = {
    {"ALPHATESTVALUE", "0.5"}, //
  };
}

PBRMaterialDefines::~PBRMaterialDefines() = default;

void PBRMaterialDefines::reset()
{
  MaterialDefines::reset();

  boolDef["PBR"]           = true;
  boolDef["NORMALXYSCALE"] = true;

  stringDef["ALPHATESTVALUE"] = "0.5";
}

std::string PBRMaterialDefines::toString() const
{
  std::ostringstream oss;
  oss << MaterialDefines::toString();
  oss << IImageProcessingConfigurationDefines::convertToString();

  return oss.str();
}

} // end of namespace BABYLON

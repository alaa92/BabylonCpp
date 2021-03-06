﻿#ifndef BABYLON_SHADERS_SHADERS_INCLUDE_PRE_PASS_DECLARATION_FX_H
#define BABYLON_SHADERS_SHADERS_INCLUDE_PRE_PASS_DECLARATION_FX_H

namespace BABYLON {

extern const char* prePassDeclaration;

const char* prePassDeclaration
  = R"ShaderCode(

#ifdef PREPASS
#extension GL_EXT_draw_buffers : require
#ifdef WEBGL2
layout(location = 0) out highp vec4 glFragData[{X}];
highp vec4 gl_FragColor;
#endif

#ifdef PREPASS_DEPTHNORMAL
    varying highp vec3 vViewPos;
#endif
#ifdef PREPASS_VELOCITY
    varying highp vec4 vCurrentPosition;
    varying highp vec4 vPreviousPosition;
#endif

#endif

)ShaderCode";

} // end of namespace BABYLON

#endif // end of BABYLON_SHADERS_SHADERS_INCLUDE_PRE_PASS_DECLARATION_FX_H

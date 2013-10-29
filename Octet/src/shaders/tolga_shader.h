////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012, 2013
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Single texture shader with no lighting

namespace octet {
  class tolga_shader : public shader {
    // indices to use with glUniform*()

    // index for model space to projection space matrix
    GLuint modelToProjectionIndex_;

    // index for texture sampler
    //GLuint samplerIndex_;

    // index for random feed
    GLuint randomFeedRIndex_;
    GLuint randomFeedGIndex_;
    GLuint randomFeedBIndex_;



  public:
    void init() {
      // this is the vertex shader.
      // it is called for each corner of each triangle
      // it inputs pos and uv from each corner
      // it outputs gl_Position and uv_ to the rasterizer
      const char vertex_shader[] = SHADER_STR(
        //varying vec2 uv_;

        attribute vec4 pos;
        //attribute vec2 uv;

        uniform mat4 modelToProjection;
        uniform float randomFeedR;

        void main() 
        { 
          gl_Position = pos * vec4(0.1,0.1,0.1,1.0); 
        }
      );

      // this is the fragment shader
      // after the rasterizer breaks the triangle into fragments
      // this is called for every fragment
      // it outputs gl_FragColor, the color of the pixel and inputs uv_
      const char fragment_shader[] = SHADER_STR(
        varying vec2 uv_;
        //uniform sampler2D sampler;
        uniform float randomFeedR;
        uniform float randomFeedG;
        uniform float randomFeedB;

        vec4 col;
        void main() 
        { 
          col = vec4(randomFeedR, randomFeedG, randomFeedB, 1.0);
          //gl_FragColor = texture2D(sampler, uv_); 
          gl_FragColor = col;
        }
      );
    
      // use the common shader code to compile and link the shaders
      // the result is a shader program
      shader::init(vertex_shader, fragment_shader);

      // extract the indices of the uniforms to use later
      modelToProjectionIndex_ = glGetUniformLocation(program(), "modelToProjection");
      //samplerIndex_ = glGetUniformLocation(program(), "sampler");
      randomFeedRIndex_ = glGetUniformLocation(program(), "randomFeedR");
      randomFeedGIndex_ = glGetUniformLocation(program(), "randomFeedG");
      randomFeedBIndex_ = glGetUniformLocation(program(), "randomFeedB");
    }

    void render(const mat4t &modelToProjection, float randomFeedR, float randomFeedG, float randomFeedB) {
      // tell openGL to use the program
      shader::render();

      // customize the program with uniforms
      glUniform1f(randomFeedRIndex_, randomFeedR);
      glUniform1f(randomFeedGIndex_, randomFeedG);
      glUniform1f(randomFeedBIndex_, randomFeedB);
      //glUniform1i(samplerIndex_, sampler);
      glUniformMatrix4fv(modelToProjectionIndex_, 1, GL_FALSE, modelToProjection.get());
    }
  };
}

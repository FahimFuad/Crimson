#include <Crimson.h>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class App : public Crimson::Application {
private:
   Crimson::Shader m_shader;
   Crimson::Model m_model;
   Crimson::Texture m_texture;
   Crimson::Light m_directional;
   Crimson::Camera m_camera;

   Crimson::Material m_shinyMaterial;

   glm::mat4 m_modl;
   glm::mat4 m_view;

   float m_curAngle = 0.0f;
public:
   App() :
      m_camera(glm::vec3(0,0,-5), 45.0f, 800/600, 0.1f, 100.0f),
      m_model("Resources/monkey3.obj"),
      m_texture("Resources/Wood.jpg"),
      m_shader("Resources/Basic.vert", "Resources/Basic.frag"),
      m_shinyMaterial(1.0f, 32) {}

   void OnBegin() override  {
      m_texture.Bind(0);

      m_modl = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
      m_modl = glm::rotate(m_modl, 5.5f, glm::vec3(0, 1, 0));
      m_modl = glm::scale(m_modl, glm::vec3(1.0f, 1.0f, 1.0f));

      m_shader.Bind();
      m_shader.SetUniform1i("tex", 0);
      m_shader.SetUniformMatrix4("modl", m_modl);

      /*m_directional.UseLight(m_shader.GetUniformLocation("directionalLight.ambientIntensity"),
                             m_shader.GetUniformLocation("directionalLight.color"),
                             m_shader.GetUniformLocation("directionalLight.diffuseIntensity"),
                             m_shader.GetUniformLocation("directionalLight.direction"));*/

      m_shader.SetUniform3f("eyePosition", m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z);
      m_shinyMaterial.UseMaterial(m_shader.GetUniformLocation("material.specularIntensity"),
                                  m_shader.GetUniformLocation("material.shininess"));

      m_shader.SetUniform3f("directionalLight.color", 1, 1, 1);
      m_shader.SetUniform1f("directionalLight.ambientIntensity", 0.2f);
      m_shader.SetUniform1f("directionalLight.diffuseIntensity", 0.9f);
      m_shader.SetUniform3f("directionalLight.direction", 1, 1, 0);
   }

   void OnUpdate(float delta) override {
      m_shader.SetUniformMatrix4("view", m_camera.GetViewProjection());
      m_shader.SetUniform3f("eyePosition", m_camera.GetPosition().x, m_camera.GetPosition().y, m_camera.GetPosition().z);

      float pitch = m_camera.GetPitch();
      float yaw = m_camera.GetYaw();

      float rotSpeed = 800.0f;
      float moveSpeed = 10.0f;

      float yoffset = 0.0f;
      float xoffset = 0.0f;

      if (m_keyboard.IsKeyHeld(SDL_SCANCODE_UP)) {
         yoffset = rotSpeed * delta;
      } else if (m_keyboard.IsKeyHeld(SDL_SCANCODE_DOWN)) {
         yoffset = -rotSpeed * delta;
      }

      if (m_keyboard.IsKeyHeld(SDL_SCANCODE_LEFT)) {
         xoffset = -rotSpeed * delta;
      } else if (m_keyboard.IsKeyHeld(SDL_SCANCODE_RIGHT)) {
         xoffset = rotSpeed * delta;
      }

      float sensitivity = 0.1f;
      xoffset *= sensitivity;
      yoffset *= sensitivity;

      yaw += xoffset;
      pitch += yoffset;

      if (pitch > 89.0f) {
         pitch = 89.0f;
      }

      if (pitch < -89.0f) {
         pitch = -89.0f;
      }

      m_camera.SetRotation(yaw, pitch);


      glm::vec3 pos = m_camera.GetPosition();
      float rot = glm::radians(m_camera.GetYaw());
      if (m_keyboard.IsKeyHeld(SDL_SCANCODE_W)) {
         pos.x -= (float)cos(rot) * moveSpeed * -1.0f * delta;
         pos.z += (float)sin(rot) * moveSpeed * delta;
      } else if (m_keyboard.IsKeyHeld(SDL_SCANCODE_S)) {
         pos.x -= (float)cos(rot) * moveSpeed * 1.0f * delta;
         pos.z -= (float)sin(rot) * moveSpeed * delta;
      }
      if (m_keyboard.IsKeyHeld(SDL_SCANCODE_D)) {
         pos.x -= (float)sin(rot) * moveSpeed * delta;
         pos.z += (float)cos(rot) * moveSpeed * 1.0f * delta;
      } else if (m_keyboard.IsKeyHeld(SDL_SCANCODE_A)) {
         pos.x += (float)sin(rot) * moveSpeed * delta;
         pos.z += (float)cos(rot) * moveSpeed * -1.0f * delta;
      }

      if (m_keyboard.IsKeyHeld(SDL_SCANCODE_SPACE)) {
         pos.y+=5.5f*delta;
      } else if (m_keyboard.IsKeyHeld(SDL_SCANCODE_LSHIFT)) {
         pos.y-=5.5f*delta;
      }

      m_camera.SetPosition(pos);
   }

   void OnRender(float delta) override {
      m_shader.SetUniformMatrix4("modl", m_modl);
      m_model.Render();
   }
};

int main(int argc, char const *argv[]) {
   App app;
   app.Run();

   return 0;
}

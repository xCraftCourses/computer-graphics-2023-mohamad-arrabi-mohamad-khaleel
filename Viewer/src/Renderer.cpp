#include "Renderer.h"
#include "MeshModel.h"
#include "ShaderProgram.h"
#include <imgui/imgui.h>
#include <vector>
#include <memory>
#include <algorithm>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Render(const std::shared_ptr<Scene>& scene)
{
	int cameraCount = scene->GetCameraCount();
	if (cameraCount > 0)
	{
		int modelCount = scene->GetModelCount();
		const Camera& camera = scene->GetActiveCamera();
	
		for(int currentModelIndex = 0; currentModelIndex < modelCount; currentModelIndex++)
		{
			std::shared_ptr<MeshModel> currentModel = scene->GetModel(currentModelIndex);

			// Activate the 'colorShader' program (vertex and fragment shaders)
			colorShader.use();

			// Set the uniform variables
			colorShader.setUniform("model", currentModel->GetWorldTransformation() * currentModel->GetModelTransformation());
			colorShader.setUniform("view", camera.GetViewTransformation());
			colorShader.setUniform("projection", camera.GetProjectionTransformation());
			colorShader.setUniform("material.textureMap", 0);

			colorShader.setUniform("material.obj_ambientColor", currentModel->ambientColor);
			colorShader.setUniform("material.obj_diffuseColor", currentModel->diffuseColor);
			colorShader.setUniform("material.obj_specularColor", currentModel->specularColor);

			colorShader.setUniform("material.l_ambientColor", scene->GetLight(0)->ambientColor);
			colorShader.setUniform("material.l_diffuseColor", scene->GetLight(0)->diffuseColor);
			colorShader.setUniform("material.l_specularColor", scene->GetLight(0)->specularColor);
			colorShader.setUniform("material.ver", scene->GetLight(0)->alpha);

			colorShader.setUniform("material.p_light", scene->GetLight(0)->GetPosition());
			colorShader.setUniform("material.eye", camera.GetEye());

			colorShader.setUniform("material.normalMapping", false);

			// Set 'texture1' as the active texture at slot #0
			texture1.bind(0);

			// Drag our model's faces (triangles) in fill mode
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);

			// Unset 'texture1' as the active texture at slot #0
			texture1.unbind(0);

			colorShader.setUniform("color", glm::vec3(0,0,0));

			// Drag our model's faces (triangles) in line mode (wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBindVertexArray(currentModel->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, currentModel->GetModelVertices().size());
			glBindVertexArray(0);
		}
	}
}

void Renderer::LoadShaders()
{
	colorShader.loadShaders("vshader_color.glsl", "fshader_color.glsl");
}

void Renderer::LoadTextures()
{
	if (!texture1.loadTexture("C:\\Users\\USER1\\Documents\\GitHub\\computer-graphics-2023-mohamad-arrabi-mohamad-khaleel\\Data\\gollum.jpg", true))
	{
		texture1.loadTexture("C:\\Users\\USER1\\Documents\\GitHub\\computer-graphics-2023-mohamad-arrabi-mohamad-khaleel\\Data\\gollum.jpg", true);
	}
}
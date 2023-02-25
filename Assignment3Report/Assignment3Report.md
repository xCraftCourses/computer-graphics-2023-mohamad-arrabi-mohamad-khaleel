1)
first, it creates a unique identifier for an opengl texture and for a vertex array object (VAO). Then, it creates a buffer, and copies the vertex and texture coordinates data to it. Finally, it creates a shader program, and tells the shader where to look for the vertex position data, and the data dimensions.

2)
we started my loading the mesh model to the GPU.

3)
This is the code for the vShader:
```c++
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	orig_fragPos = vec3(vec4(pos, 1.0f));
	fragPos = vec3(model * vec4(pos, 1.0f));
	fragNormal = mat3(model) * normal;

	// Pass the vertex texture coordinates property as it is. Its interpolated value
	// will be avilable for us in the fragment shader
	fragTexCoords = texCoords;

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position = projection * view *  model * vec4(pos, 1.0f);
}
```
4)
We implemented a simple fragment shader that outputs a constant color:
```c++
#version 330 core

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;

// The final color of the fragment (pixel)
out vec4 frag_color;

void main()
{
	frag_color = vec4(vec3(0.0f, 0.0f, 1.0f),1);
}
```
5)
here, we loaded all the variables and parameters to the GPU:
```c++
colorShader.setUniform("model", currentModel->GetWorldTransformation() *currentModel->GetModelTransformation());
colorShader.setUniform("camera", camera.GetViewTransformation());
colorShader.setUniform("projection", camera.GetProjectionTransformation());
colorShader.setUniform("material.textureMap", 0);

colorShader.setUniform("material.objAmbientColor", currentModel->ambientColor);
colorShader.setUniform("material.objDiffuseColor", currentModel->diffuseColor);
colorShader.setUniform("material.objSpecularColor",currentModel->specularColor);

colorShader.setUniform("material.lightAmbientColor", scene->GetLigh(0->ambientColor);
colorShader.setUniform("material.lightDiffuseColor", scene->GetLigh(0->diffuseColor);
colorShader.setUniform("material.lightSpecularColor", scene->GetLigh(0->specularColor);
colorShader.setUniform("material.alpha", scene->GetLight(0)->alpha);

colorShader.setUniform("material.lightPos", scene->GetLight(0)->GetPosition());
colorShader.setUniform("material.eye", camera.GetEye());
```
6)
we load image cow and do phong lighting:
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment3Report/phong%20lighting%20cow.png)

7)
now the plane mapping in image toon, first image:
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment3Report/toon%20plane%20mapping%201.png)
second image after we do rotate:
![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment3Report/toon%20plane%20mapping%202.png)
 8)
 cylindrical mapping:
 ![alt text]()

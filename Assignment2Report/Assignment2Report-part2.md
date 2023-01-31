in this part we add new class "Light" and in the class we added 3 RGB values, one for the ambient light, one for the diffuse light and one for the specular light. we also added 3 RGB values to the mesh model as these represent the material of the object:
glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
we ran the program and we got the following output: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/first%20we%20see.png)
we also saw the effect of the object material color. we set it's ambient color material to red (1, 0, 0) so that only the red component of the light gets displayed.
now we see the change when we change the ambient light, first image : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/ambient%20light%201.png)
and another image when we change the ambient light : ![alt text]()

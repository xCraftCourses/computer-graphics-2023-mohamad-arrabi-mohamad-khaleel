in this part we add new class "Light" and in the class we added 3 RGB values, one for the ambient light, one for the diffuse light and one for the specular light. we also added 3 RGB values to the mesh model as these represent the material of the object:
glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
we ran the program and we got the following output:

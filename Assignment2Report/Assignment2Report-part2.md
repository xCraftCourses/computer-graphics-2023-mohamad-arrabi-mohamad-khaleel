in this part we add new class "Light" and in the class we added 3 RGB values, one for the ambient light, one for the diffuse light and one for the specular light. we also added 3 RGB values to the mesh model as these represent the material of the object:
glm::vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
we ran the program and we got the following output: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/first%20we%20see.png)
we also saw the effect of the object material color. we set it's ambient color material to red (1, 0, 0) so that only the red component of the light gets displayed.
now we see the change when we change the ambient light, first image : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/ambient%20light%201.png)
and another image when we change the ambient light : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/ambient%20light%202.png)
now we calculated the diffuse component and added it to the color: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/ambient%20and%20difuse.png)
now we added the gouroud shading and the difference is clear. We can se that the object is smoother around the edges of the triangles as it makes a smooth transition between the colors of neighboring pixels: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/add%20gouroud%20shading.png)
Then, we implemented the phong shading with the specular light (we used the equations in the slides to calculate all the light reflections and intensity for all shading components).

we have drawn the reflection direction of each face : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/reflection%20vector.png)
now this is the result of the phong shading. We can clearly see the effect of the alpha which is the specular intensity, it changes the object's reflection intensity from a "mirrory" look to a more "matte" look. first image with alpha = 1.0 : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment2Report/specular%20alpha%201.png)
and this when alpha = 10.20 : ![alt text]()

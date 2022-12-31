we implement orthographic projection by use glm::ortho:
we load bunny model :  ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bunny%20image.png)
when we increase the left(before was -1 we increase to 0.098): ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/left%20bunny%20orth.png)
when we increase the up : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/up%20bunny%20orth.png)
we implement the ability to change position the camera, frist we load bunny image with default position: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/image%20bunny%20to%20reposition.png)
and now after we change the position we do reposition : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bunny%20with%20reposition.png)
and this image for camera transformation from the GUI : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/camera%20transformation.png)
to Allow the user to set the view volume automatically based on the window’s size in main.cpp when the windowsWidth and windowsHeight change the size of the model that we draw change appropriately but the model stay in there same position but with appropriately with new size of the windows. 
we load buuny image and this view value : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bunny%20image%20size%20window.png)
and we show the change when we change the size of view volume : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bunny%20after%20change%20view%20volume.png)
bunny image with local axes and world axes : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/local%20and%20world%20axes.png)
when we do local rotate the local axes not transform : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/local%20axes%20local%20transformation.png)
when we do world rotate the local axes transform : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/local%20axes%20world%20rotate.png)
to show the not commutative we load bunny model: ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bunny%20not%20com.png)
to show the different: 1) we do translate in the local axis and rotate in the world axis : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/local%20translate%20world%20rotate.png)
2) we do translate in the world axis and rotate in the local axis : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/world%20translate%20local%20rotate.png)
the different that we see in 1) the model rotate around world axes and in 2) the model rotate around local axes

image of the bounding box : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/bounding%20box.png)
that was transform when we transform the model.

bunny image with vertex normal : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/vertex%20normal.png)
after that we do translate : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/normal%20vertex%20translate.png)
we do rotate : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/normal%20vertex%20rotate.png)
bunny image with face normal : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/face%20normal.png)
after that we do translate : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/face%20normal%20translate.png)
we do rotate : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/face%20normal%20rotate.png)
explain how we do that : The vertecis normals are found in the "obj" file, so from each vertex we drew a line in the direction of the normal.
We calculated faces normals by ourselves. This is the formula that we used (p1, p2 and p3 are the points of the triangle/face):

glm::vec3 U = p2 - p1;
glm::vec3 V = p3 - p1;
float x = (U.y * V.z) - (U.z * V.y);
float y = (U.z * V.x) - (U.x * V.z);
float z = (U.x * V.y) - (U.y * V.x);
comparison between translating in the z axis in the orthographic and perspective projection: first we load bunny image : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/image%20bunny%20compare.png)
now we do local translate z in orthographic we see that not effect : ![alt text]()
we set camera position (1,1,1) and orient it towards the origin. in orthographic : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/ortho%20a%20position.png) in prespective : ![alt text](https://github.com/HaifaGraphicsCourses/computer-graphics-2023-mohamad-arrabi-mohamad-khaleel/blob/master/Assignment1Report/prespective%20a%20position.png)

<<<<<<< HEAD
#version 330 core

struct Material
{
	sampler2D textureMap;
	vec3 l_ambientColor;
	vec3 l_diffuseColor;
	vec3 l_specularColor;
	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
	float ver;
	vec3 vertex_normal;
	vec3 p_light;
	vec3 eye;
	vec3 obj_ambientColor;
	vec3 obj_diffuseColor;
	vec3 obj_specularColor;
};

// We set this field's properties from the C++ code
uniform Material material;

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 frag_color;

int toon = 5;
float PI = 3.14159;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec2 cylinder = vec2((atan(orig_fragPos.y , 1.5 * orig_fragPos.x) + PI * 0.5) / PI, -(-orig_fragPos.z + 0.5));
	vec2 spherical = vec2(atan(orig_fragPos.x, orig_fragPos.z) / (2 * PI), asin(orig_fragPos.y / 3) / PI);
	vec3 texture_color = vec3(texture(material.textureMap, fragTexCoords));
	vec3 Ia = material.l_ambientColor * material.obj_ambientColor;
	vec3 light_vec = normalize(material.p_light - fragPos);
	float toonlevel = floor(pow(max(float(dot(fragNormal, light_vec)), 0.0f), material.ver) * toon);
	vec2 plane = vec2(orig_fragPos.x, orig_fragPos.y);
	vec3 Is = material.l_specularColor * material.obj_specularColor * (toonlevel / toon);
	vec3 Id = material.l_diffuseColor * material.obj_diffuseColor * max(float(dot(fragNormal, light_vec)), 0.0f);
	frag_color = (toonlevel / toon) * normalize(vec4(Ia, material.ver) + vec4(Id, 0.0f) + vec4(Is, 0.0f));
}
=======
#version 330 core

struct Material
{
	sampler2D textureMap;
	vec3 l_ambientColor;
	vec3 l_diffuseColor;
	vec3 l_specularColor;
	// You can add more fields here...
	// Such as:
	//		1. diffuse/specular relections constants
	//		2. specular alpha constant
	//		3. Anything else you find relevant
	float ver;
	vec3 vertex_normal;
	vec3 p_light;
	vec3 eye;
	vec3 obj_ambientColor;
	vec3 obj_diffuseColor;
	vec3 obj_specularColor;
};

// We set this field's properties from the C++ code
uniform Material material;

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
// The final color of the fragment (pixel)
out vec4 frag_color;

int toon = 5;
float PI = 3.14159;

void main()
{
	// Sample the texture-map at the UV coordinates given by 'fragTexCoords'
	vec2 cylinder = vec2((atan(orig_fragPos.y , 1.5 * orig_fragPos.x) + PI * 0.5) / PI, -(-orig_fragPos.z + 0.5));
	vec2 spherical = vec2(atan(orig_fragPos.x, orig_fragPos.z) / (2 * PI), asin(orig_fragPos.y / 3) / PI);
	vec3 texture_color = vec3(texture(material.textureMap, fragTexCoords));
	vec3 Ia = material.l_ambientColor * material.obj_ambientColor;
	vec3 light_vec = normalize(material.p_light - fragPos);
	float toonlevel = floor(pow(max(float(dot(fragNormal, light_vec)), 0.0f), material.ver) * toon);
	vec2 plane = vec2(orig_fragPos.x, orig_fragPos.y);
	vec3 Is = material.l_specularColor * material.obj_specularColor * (toonlevel / toon);
	vec3 Id = material.l_diffuseColor * material.obj_diffuseColor * max(float(dot(fragNormal, light_vec)), 0.0f);
	frag_color = (toonlevel / toon) * normalize(vec4(Ia, material.ver) + vec4(Id, 0.0f) + vec4(Is, 0.0f));
}
>>>>>>> f76abf508cfd7d9d2360819e313b9e8abe594dff

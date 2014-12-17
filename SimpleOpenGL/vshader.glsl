#version 330
uniform vec3 theta;
uniform vec3 trans;
uniform vec3 scale;

uniform vec4 proj;

uniform vec3 eye;
uniform vec3 lookat;
uniform vec3 up;

in vec3 vPosition;
in vec3 vNormal;

uniform vec3 lightPosition;

out vec3 L;
out vec3 E;
out vec3 H;
out vec3 N;

in vec2 vTexCoord;
uniform sampler2D text;
out vec2 texCoord;

void main()
{
	vec4 homogPos = vec4(vPosition, 1.0);

    // Compute the sines and cosines of each rotation
    // about each axis
    vec3 angles = radians (theta);
    vec3 c = cos (angles);
    vec3 s = sin (angles);
    
	texCoord = vTexCoord;

    // rotation matricies
    mat4 rx = mat4 (1.0,  0.0,  0.0,  0.0, 
                    0.0,  c.x,  s.x,  0.0,
                    0.0, -s.x,  c.x,  0.0,
                    0.0,  0.0,  0.0,  1.0);
                    
    mat4 ry = mat4 (c.y,  0.0, -s.y,  0.0, 
                    0.0,  1.0,  0.0,  0.0,
                    s.y,  0.0,  c.y,  0.0,
                    0.0,  0.0,  0.0,  1.0);

    mat4 rz = mat4 (c.z, -s.z,  0.0,  0.0, 
                    s.z,  c.z,  0.0,  0.0,
                    0.0,  0.0,  1.0,  0.0,
                    0.0,  0.0,  0.0,  1.0);

	mat4 transMat = mat4 (	1.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0,
							trans.x, trans.y, trans.z, 1.0);
          
    mat4 scaleMat = mat4 (	scale.x, 0.0,		0.0,	0.0,
							0.0,	scale.y,	0.0,	0.0,
							0.0,	0.0,	scale.z,	0.0,
							0.0,	0.0,		0.0,	1.0);


	//projData = {nearPlane, farPlane, width, height}	

	mat4 projMat = mat4 (2.*proj[0]/proj[2],		0.,	0.,	0.,
						 0.	,	2.*proj[0]/proj[3],	0.,	0.,
						 0.	,	0.,	-1.0 * (proj[1]+proj[0])/(proj[1]-proj[0]),	-1.0,
						 0.	,	0.,	-2.0*(proj[1]*proj[0])/(proj[1]-proj[0]),	0.);

	//need norm of this
	vec3 n = normalize(eye - lookat);
	vec3 u = normalize(cross(up, n));
	vec3 v = cross(n,u);

	mat4 viewMat = mat4 (u.x, v.x, n.x,	0.,
						 u.y, v.y, n.y,	0.,
						 u.z, v.z, n.z,	0.,
						 dot(-1.0 * u, eye),
							  dot(-1.0 * v, eye),
								   dot(-1.0 * n, eye),	1.);

	mat4 T = projMat * viewMat * transMat * rz * ry * rx * scaleMat;

    gl_Position = T * homogPos;

	//Shading
	vec4 worldCoord4v = transMat * rz * ry * rx * scaleMat * homogPos;
	vec3 worldCoord3v = vec3(worldCoord4v.x / worldCoord4v.w,
	worldCoord4v.y / worldCoord4v.w,
	worldCoord4v.z / worldCoord4v.w);
	vec4 worldNormal4v = rz * ry * rx * vec4(vNormal, 1.0);
	vec3 worldNormal3v = vec3(worldNormal4v.x / worldNormal4v.w,
	worldNormal4v.y / worldNormal4v.w,
	worldNormal4v.z / worldNormal4v.w);
	L = normalize(lightPosition - worldCoord3v);
	E = normalize(eye - worldCoord3v);
	H = normalize(L + E);
	N = normalize(worldNormal3v);
}
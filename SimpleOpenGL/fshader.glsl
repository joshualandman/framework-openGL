#version 330
in vec3 L;
in vec3 E;
in vec3 H;
in vec3 N;
in vec4 color;

in vec2 texCoord;
uniform sampler2D text;

out vec4 outColor;

void main()
{
	//vec3 ambientProduct = vec3(.4, .4, .4);
	//vec3 diffuseProduct = vec3(.4, .4, .4);
	//vec3 specularProduct = vec3(.2, .2, .2);
	//float gloss = .7;
	
	//vec4 hue = vec4(1.0, 1.0, 1.0, 1.0);
	//vec4 hue = texture(text, texCoord);
	//vec3 ambient = hue.rgb * vec3(.1);
	//vec3 diffuse = hue.rgb * vec3(.8) * max( dot(N,L), 0. );
	//vec3 specular = vec3(1) * vec3(.1) * pow( max( dot(N,H), 0. ), 75. );
	//gl_FragColor = vec4( (ambient + diffuse + specular), hue.a);
	//vec3 ambient = ambientProduct;
	//float Kd = max( dot(L,N), 0.0 );
	//vec3 diffuse = Kd*diffuseProduct;
	//float Ks = pow( max(dot(N,H), 0.0), gloss );
	//vec3 specular = Ks * specularProduct;
	//if( dot(L, N) < 0.0 ) specular = vec3(0.0, 0.0, 0.0);
	//gl_FragColor = vec4( ( (ambient + diffuse) * hue.rgb + specular), hue.a);
	
	vec3 ambientProduct = vec3(.4, .4, .4);
	vec3 diffuseProduct = vec3(.4, .4, .4);
	vec3 specularProduct = vec3(.2, .2, .2);
	float gloss = .7;
	vec4 hue = texture( text, texCoord);
	vec3 ambient = hue.rgb * vec3(.1); //ambientProduct;
	float Kd = max( dot(L,N), 0.0 );
	vec3 diffuse = hue.rgb * vec3(.8) * max(dot(N,L), 0.0); //Kd*diffuseProduct;
	float Ks = pow( max(dot(N,H), 0.0), gloss );
	vec3 specular = vec3(1.0) * vec3(.1) * pow( max( dot(N,H), 0.0), .75); //Ks * specularProduct;
	if( dot(L, N) < 0.0 ) specular = vec3(0.0, 0.0, 0.0);
	outColor = vec4((ambient + diffuse + specular), hue.a);// * hue.rgb + specular), hue.a);
}

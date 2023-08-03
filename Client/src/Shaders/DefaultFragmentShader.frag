#version 330
varying vec4 color;
varying vec2 texCoord;

uniform vec2 resolution;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float globalTime;
uniform float deltaTime;

void main() {
	gl_FragColor = texture2D(tex0, texCoord);
}

/*vec3 palette( float t ) {
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);

    return a + b*cos( 6.28318*(c*t+d) );
}

void main() {
    vec2 uv = (gl_FragCoord.xy - 4.5 * resolution.xy) / (resolution.y);
	uv.y -= 7.5;
    vec2 uv0 = uv;
    vec3 finalColor = vec3(0.0);
	float speed = 0.001;
    
    for (float i = 0.0; i < 4.0; i++) {
        uv = fract(uv * 1.5) - 0.5;

        finalColor += (palette(length(uv0) + i*0.04 + globalTime*speed)) * (pow(0.01 / (abs(sin((length(uv) * exp(-length(uv0))) * 8.0 + globalTime*speed))), 1.10));
    }
        
    gl_FragColor = vec4(finalColor, color.a);
}*/

/*void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) /resolution.y;
    
    float a = atan(uv.y, uv.x);
    float r = length(uv);
    float time = deltaTime * 32.0;
    vec2 st = vec2(a / 3.1415, 0.1 / r) + 0.01 * time;
    
    vec4 col = mix(color, texture(tex0, st), time);
    col *= 3.5 * r;

    gl_FragColor = col;
}*/

/*void main() {
	vec2 q = texCoord;
    vec4 col = texture2D(tex0, q);
	
	q = gl_FragCoord.xy/resolution.xy;
	float dis = 1.;
	for (int i = 0; i < 12; i++)
	{
		float f = pow(dis, .45)+.25;

		vec2 st =  f * (q * vec2(1.5, .05)+vec2(-globalTime*.1+q.y*.5, globalTime*.12));
		f = (texture2D(tex1, st * .5, -99.0).x + texture2D(tex1, st*.284, -99.0).y);
		f = clamp(pow(abs(f)*.5, 29.0) * 140.0, 0.00, q.y*.4+.05);

		vec4 bri = vec4(.25);
		col += bri*f;
		dis += 3.5;
	}
	col = clamp(col, 0.0, 1.0);
			
	//col = mix(texture2D(tex0, vec2(q.x, 1.0-q.y)), col, smoothstep(2.25, 4.0, globalTime));
	col = pow(col, vec4(1.1));
	
	gl_FragColor = col;
}*/
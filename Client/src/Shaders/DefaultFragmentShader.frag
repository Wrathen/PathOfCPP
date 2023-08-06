varying vec4 color;
varying vec2 texCoord;

uniform vec2 resolution;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float globalTime;

void main() {
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
}
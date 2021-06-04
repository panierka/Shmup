uniform sampler2D texture;

uniform vec4 flashColor;
uniform float tint;

void main()
{
	vec4 pixel_color = texture2D(texture, gl_TexCoord[0].xy);

	vec4 colorDifference = vec4(0,0,0,1);

	colorDifference.r = flashColor.r - pixel_color.r;
	colorDifference.g = flashColor.g - pixel_color.g;
	colorDifference.b = flashColor.b - pixel_color.b;
	pixel_color.r = pixel_color.r + colorDifference.r * tint;
	pixel_color.g = pixel_color.g +colorDifference.g * tint;
	pixel_color.b =pixel_color.b + colorDifference.b * tint;


	gl_FragColor = pixel_color;

}

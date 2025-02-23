from PIL import Image
from glob import glob
from pathlib import Path
from io import StringIO

header = StringIO()
arrays = StringIO()
sprites = StringIO()

# header
header.write('#pragma once\n\n')
header.write('#include <cstdint>\n\n')
header.write('#include "../util.hpp"\n\n')
header.write("namespace Sprites {\n")
header.write('struct Sprite {Vec2i size; const uint8_t* data; };\n\n')

arrays.write(f'namespace {{\n')

# for each image, write the image data as a constexpr array
for infile_name in glob('./img/*'):
	path = Path(infile_name)
	img_name = path.stem
	img = Image.open(infile_name).convert('RGBA')
	img = img.resize((min(320, img.width), min(240, img.height)), Image.NEAREST)
	width, height = img.size
	arrays.write(f'  constexpr uint8_t {img_name}__data[{width*height*4}] = {{')
	for r, g, b, a in img.getdata():
		arrays.write(f'0x{a:02x}, 0x{b:02x}, 0x{g:02x}, 0x{r:02x}, ')
	arrays.write('};\n')
	sprites.write(f'constexpr Sprite {img_name} = {{Vec2i({width}, {height}), {img_name}__data}};\n')

arrays.write('} // namespace\n\n')

with open('./src/auto/sprites.hpp', 'w') as sprites_hpp:
	sprites_hpp.write(header.getvalue())
	sprites_hpp.write(arrays.getvalue())
	sprites_hpp.write(sprites.getvalue())
	sprites_hpp.write("} // namespace Sprites\n")

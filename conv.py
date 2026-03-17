import sys
from PIL import Image

def run(in_path, out_path):
    img = Image.open(in_path)
    w, h = img.size
    aspect = w/h
    if aspect > 320/480:
        new_w = int(480 * aspect)
        img = img.resize((new_w, 480), Image.Resampling.LANCZOS)
        img = img.crop(((new_w - 320)//2, 0, (new_w - 320)//2 + 320, 480))
    else:
        new_h = int(320 / aspect)
        img = img.resize((320, new_h), Image.Resampling.LANCZOS)
        img = img.crop((0, (new_h - 480)//2, 320, (new_h - 480)//2 + 480))

    img = img.convert('RGB')
    data = []
    
    # We apply the 16-bit swap during conversion
    for y in range(480):
        for x in range(320):
            r, g, b = img.getpixel((x, y))
            c = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            # Write HIGH byte then LOW byte instead of LOW then HIGH
            data.append((c >> 8) & 0xFF)
            data.append(c & 0xFF)
            
    with open(out_path, 'w') as f:
        f.write('#include <stdint.h>\n\n')
        f.write('const uint8_t data_out_raw[] = {\n')
        for i, b in enumerate(data):
            f.write(f'0x{b:02x},')
            if (i+1) % 16 == 0: f.write('\n')
        f.write('};\n')
        f.write(f'const unsigned int data_out_raw_len = {len(data)};\n')
        
if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])

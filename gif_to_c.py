import sys

def run(in_path, out_path):
    # Just read the raw bytes of the original file without destroying its quality or transparency
    with open(in_path, 'rb') as f:
        raw_gif_bytes = f.read()
        
    with open(out_path, 'w') as f:
        f.write('#include <stdint.h>\n\n')
        f.write('const uint8_t raw_gif_data[] = {\n')
        for i, b in enumerate(raw_gif_bytes):
            f.write(f'0x{b:02x},')
            if (i+1) % 16 == 0: f.write('\n')
        f.write('};\n')
        f.write(f'const unsigned int raw_gif_data_len = {len(raw_gif_bytes)};\n')
        
if __name__ == '__main__':
    run(sys.argv[1], sys.argv[2])

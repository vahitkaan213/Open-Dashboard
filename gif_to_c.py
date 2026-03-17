import sys
from PIL import Image, ImageSequence

def run(in_path, out_path, max_size=(160, 240)):
    with Image.open(in_path) as img:
        # Resize all frames to save space
        frames = []
        for i, frame in enumerate(ImageSequence.Iterator(img)):
            # Limit to 30 frames to save flash space on 8MB board
            if i >= 30: break
            
            f = frame.convert('RGB')
            # Thumbnail keeps aspect ratio
            f.thumbnail(max_size, Image.Resampling.LANCZOS)
            frames.append(f)
            
        print(f"Captured {len(frames)} frames")
        
        # Save as a temporary small GIF to get the raw bytes
        import io
        buf = io.BytesIO()
        frames[0].save(buf, format='GIF', save_all=True, append_images=frames[1:], loop=0, optimize=True)
        raw_gif_bytes = buf.getvalue()
        
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

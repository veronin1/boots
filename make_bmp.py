from PIL import Image

width, height = 1920, 1080
img = Image.new("RGB", (width, height))

for y in range(height):
    for x in range(width):
        r = (x * 255) // width
        g = (y * 255) // height
        b = 128
        img.putpixel((x, y), (r, g, b))

img.save("1080p_gradient.bmp")

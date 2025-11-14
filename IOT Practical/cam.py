import os
output_file="image.jpg"
os.system(f"rpicam-still -o {output_file}")
print(f"image saved as{output_file}")
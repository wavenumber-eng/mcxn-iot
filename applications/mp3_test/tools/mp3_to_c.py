import os
import sys
import binascii

def generate_c_array(folder_name, output_c="mp3_files.c", output_h="mp3_files.h"):
    files = [f for f in os.listdir(folder_name) if f.endswith(".mp3")]
    
    if not files:
        print("No MP3 files found in the folder.")
        return
    
    with open(output_c, "w") as c_file, open(output_h, "w") as h_file:
        
        h_file.write("#ifndef MP3_FILES_H\n#define MP3_FILES_H\n\n#include <stdint.h>\n\n")
        c_file.write("#include \"mp3_files.h\"\n\n")
        
        for file_name in files:
            file_path = os.path.join(folder_name, file_name)
            var_name = file_name.replace(".", "_").replace("-", "_")
            
            with open(file_path, "rb") as f:
                data = f.read()
                hex_data = ", ".join(f"0x{binascii.hexlify(bytes([b])).decode()}" for b in data)
                
                c_file.write(f"const uint8_t {var_name}[] = {{ {hex_data} }};\n")
                c_file.write(f"const size_t {var_name}_size = sizeof({var_name});\n\n")
                
                h_file.write(f"extern const uint8_t {var_name}[];\n")
                h_file.write(f"extern const size_t {var_name}_size;\n\n")
        
        h_file.write("#endif // MP3_FILES_H\n")
    
    print(f"Generated {output_c} and {output_h}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py <folder_name>")
        sys.exit(1)
    
    folder = sys.argv[1]
    generate_c_array(folder)

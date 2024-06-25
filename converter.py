import re
import os

def read_gcda_file(filepath):
    with open(filepath, 'rb') as file:
        gcda_content = file.read()

    # Regex pattern for possible path in raw bytes, accounting for backslashes and forward slashes
    # Assuming that the structure `C:/` is followed by any non-space ASCII characters until `.gcda`
    path_pattern = re.compile(rb'C:[\\/](?:[^\x00-\x1F\x7F "])+\.gcda')

    # Find all matches of the path pattern
    matches = list(path_pattern.finditer(gcda_content))

    path_and_data = {}

    # Checking if we have at least one match
    if matches:
        for i in range(len(matches)):
            # Get the current match and the next match
            start_match = matches[i]
            end_match = matches[i+1] if i+1 < len(matches) else None
            
            start = start_match.end()
            # If there's another path ahead, the current blob ends just before it starts
            end = end_match.start() if end_match else len(gcda_content)
            path = gcda_content[start_match.start():start_match.end()]
            binary_blob = gcda_content[start:end]

            # Attempt to decode the path
            try:
                decoded_path = path.decode('utf-8')
            except UnicodeDecodeError:
                # If decoding fails, use a fallback representation
                decoded_path = repr(path)

            path_and_data[decoded_path] = binary_blob

        return path_and_data
    else:
        print("No paths were found in the binary file.")
        return {}

gcda_filepath = 'dump.bin'

# Extract the paths and blobs
extracted_data = read_gcda_file(gcda_filepath)

# Do something with the extracted data
for path, data_blob in extracted_data.items():
    print(f"Path: {path}")
    with open(path, 'wb') as blob_file:
                blob_file.write(data_blob)
    print(f"Wote binary blob of {len(data_blob)} bytes\n")


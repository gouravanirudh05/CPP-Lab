import binascii

def decode_hex_string(hex_string, key):
    # Convert the hex string to bytes
    bytes_data = bytes.fromhex(hex_string)
    
    # XOR each byte with the key
    decoded_bytes = bytes([b ^ key for b in bytes_data])
    
    # Convert the decoded bytes back to a string
    decoded_string = decoded_bytes.decode('utf-8', errors='ignore')
    
    return decoded_string

# Provided hex string and key
hex_string = "0a5b046d07f6f971b7776de682f57c5b9cdc8fa060db7ef59de82e721c8098f4"
key = 146

# Decode the string
decoded_string = decode_hex_string(hex_string, key)
print(decoded_string)

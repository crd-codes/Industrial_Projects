# File Packer & Unpacker with Encryption

# 🛠 Technology : Java Programming

---

## 📌 Project Overview

This project is a **Java-based file utility tool** that provides functionality for packing multiple files into a single archive and unpacking them back with all metadata preserved.  
To enhance security, the packed file is **encrypted**, and only authorized users can decrypt and extract the data.  

---

## ✨ Features

### File Packing
- Combines multiple regular files into a single archive file.
- Stores metadata (file name, size) along with file content.

### File Unpacking
- Extracts individual files from the packed archive.
- Restores all original metadata and file structure.

### Data Security
- Built-in encryption and decryption to protect packed files.
- Uses XOR-based encryption in Java.


## ⚙️💻 Example Usage (Console Flow)

### Packing files
```bash
$ javac Packer.java
$ java Packer
Enter the name of folder: Data
Enter the name of packed file: packed.txt
Folder is present
Number of files in the folder are: 3
```

### Unpacking files
```bash
$ javac Unpacker.java
$ java Unpacker
Enter the name of packed file: packed.txt
File name: file1.txt
File size: 120
File name: file2.txt
File size: 250
File name: file3.txt
File size: 180
```

# 👨‍💻 Author

CR Dugade (crd-codes)









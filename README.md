# MP3 Tag Reader and Editor (ID3v2.3)

📄 Project Description

MP3 Tag Reader and Editor is a C-based command-line utility designed to interact with ID3v2.3 metadata tags** in MP3 files. The program allows users to view and edit embedded song information such as the title,artist,album,year,genre and comment.

The tool works by reading the MP3 file in binary mode, identifying the specific metadata frames, and either displaying or updating their contents. Edits are performed by creating a temporary MP3 copy with the updated tag, preserving the original structure of the file.

This project demonstrates key concepts in systems programming, such as:

- File I/O with binary data
- Manual endian conversion
- Dynamic memory management
- Modular C programming
- Command-line interface design

## 🗂️ File Structure

| File         | Description                                      |
|--------------|--------------------------------------------------|
|   main.c     | Entry point; parses command-line arguments       |
|   edit.c     | Modifies ID3v2.3 tag frames in the MP3 file      |
|   view.c     | Reads and displays tag frames                    |
|   header.h   | Declarations for shared functions                |

## ⚙️ Compilation

Compile the project using GCC:
gcc *.c


🚀 Usage

🔍 View Metadata

./a.out -v <filename>.mp3
Displays the following fields (if present):

Title
Artist
Album
Year
Genre
Comment

✏️ Edit Metadata

./a.out -e <filename>.mp3 <option> <new_value>

Edit Options:

| Option | Frame | Field   |
| ------ | ----- | ------- |
| `-t`   | TIT2  | Title   |
| `-a`   | TPE1  | Artist  |
| `-A`   | TALB  | Album   |
| `-y`   | TYER  | Year    |
| `-g`   | TCON  | Genre   |
| `-c`   | COMM  | Comment |


Example:

./a.out -e song.mp3 -y 2025
This updates the year in the MP3 file to 2025.

🆘 Help

./a.out -h
Displays a help menu with available commands and usage instructions.

---------------HELP MENU----------------
 -v -> to view mp3 file contents
 -e -> to edit mp3 file contents
 -t -> to edit song title
 -a -> to edit artist name
 -A -> to edit album name
 -y -> to edit year
 -g -> to edit content
 -c -> to edit comment

📋 Example output

./a.out -v song.mp3

# Output(view):
-------------Selected View details-------------

---------------------------------------------
        MP3 Tag Reader for ID3v2
---------------------------------------------
Title   :   Sunnysunny
Artist  :   Yo Yo Honey Singh - [SongsPk.CC]- [SongsPk.CC]
Album   :   Yaariyan
Year    :   2013
Genre   :   Bollywood Music - [SongsPk.CC]C]- [SongsPk.CC]
Comment :   eng
---------------------------------------------

-------------Details displayed successfully--------------

# Output(edit):
-------------Selected edit details-------------

--------Changed the Year---------
Year    :   2025
--------Year Changed successfully---------


# SwiftGrep

**Author:** Luke Young  
**Language Standard:** C++20

SwiftGrep is a cross-platform command-line text searching utility written in modern C++. It is inspired by the Unix `grep` utility and is being developed as a learning project focused on writing clean, portable, and efficient C++.

## Command Syntax

`swiftGrep [-i|-v|-c|-l|-f] SEARCH_TEXT FILE...`

## Current Features

- Search text files for matching strings
- Command-line interface
- Basic command-line argument validation
- Multiple file support
- Flags: -i case-insensitive, -v invert-match, -c count-only, -l line-numbers, -f file-name

## Development Roadmap

### Completed
- [x] Basic file reader
- [x] Basic string search
- [x] Command-line argument support
- [x] Display file name and line number
- [x] Argument validation
- [x] Case-insensitive searching (basic one flag option -i)
- [x] Multiple file support
- [x] One selectable command-line flag
- [x] Support multiple command-line flags simultaneously

### Planned
- [ ] Recursive directory searching
- [ ] Unit tests
- [ ] Performance optimization
- [ ] Cross-platform build system (CMake)
- [ ] Continuous Integration (GitHub Actions)
- [ ] Version 1.0 release

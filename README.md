# Chess-CPP

How to install:
  1. Download SFML https://www.sfml-dev.org/ (Windows) or install (Mac OS) 'brew install sfml'
  2. Compile it

Compiling (Mac OS):
  1. g++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -o output_filename -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -std=c++20

Compiling (Windows):
  1. g++ -c main.cpp -o output_filename.o -I"install_SFML_PATH\include" -DSFML_STATIC
  2. g++ output_filename.o -o output_filename -L"sfml-install-path\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s

cub3D - map parsing helper
==========================

This repository contains a partial implementation of the map parsing logic for the 42 cub3D / so_long style project.

Map parsing expectations (inferred):
- Map file must have a `.ber` extension.
- Read the entire file, join lines using `\n`, and split into a 2D map array.
- Track `map_width` (max line length without trailing newline) and `map_height` (number of non-empty lines).
- Validate:
  - Rectangular (all rows same width)
  - Surrounded by walls (first/last rows and first/last columns are '1')
  - Contains exactly one player 'P', at least one collectible 'C', and exactly one exit 'E'
  - Screen size check (ensure the map fits in the intended window size)

How to link this project to GitHub (local -> remote):
1. Create a GitHub repository on github.com.
2. From this project directory run:

```bash
git init
git add .
git commit -m "Initial commit: add map parsing files"
git branch -M main
git remote add origin git@github.com:USERNAME/REPO.git
git push -u origin main
```

Replace USERNAME/REPO.git with your repository path. If you prefer HTTPS, use the HTTPS remote URL.

Notes:
- I added a basic `.gitignore`. I did not modify the existing source files.
- I couldn't fetch the PDF subject (blocked). If you can paste or upload the subject text or allow network access, I will precisely align validations with the official subject.
